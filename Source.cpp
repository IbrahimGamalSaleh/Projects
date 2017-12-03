//#include <bits/stdc++.h>
#include "TASKLIST.cpp"
#include <regex>
#include <iostream>
#include <console.h>
#include <windows.h>
#include <fstream>
#include <istream>
#include <ostream>
#include <conio.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <utility>

#define KW_LEN 14
#define CMDS 30

char command[1024];
char PATH[1024];

// commands, starts here
void ATTRIB(char*);
void CD(char*);
void CHDIR(char*);
void CLS(char*); //*
void CMD(char*); //*
void DEL(char*);
void DIR(char*); //*
void EDIT(char*);
void EXIT(char*); //*
void FIND(char*); 
void HELP(char*); //*
void MD(char*);
void MKDIR(char*);
void PRINT(char*); //*
void RD(char*);
void RENAME(char*); //*
void SYSTEMINFO(char*);
void TASKLIST(char*); //*
void TITLE(char*); //*
void TIME(char*); //*
void TYPE(char*); //*
void VER(char*); // mostly can't
				 // commands, ends here

char cmd[CMDS][14] = { "ATTRIB", "CD", "CHDIR", "CLS", "CMD", "DEL"
, "DIR", "EDIT", "EXIT", "FIND", "HELP", "MD", "MKDIR"
, "PRINT", "RD", "RENAME", "SYSTEMINFO"
, "TASKLIST", "TITLE", "TIME", "TYPE", "VER" };

void(*funs[CMDS]) (char*) = { ATTRIB, CD, CHDIR, CLS, CMD, DEL
, DIR, EDIT, EXIT, FIND, HELP, MD, MKDIR
, PRINT, RD, RENAME, SYSTEMINFO
, TASKLIST, TITLE, TIME, TYPE, VER };

void Interfancy();
void VERSION();
void WELCOME();
void execute(char*);

void main(void) {

	strcpy(PATH, "C:\\Users\\");

	Interfancy();
	DWORD USRNAMEsize = 100;
	char USRNAME[100];
	GetUserNameA(USRNAME, &USRNAMEsize);

	strcpy(PATH + 9, USRNAME);

	while (1) {

		do {
			printf("%s>", PATH);
			fgets(command, 1024, stdin);
			command[strlen(command) - 1] = 0;
		} while (strlen(command) == 0);

		printf("%s\n", command);
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
	printf("%s\n", kw);
	for (i = 0; i < CMDS; ++i)
		if (strcmp(cmd[i], kw) == 0) {
			funs[i](line);
			break;
		}

	if (i == CMDS)
		printf("Sorry, unrecognizable command '%s', type 'help' for available commands\n", line);

}

// COMMANDS start here
void ATTRIB(char* LINE) {

	//	if (LINE[0])

}

void CD(char* LINE) {

	if (strlen(LINE) == 0)
		printf("%s\n", PATH);
	else strcpy_s(PATH, LINE);
	if (PATH[0] >= 'a')
		PATH[0] = PATH[0] + ('A' - 'a');

}

void CHDIR(char* LINE) {

	CD(LINE);

}

void CLS(char* LINE) {
	clrscr(0);
}

void CMD(char* LINE) {
	STARTUPINFO info = { sizeof(info),0,0,L"NEW" };
	PROCESS_INFORMATION processInfo;
	if (!CreateProcess(TEXT("G:\\FAC\\Third Year\\First Term\\Operating System\\PROJECT\\CODES\\VS2015\\PROJETC\\Debug\\PROJETC.exe"),   // No module name (use command line)
		NULL,				// Command line
		NULL,				// Process handle not inheritable
		NULL,				// Thread handle not inheritable
		FALSE,				// Set handle inheritance to FALSE
		CREATE_NEW_CONSOLE, // No creation flags
		NULL,				// Use parent's environment block
		NULL,			    // Use parent's starting directory 
		&info,				// Pointer to STARTUPINFO structure
		&processInfo)		// Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	/*

	if (CreateProcessA("G:\\FAC\\Third Year\\First Term\\Operating System\\PROJECT\\CODES\\VS2015\\PROJETC\\Debug\\PROJETC.exe", "",
	NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	}

	CreateProcessA(,NULL,);
	system("cmd \"G:\\FAC\\Third Year\\First Term\\Operating System\\PROJECT\\CODES\\VS2015\\PROJETC\\Debug\\PROJETC.exe\"");*/
}

void DEL(char* LINE) {

	WIN32_FIND_DATAA d;
	HANDLE hfile = FindFirstFileA(LINE, &d);
	if (hfile != INVALID_HANDLE_VALUE)
	{
		do
		{



		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}

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
				printf("\t %lld", size);
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

}

void FIND(char* LINE) {

	//std::string wrd = "";
	char wrd[10000];
	int i;
	
	for (i = 0; LINE[i+1] != '"';++i)
		wrd[i] = LINE[i+1];
	wrd[i] = 0;
	printf("%c\n", wrd[i]);
	
	for (i = 0; i+ strlen(wrd)+3 < strlen(LINE); ++i)
		LINE[i] = LINE[i+ strlen(wrd)+3];
	LINE[i] = 0;

	printf("\n%s\n", LINE);

	std::string cont = "";

	char pat[1024];
	for (i = 0; i < strlen(LINE) && LINE[i] != '\\'; ++i)
		pat[i] = LINE[i];

	printf("\n%s\n", pat);

	WIN32_FIND_DATAA d;
	HANDLE hfile = FindFirstFileA(LINE, &d);
	if (hfile != INVALID_HANDLE_VALUE) {
		printf("\n%s\n", LINE);
		do {
			strcpy(pat + i, d.cFileName);
			printf("---------- %s", pat);
			std::fstream File;
			File.open(pat, std::fstream::in);
			while (getline(File, cont)) {
				std::stringstream ssstrng(cont);
				std::string part="";
				while (ssstrng>>part)
					if (strcmp(part.c_str(),wrd)==0){
						printf("%s\n", cont.c_str());
						break;
					}
			}
			File.close();
			printf("\n\n");

		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}

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
	printf("\nTYPE\t\tDisplays the contents of a text file.\n");
	printf("\n");
}

void MD(char* LINE) {

}

void MKDIR(char* LINE) {

}

void PRINT(char* LINE) {

}

void RD(char* LINE) {

}

void RENAME(char* LINE) {

}

void SYSTEMINFO(char* LINE) {

}

void TASKLIST(char* LINE) {

	DWORD aProcesses[1024], cbNeeded, cProcesses;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return;

	cProcesses = cbNeeded / sizeof(DWORD);

	printf("\n|Process Name \t\t\t| PID  \t|\n");
	printf("------------------------------------------------------------------\n");

	for (int index = 0; index < cProcesses; index++) {
		char szProcessName[MAX_PATH] = "unknown";

		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[index]);
		HMODULE hMod;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
			GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName));

		printf("%s", szProcessName);
		for (int i = ceil(strlen(szProcessName) / 8.0); i < 5; ++i) printf("\t");
		printf("%*d\n", 6, aProcesses[index]);

	}

}

void TITLE(char*LINE) {
	SetConsoleTitleA(LINE);
}

void TIME(char* LINE)
{
	time_t ct;
	tm * tt = new tm();
	time(&ct);
	localtime_s(tt, &ct);
	printf("%d/%d/%d  %d:%d:%d\n", tt->tm_mday, tt->tm_mon + 1, tt->tm_year + 1900, tt->tm_hour, tt->tm_min, tt->tm_sec);

}

void TYPE(char* LINE) {

	std::string cont = "";

	WIN32_FIND_DATAA d;
	HANDLE hfile = FindFirstFileA(LINE, &d);
	char pat[1024];
	int i;
	for (i = 0; i < strlen(LINE) && LINE[i] != '\\'; ++i)
		pat[i] = LINE[i];

	/*	FILE *File = fopen(LINE, "r");

	if (File) // not NULL  //if (freopen("E:\a.bat","r",stdin))
	while (fscanf(File, "%s", cont))
	printf("%s\n", cont);
	else
	printf("Failed to open this file\n");

	fclose(File);
	*/

	if (hfile != INVALID_HANDLE_VALUE) {
		do {
			strcpy(pat+i, d.cFileName);
			std::fstream File;
			File.open(pat, std::fstream::in);
			while (getline(File,cont))
				printf("%s\n", cont.c_str());
			File.close();
			printf("\n\n");

		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}

}

void VER(char* LINE) {

}


/*

*-VER command prints version of Operating System




















*/
