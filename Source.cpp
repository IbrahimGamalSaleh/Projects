//#include <bits/stdc++.h>
#include <regex>
#include <iostream>
#include <console.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <utility>

#define KW_LEN 14
#define CMDS 20

char command[1024];
char PATH[1024];

// commands, starts here
void ATTRIB(char*);
void CD(char*);
void CHDIR(char*);
void CLS(char*);
void CMD(char*);
void DEL(char*);
void DIR(char*);
void EDIT(char*);
void EXIT(char*);
void HELP(char*);
void MD(char*);
void MKDIR(char*);
void PRINT(char*);
void RD(char*);
void RENAME(char*);
void SYSTEMINFO(char*);
void TASKLIST(char*);
void TITLE(char*);
void TYPE(char*);
void VER(char*);
// commands, ends here

char cmd[CMDS][14] = { "ATTRIB", "CD", "CHDIR", "CLS", "CMD", "DEL"
					, "DIR", "EDIT", "EXIT", "HELP", "MD", "MKDIR"
					, "PRINT", "RD", "RENAME", "SYSTEMINFO"
					, "TASKLIST", "TITLE", "TYPE", "VER"};

void(*funs[CMDS]) (char*) = { ATTRIB, CD, CHDIR, CLS, CMD, DEL
							, DIR, EDIT, EXIT, HELP, MD, MKDIR
							, PRINT, RD, RENAME, SYSTEMINFO
							, TASKLIST, TITLE, TYPE, VER };

void Interfancy();
void VERSION();
void WELCOME();
void execute(char*);

void main(void) {

	strcpy(PATH, "C:\\Users\\Youssof Kamal El - Din");

	Interfancy();

	while (1) {

		do {
			printf("%s>", PATH);
			fgets(command, 1024, stdin);
			command[strlen(command) - 1] = 0;
		} while (strlen(command) == 0);

		execute(command);
	}
}

void VERSION() {
	printf("\t\t      MyMy [Vergin 0.1]\n");
}

void WELCOME() {
	printf("\t\tWelcome to MyMy\n");
}

void Interfancy() {

	VERSION();
	//WELCOME();

	printf("\n");
	printf("* Write 'help' for a list of commands\n\n");

}

void execute(char* line) {

	char kw[KW_LEN];
	int i, l = strlen(line);

	for (i = 0; i < l && line[i] != ' '; ++i)
		kw[i] = line[i];

	kw[i] = 0;

	for (int k = 0; kw[k]; ++k)
		kw[k] = toupper(kw[k]);

	int j = 0;
	for (int i = strlen(kw) + 1; i<strlen(line); ++j, ++i)
		line[j] = line[i];
	line[j] = 0;

	for (i = 0; i < CMDS; ++i)
		if (strcmp(cmd[i], kw) == 0) {
			funs[i](line);
			break;
		}

	if (i == CMDS)
		printf("Sorry, unrecognizable command '%s', type 'help' for available commands\n", line);

}

void ATTRIB(char* LINE) {

}

void CD(char* LINE) {

	if (strlen(LINE) == 0)
		printf("%s", PATH);
	else strcpy_s(PATH, LINE);

}

void CHDIR(char* LINE) {

	CD(LINE);

}

void CLS(char* LINE) {
	//clrscr(0);
}

void CMD(char* LINE) {}

void DEL(char* LINE) {

}

void DIR(char* LINE) {

	WIN32_FIND_DATAA d;
	FILETIME ftLocal;
	SYSTEMTIME stCreate;
	int dir = 0;
	int file = 0;
	INT64 size;
	HANDLE hfile = FindFirstFileA(LINE, &d);
	if (hfile != INVALID_HANDLE_VALUE)
	{

		do
		{
			FileTimeToLocalFileTime(&d.ftCreationTime, &ftLocal);
			FileTimeToSystemTime(&ftLocal, &stCreate);

			printf("%02d/%02d/%d %02d:%02d:%02d",
				stCreate.wMonth, stCreate.wDay, stCreate.wYear,
				stCreate.wHour, stCreate.wMinute, stCreate.wSecond);
			if (d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{

				std::cout << "    <DIR>    ";
				dir++;
			}
			else
			{

				size = d.nFileSizeHigh;
				size <<= 32;
				size += d.nFileSizeLow;
				printf("         %lld", size);
				file++;
			}
			std::cout << "          " << d.cFileName << "\n";
		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}
	printf("   DIR = %8d \n", dir);
	printf("   FILE = %8d \n", file);

}

void EDIT(char* LINE) {

}

void EXIT(char* LINE) {
	system("exit");
}

void HELP(char* LINE) {
	printf("\n");

	printf("For more information on a specific command, type HELP command-name\n");

	printf("CD\t\tDisplays the name of or changes the current directory.\n");
	printf("CHDIR\t\tDisplays the name of or changes the current directory.\n");
	printf("CLS\t\tClears the screen.\n");
	printf("CMD\t\tStarts a new instance of the Windows command interpreter.\n");
	printf("DIR\t\tDisplays a list of files and subdirectories in a directory.\n");
	printf("EXIT\t\tQuits the CMD.EXE program (command interpreter).\n");
	printf("HELP\t\tProvides Help information for Windows commands.\n");
	printf("MKDIR\t\tCreates a directory.\n");
	printf("PRINT\t\tPrints a text file.\n");
	printf("SYSTEMINFO\tDisplays machine specific properties and configuration.\n");
	printf("TASKLIST\tDisplays all currently running tasks including services.\n");
	printf("TITLE\t\tSets the window title for a CMD.EXE session.\n");
	printf("VER\t\tDisplays the Windows version.\n");

	printf("\nFor more help, think about it twice; there's no online-help :P\n");
	printf("\TYPE\t\tDisplays the contents of a text file.\n");
	printf("\n");
}

void MD(char* LINE){

}

void MKDIR(char* LINE) {}

void PRINT(char* LINE) {}

void RD(char* LINE) {

}

void RENAME(char* LINE) {

}

void SYSTEMINFO(char* LINE) {}

void TASKLIST(char* LINE) {}

void TITLE(char*LINE) {
	SetConsoleTitleA(LINE);
}

void VER(char* LINE) {}

void TYPE(char* LINE) {
	//char*cont = new char[10000];
	std::string cont = "";
	std::fstream File;
	File.open(LINE);
	if (File.is_open())
	{
		while (!File.eof())
		{
			std::getline(File, cont);
			std::cout << cont << "\n";
		}

	}
	else
	{
		std::cout << "Failed to open this file";
	}
	File.close();
}
void TIME(char*LINE)
{
	time_t ct;
	tm * tt = new tm();
	time(&ct);
	localtime_s(tt, &ct);
	printf("%d / %d / %d  %d:%d:%d\n", tt->tm_mday, tt->tm_mon + 1, tt->tm_year + 1900, tt->tm_hour, tt->tm_min, tt->tm_sec);

}

/*


Interface   --- vvv

help-for-commands   --- vvv

**commands
-check for recognizable commands and safety of unrecognizable   --- vvv
-working commands
-more commands


*-PATH needs username of system
*-VER command prints version of Operating System
*-MKDRI , DIR
*-List of File names, last-modified date&time, size





















*/
