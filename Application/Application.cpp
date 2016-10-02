// ConsoleApplication1.cpp : Defines the entry point for the console application.
// Samuel Javorka, orezanie (cut)

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include "..\Library\Library.h"
#include <iostream>

void DisplayUsage(char * appPath)
{
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(appPath, drive, dir, fname, ext);
	std::cout << fname << std::endl;
	std::cout << "\t-h - help" << std::endl;
}

/*
max - kolko znakov/segmentov chceme vypísať
delim - ak != 0, tak potom delitel segmentov
*/
void cut(unsigned int max, int delim, char *path);

int main(int argc, char **argv)
{
	int c;
	char *ptr;
	int delim = 0;
	int max = 0;
	char *path = NULL;
	if (argc == 1)
	{
		DisplayUsage(argv[0]);
	}
	else
	{
		while ((c = getopt(argc, argv, "hd:m:f:")) != EOF)
		{
			switch (c)
			{
			case 'h':
				DisplayUsage(argv[0]);
				return 0;
			case 'd':
				// prvý znak zo špecifikacie je oddelovať
				delim = optarg[0];
				break;
			case 'f':
				path = optarg;
				break;
			case 'm':
				max = strtol(optarg, &ptr, 10);
				break;
			case '?':
				std::wcout << "Chybny parameter '" << argv[optind - 1] << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			default:
				std::wcout << "Neznamy parameter '" << (char)c << "'" << std::endl;
				DisplayUsage(argv[0]);
				return -1;
			}
		}
	}


	cut(max, delim, path);
	return 0;
}

void cut(unsigned int max, int delim, char *path) {
	// ak nešpecifikujeme max, vypíše prvý segment/znak
	if (!max)
		max = 1;
	unsigned int charCounter = 0;
	unsigned int segmentCounter = 0;
	FILE *file = stdin;
	if (path != NULL) {
		file = fopen(path, "r");
		if (file == NULL) {
			std::cout << "nepodarilo sa otvorit subor" << std::endl;
			return;
		}
	}
	// read vstup, znak po znaku
	for (int ch = 0; (ch = fgetc(file)) != EOF; ++charCounter)
	{
		if (ch == '\n')
		{
			charCounter = segmentCounter = 0;
		}
		if (ch == delim)
		{
			++segmentCounter;
			// continue; //odkomentovat ak chceme vypisat bez delicu
		}

		if ((!delim && charCounter < max) || delim && segmentCounter < max)
		{
			putchar(ch);
		}

		// možme breaknut, nečitame dalej
		// else
		// break;
	}
	if (path != NULL) fclose(file);
}
