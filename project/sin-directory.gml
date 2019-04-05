#define sinDirectoryDefine
/* SIN DIRECTORY DLL | VERSION 1.2.0 */

/* initialize the DLL, call this script before you use any functions from the DLL */

//DLL Path
var_sin_directory_dll = working_directory + "\sin-directory.dll";


//Declare functions available
global.var_sin_directory_get_path = external_define(var_sin_directory_dll, "sin_directory_get_path", dll_cdecl, ty_string, 1, ty_real);


#define sinDirectoryGetPath

return external_call(global.var_sin_directory_get_path, argument[0]);

