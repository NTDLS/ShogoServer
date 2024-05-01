/****************************************************************************
;
;	 MODULE:		ServerUtils (.CPP)
;
;	PURPOSE:		Server Utility Functions
;
;	HISTORY:		08/04/98 [blg] This file was created
;
;	COMMENT:		Copyright (c) 1998, Monolith Productions Inc.
;
****************************************************************************/

// Includes...
#include "StdAfx.h"
#include "ServerUtils.h"
#include "WinInet.h"

// Externs...
extern	CString g_sWebRegHost;
extern	DGUID	GAMEGUID;

// Globals...
HINSTANCE			s_hServerDLL     = NULL;
CreateServerFn		s_fnCreateServer = NULL;
DeleteServerFn		s_fnDeleteServer = NULL;
ServerInterface*	s_pServerMgr     = NULL;

// Functions...

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL LoadServerDLL(char *pDLLName)
{
	SI_CREATESTATUS status;

	if (s_pServerMgr && s_hServerDLL)
	{
		return(TRUE);
	}

	s_hServerDLL = LoadLibrary(pDLLName);

	if(!s_hServerDLL)
	{
		return(FALSE);
	}

	s_fnCreateServer = (CreateServerFn)GetProcAddress(s_hServerDLL, "CreateServer");
	s_fnDeleteServer = (DeleteServerFn)GetProcAddress(s_hServerDLL, "DeleteServer");
	
	if (!s_fnCreateServer || !s_fnDeleteServer)
	{
		FreeLibrary(s_hServerDLL);
		s_hServerDLL = NULL;
		return(NULL);
	}

	s_pServerMgr = NULL;

	status = s_fnCreateServer(SI_VERSION, GAMEGUID, &s_pServerMgr);

	if (status != 0)
	{
		return(FALSE);
	}

	return(TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ServerInterface* GetServerInterface()
{
	return(s_pServerMgr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FreeServerDLL()
{
	if (s_hServerDLL && s_fnDeleteServer)
	{
		s_fnDeleteServer();
		FreeLibrary(s_hServerDLL);
	}

	s_hServerDLL     = NULL;
	s_fnCreateServer = NULL;
	s_fnDeleteServer = NULL;
	s_pServerMgr     = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL HttpPostJson(const char* sUrl, const char* sPostData, BOOL bWait)
{
	char* headers = "Content-Type: application/json";
	char* accept[2] = {"*/*", NULL};

	HINTERNET hSession = InternetOpen("GameServ", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnect(hSession, g_sWebRegHost, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", sUrl, NULL, NULL, (const char**)accept,
		INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_PRAGMA_NOCACHE, 0);

	HttpSendRequest(hRequest, headers, strlen(headers), (void *)sPostData, strlen(sPostData));

	// Wait until the request is finished...
	if (bWait)
	{
		DWORD dwSize = 0;
		char  sBuf[1024];

		strcpy_s(sBuf, sizeof(sBuf), "");

		if (!InternetReadFile(hRequest, sBuf, 1000, &dwSize))
		{
			InternetCloseHandle(hSession);
			return(FALSE);
		}
	}


	InternetCloseHandle(hSession);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL HttpGet(const char* sUrl, const char* queryString, BOOL bWait)
{
	if (!sUrl) return(FALSE);

	HINTERNET hNet = InternetOpen("GameServ", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hNet) return(FALSE);

	CString utl(sUrl);
	if(queryString)
	{
		utl += "?";
		utl += queryString;
	}

	// Convert spaces to pluses...
	int nLen = utl.GetLength();
	for (int i = 0; i < nLen; i++)
	{
		if (utl.GetAt(i) == ' ') utl.SetAt(i, '+');
	}

	HINTERNET hHttp = InternetOpenUrl(hNet, utl, NULL, 0, 0, 0);
	if (!hHttp)
	{
		InternetCloseHandle(hNet);
		return(FALSE);
	}


	// Wait until the request is finished...
	if (bWait)
	{
		DWORD dwSize = 0;
		char  sBuf[1024];

		strcpy_s(sBuf, sizeof(sBuf), "");

		if (!InternetReadFile(hHttp, sBuf, 1000, &dwSize))
		{
			InternetCloseHandle(hNet);
			return(FALSE);
		}
	}


	InternetCloseHandle(hNet);

	return(TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RemoveTrailingStuff(char *pStr)
{
	int len;

	len = strlen(pStr);
	if(len > 0 && pStr[len-1] == '\n')
	{
		pStr[len-1] = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
