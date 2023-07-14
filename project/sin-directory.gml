#define sinDirectoryDefine
/* SIN DIRECTORY DLL | VERSION 3.2.0 */

/* initialize the DLL, call this script before you use any functions from the DLL */

//DLL Path
var_sin_directory_dll = working_directory + "\sin-directory.dll";


//Declare functions available
global.var_sin_directory_get_path = external_define(var_sin_directory_dll, "sin_directory_get_path", dll_cdecl, ty_string, 1, ty_real);
global.var_sin_directory_create = external_define(var_sin_directory_dll, "sin_directory_create", dll_cdecl, ty_real, 1, ty_string);
global.var_sin_directory_delete = external_define(var_sin_directory_dll, "sin_directory_delete", dll_cdecl, ty_real, 1, ty_string);
global.var_sin_directory_rename = external_define(var_sin_directory_dll, "sin_directory_rename", dll_cdecl, ty_real, 2, ty_string, ty_string);
global.var_sin_directory_exists = external_define(var_sin_directory_dll, "sin_directory_exists", dll_cdecl, ty_real, 1, ty_string);


#define sinDirectoryGetPath
return external_call(global.var_sin_directory_get_path, argument[0]);

#define sinDirectoryCreate
return external_call(global.var_sin_directory_create, argument[0]);

#define sinDirectoryRename
return external_call(global.var_sin_directory_rename, argument[0], argument[1]);

#define sinDirectoryDelete
return external_call(global.var_sin_directory_delete, argument[0]);

#define sinDirectoryExists
return external_call(global.var_sin_directory_exists, argument[0]);

