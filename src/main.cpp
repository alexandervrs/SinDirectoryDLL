
#ifndef UNICODE
	#undef _UNICODE
#else
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

#define _WIN32_WINNT 0x0500
#define _WIN32_IE 0x0500

#define CSIDL_MYDOCUMENTS 0x0005

#include "main.h"
#include <windows.h>
#include <shlobj.h>


char special_directory_buffer[(MAX_PATH*4)+1];


export const char* sin_directory_get_path(double folder_type)
{
    wchar_t path[MAX_PATH+1] = {0};
	
	int folderID = -1;
	
	if (folder_type < 0) {
		return "";
	}
	
	switch ((int)folder_type) {
		case 0: // desktop
			folderID = CSIDL_DESKTOPDIRECTORY;
			break;
		case 1: // roaming appdata
			folderID = CSIDL_APPDATA;
			break;
		case 2: // local appdata
			folderID = CSIDL_LOCAL_APPDATA;
			break;
		case 3: // my documents
			folderID = CSIDL_MYDOCUMENTS;
			break;
		case 4: // my music
			folderID = CSIDL_MYMUSIC;
			break;
		case 5: // my pictures
			folderID = CSIDL_MYPICTURES;
			break;
		case 6: // my video
			folderID = CSIDL_MYVIDEO;
			break;
		case 7: // user profile
			folderID = CSIDL_PROFILE;
			break;
		case 8: // send to
			folderID = CSIDL_SENDTO;
			break;
		case 9: // start menu
			folderID = CSIDL_STARTMENU;
			break;
		case 10: // startup
			folderID = CSIDL_STARTUP;
			break;
		case 11: // templates
			folderID = CSIDL_TEMPLATES;
			break;
		case 12: // burn area
			folderID = CSIDL_CDBURN_AREA;
			break;
		case 13: // fonts
			folderID = CSIDL_FONTS;
			break;
		case 14: // resources
			folderID = CSIDL_RESOURCES;
			break;
		case 15: // program files
			folderID = CSIDL_PROGRAM_FILES;
			break;
		case 16: // program files x86
			folderID = CSIDL_PROGRAM_FILESX86;
			break;
		case 17: // program files common
			folderID = CSIDL_PROGRAM_FILES_COMMON;
			break;
		case 18: // system
			folderID = CSIDL_SYSTEM;
			break;
		case 19: // system x86
			folderID = CSIDL_SYSTEMX86;
			break;
		case 20: // windows
			folderID = CSIDL_WINDOWS;
			break;
		case 21: // programs
			folderID = CSIDL_PROGRAMS;
			break;
		case 22: 
			// temp
			break;
		case 23: 
			// cwd
			break;
	}
	
	if (folder_type < 22) {
		
		if (SHGetFolderPathW(NULL, folderID, NULL, 0, path) != S_OK)
		{
			//MessageBoxW(NULL, L"ERROR in SHGetFolderPathW", L"TEST", MB_OK);
			return "";
		}
		
		wcscat(path, L"\\"); // trailing slash
		
	} else if (folder_type == 22) {
		
		if (!GetTempPathW(MAX_PATH, path)) {
			//MessageBoxW(NULL, L"ERROR in GetTempPathW", L"TEST", MB_OK);
			return "";
		}
		
	} else if (folder_type == 23) {
		
		if (!GetCurrentDirectoryW(MAX_PATH, path)) {
			
			//MessageBoxW(NULL, L"ERROR in GetCurrentDirectoryW", L"TEST", MB_OK);
			return "";
			
		}
		
		wcscat(path, L"\\"); // trailing slash
		
	} else {
		return "";
	}
	
    //MessageBoxW(NULL, path, L"Special Directory", MB_OK);

    int buflen = WideCharToMultiByte(CP_UTF8, 0, path, lstrlenW(path), special_directory_buffer, MAX_PATH*4, NULL, NULL);
    if (buflen <= 0)
    {
        //MessageBoxW(NULL, L"ERROR in WideCharToMultiByte", L"TEST", MB_OK);
        return "";
    }

    special_directory_buffer[buflen] = 0;

    return special_directory_buffer;
}
