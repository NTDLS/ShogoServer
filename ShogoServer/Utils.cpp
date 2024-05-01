// Utils.cpp

#include "StdAfx.h"


int Bin2Hex(void *lpTarget, int iMaxSz, const void *lpSrc, int iSz, int iBytes, bool bPrefix)
{
	int iWPos = 0;
	int iRPos = 0;
	int iByte = 0;

	if (iBytes < 1)
	{
		return 0;
	}

	//Assert(((iSz * iBytes) + 1) > iMaxSz, "Buffer too small.");

	if (bPrefix)
	{
		((char *)lpTarget)[iWPos++] = '0';
		((char *)lpTarget)[iWPos++] = 'x';
	}

	while (iRPos < iSz)
	{
		iByte = (iBytes - 1);

		while (iByte >= 0)
		{
			((char *)lpTarget)[iWPos++] = "0123456789ABCDEF"[((((char *)lpSrc)[iRPos] >> (iByte--) * 4) & 0xF)];
		}
		iRPos++;
	}

	((char *)lpTarget)[iWPos] = '\0';

	return iWPos;
}

bool NewGUID(char *sOut, int iMaxOutSz)
{
	char sGuid[48];

	GUID lGUID;
	memset(&lGUID, 0, sizeof(GUID));
	if (CoCreateGuid(&lGUID) == S_OK)
	{
		int iLength = Bin2Hex(sGuid, sizeof(sGuid), &lGUID, sizeof(GUID), 2, false);

		if (iLength == 32)
		{

			for(int iRPos = 0, iWPos = 0; iRPos < iLength;	iRPos++)
			{
				sOut[iWPos++] = sGuid[iRPos];
				if(iRPos == 7 || iRPos == 11 || iRPos == 15 || iRPos == 19)
				{
					sOut[iWPos++] = '-';
				}
			}


			return true;
		}
	}
	return false;
}


CString TimeToString(DWORD dwTime, BOOL bNoHours)
{
	int nHours = dwTime / 3600000;
	dwTime -= nHours * 3600000;

	int nMinutes = dwTime / 60000;
	dwTime -= nMinutes * 60000;

	int nSeconds = dwTime / 1000;

	CString str;

	if (nHours == 0 && bNoHours)
	{
		str.Format("%02i:%02i", nMinutes, nSeconds);
	}
	else
	{
		str.Format("%i:%02i:%02i", nHours, nMinutes, nSeconds);
	}

	return(str);
}

void DissectTime(DWORD dwTime, int* pHour, int* pMin, int* pSec)
{
	*pHour = dwTime / 3600000;
	dwTime -= *pHour * 3600000;

	*pMin = dwTime / 60000;
	dwTime -= *pMin * 60000;

	*pSec = dwTime / 1000;
}

