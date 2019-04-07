
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
#include <iostream>
#include <vector>


static std::wstring utf8ToUTF16(const std::string &utf8)
{
    // Special case of empty input string
	if (utf8.empty()) {
		return std::wstring();
	}

	// Get length (in wchar_t's) of resulting UTF-16 string
	const int utf16_length = ::MultiByteToWideChar(
		CP_UTF8,            // convert from UTF-8
		0,                  // default flags
		utf8.data(),        // source UTF-8 string
		utf8.length(),      // length (in chars) of source UTF-8 string
		NULL,               // unused - no conversion done in this step
		0                   // request size of destination buffer, in wchar_t's
	);

	if (utf16_length == 0) {
		// Error
		DWORD error = ::GetLastError();
		throw ;
	}


	// // Allocate properly sized destination buffer for UTF-16 string
	std::wstring utf16;
	utf16.resize(utf16_length);

	// // Do the actual conversion from UTF-8 to UTF-16
	if ( ! ::MultiByteToWideChar(
		CP_UTF8,            // convert from UTF-8
		0,                  // default flags
		utf8.data(),        // source UTF-8 string
		utf8.length(),      // length (in chars) of source UTF-8 string
		&utf16[0],          // destination buffer
		utf16.length()      // size of destination buffer, in wchar_t's
		) )
	{
		DWORD error = ::GetLastError();
		throw;
	}

	return utf16;
}


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

export double sin_directory_create(char* new_folder)
{
	
	std::string path(new_folder);
	
	if (CreateDirectoryW(utf8ToUTF16(path).c_str(), NULL)) {
		return 1;
	} else {
		return 0;
	}
	
}

export double sin_directory_delete(char* folder)
{
	
	std::string path(folder);
	
	if (RemoveDirectoryW(utf8ToUTF16(path).c_str())) {
		return 1;
	} else {
		return 0;
	}
	
}

export double sin_directory_rename(char* folder, char* new_folder)
{
	
	std::string path(folder);
	std::string new_path(new_folder);
	
	DWORD attr = GetFileAttributesW(utf8ToUTF16(path).c_str());
	if ((attr & !FILE_ATTRIBUTE_DIRECTORY)) {
		return 0;
	}
	
	if (MoveFileW(utf8ToUTF16(path).c_str(), utf8ToUTF16(new_path).c_str())) {
		return 1;
	} else {
		return 0;
	}
	
}

export double sin_directory_exists(char* folder)
{
	std::string path(folder);
	
	DWORD attr = GetFileAttributesW(utf8ToUTF16(path).c_str());
	if (attr & FILE_ATTRIBUTE_DIRECTORY) {
		if (attr == INVALID_FILE_ATTRIBUTES) {
			return 0;
		} else {
			return 1;
		}
	} else {
		return 0;
	}
	
}
