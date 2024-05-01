![image](https://github.com/NTDLS/ShogoServer/assets/11428567/fe2c8328-a1c5-436e-87ba-e1964366833d)

# ShogoServer
Augmented version of the original ShogoServer from March 11th of 1999, for more information check out: https://networkdls.com/Software/View/Shogo_MAD_Server_SourceCode/

## Build Instructions
This server was last built using Visual Studio 2020 on windows 11.

## See Also
* https://github.com/NTDLS/ShogoServersCom
* https://github.com/NTDLS/ShogoServer/
* https://ShogoServers.Com/

## Screenshots

![image](https://github.com/NTDLS/ShogoServer/assets/11428567/e7f82e6f-5ca5-4de4-a714-86c4dadbb148)
![image](https://github.com/NTDLS/ShogoServer/assets/11428567/9719e00e-ba53-45db-ac0d-1e8e1f600d1d)

![image](https://github.com/NTDLS/ShogoServer/assets/11428567/4ef0fded-eea1-47fa-9932-0a148ba876f1)
![image](https://github.com/NTDLS/ShogoServer/assets/11428567/d0e8c2c3-e1be-401e-b280-98492496c8ad)

![image](https://github.com/NTDLS/ShogoServer/assets/11428567/51e452c2-c43f-44db-8b7e-001aeae82be5)
![image](https://github.com/NTDLS/ShogoServer/assets/11428567/5d5b9a34-b980-4182-ad06-13b650773646)

The original server source code for the 1990s game SHOGO Mad. I'm dropping this here because it was a total pain to find and even more of a pain to extract given that the publishers decided to envelope the code in an installer executable. ugh.
Also known as the "Shogo Source Tools (VERSION 2.2)" and the "SHOGO SOURCE CODE v 2.2", this version was originally published in March 11th of 1999.

# Original Readme (Versions and links are out of date)

SHOGO SOURCE CODE v 2.2
----------------------------

You will want to get the Shogo Source Tools because it contains
a HELP file with the LithTech APIs and overview.  The 2.2 version
of the Shogo source contains VC++ 6.0 project files for the two
primary Shogo DLLs as well, now.

DirectPlay
----------

For the DirectPlay Lobby code in the Clientshell, you must have 
DPLobby.h (part of the DirectX 6 SDK).

We cannot legally redistribute the SDK itself; it must be obtained 
from Microsoft.

Debugging your Code
-------------------

To help with debugging, the Lithtech 'SOFTDIB.REN' renderer has been
included in this package; it is in the directory you installed the source
to.  Merely copy this .REN file to the same directory as your SHOGO client.exe
and it will be made available to you by the engine.

Compiling the Code
------------------

Once you have compiled your CSHELL.DLL, CRES.DLL, OBJECT.LTO, and
SRES.DLL files, you will want to put them into a new project
directory, and then stack that project directory on top of the
Shogo project as described in the README in the Tools portion of
this release.

Directories
-----------

APPHEADERS
	This directory contains the headers for Lithtech.
	This needs to be added to your INCLUDE file path in 
	your compiler.

CLIENTRES
	This directory contains the source for the
	cres.dll file.  This is used for localization;
	it's good to store text here so the main game
	code doesn't have to change when localized. :)

CLIENTSHELLDLL
	This directory contains the source for the
	cshell.dll file.  This is the client-side source;
	HUDs, special effects, client-side stuff is all 
	written here.

MISC
	This directory contains a few files taken from other
	places which are needed to compile the ShogoServ
	project.  GameSpyMgr.lib is the library that contains
	all the GameSpy functions, and it needs to be copied
	into a library include path.  server_interface.h is from
	of the engine source code and is required for much of 
	ShogoServ.  GameSpyMgr.h is the header for the GameSpyMgr
	library.

OBJECTDLL
	This directory contains the source for the
	object.lto file.  This is the server-side source;
	it ALSO contains all the definitions of objects 
	that you can place in DEdit (the editor).  It 
	should be apparent why after perusing the code
	for a little bit and realizing how Lithtech works. :)

SHARED
	This directory contains game-specific headers which
	are shared between client and server.  This should be
	added to your include path.

SHOGOSERV
	This is the source code to the standalone listen server.
	Yes, believe it or not, we ARE releasing this.  Maybe
	we're insane, or maybe we just care about the mod
	community. :)

Information/Help
----------------

If you have problems, there are several good resources:

* The official Shogo website at http://www.shogo-mad.com/
* PlanetShogo, a fan community site at http://www.planetshogo.com/
* The shogo-mod mailing list, a mailing list for mod authors.
  To subscribe, send e-mail to listar@lists.lith.com with the
  subject 'subscribe shogo-mod' (minus the quotes, of course).

This is not officially supported by Monolith; Monolith employees
do read the shogo-mod mailing list and will provide support there.
Please try to refrain from e-mailing them directly. :)

Thanks
------

We hope you enjoy Shogo: MAD and look forward to playing all
the modifications you come up with...

- The Shogo Team
- The LithTech Team

   Where's da luv?
-> M o n o l i t h <-
