#include <windows.h>
#include <stdio.h>

typedef double (*Func)(double,double);

int main(int argc, char **argv)
{
	Func function;
	double result;
	// load DLL
	HINSTANCE hinstLib = LoadLibrary("Math.dll");
	if(hinstLib == NULL) {
		printf("ERROR: unalbe to load DLL\n");
		return 1;
	}
	// get function address
	function = (Func)GetProcAddress(hinstLib, "Add");
	if(function == NULL) {
		printf("ERROR: unalbe to find DLL function\n");
		FreeLibrary(hinstLib);
		return 1;
	}
	// call function
	result = function(1.0, 2.0);
	// unload DLL file
	FreeLibrary(hinstLib);
	// display result
	printf("Result = %f\n", result);
	system("pause");
	return 0;
}