// Library.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Library.h"
//#include <windows.h>
//#include <stdio.h>
//#include <tchar.h>


//// This is an example of an exported variable
//LIBRARY_API int nLibrary=0;
//
//// This is an example of an exported function.
//LIBRARY_API int fnLibrary(void)
//{
//    return 42;
//}
//
//// This is the constructor of a class that has been exported.
//// see Library.h for the class definition
//CLibrary::CLibrary()
//{
//    return;
//}

LIBRARY_API std::string cutInput(unsigned int max, int delim, std::string &input) {
	// ak nešpecifikujeme max, vypíše prvý segment/znak
	if (!max)
		max = 1;
	unsigned int charCounter = 0;
	unsigned int segmentCounter = 0;
	std::string output;
	// read vstup, znak po znaku
	for (int ch = 0, i = 0; i < input.length(); ++charCounter, ++i)
	{
		ch = input[i];
		if (ch == '\n')
		{
			charCounter = segmentCounter = 0;
		}
		if (ch == delim)
		{
			++segmentCounter;
		}

		if ((!delim && charCounter < max) || delim && segmentCounter < max)
		{
			output.push_back(ch);
		}
	}

	return output;
}