//#include <bits/stdc++.h>
#include <regex>
#include <iostream>
#include <console.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <utility>

#define KW_LEN 14
#define CMDS 13

char command[1024];
char PATH[1024];

// commands, starts here
void CD(char*);
void CHDIR(char*);
void CLS(char*);
void CMD(char*);
void DIR(char*);
void EXIT(char*);
void HELP(char*);
void MKDIR(char*);
void PRINT(char*);
void SYSTEMINFO(char*);
void TASKLIST(char*);
void TITLE(char*);
void VER(char*);
// commands, ends here

char cmd[CMDS][14] = { "CD", "CHDIR", "CLS", "CMD"
					, "DIR", "EXIT", "HELP", "MKDIR", "PRINT"
					, "SYSTEMINFO", "TASKLIST", "TITLE", "VER" }; // or maybe a struct ??

void(*funs[CMDS]) (char* Line) = { CD, CHDIR, CLS, CMD, DIR,
								EXIT, HELP, MKDIR, PRINT, SYSTEMINFO,
								TASKLIST, TITLE, VER };

void Interfancy();
void VERSION();
void WELCOME();
void execute(char*);

void main(void) {

	strcpy(PATH, "C:\\Users\\Youssof Kamal El-Din");

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

	for (int k = 0;kw[k];++k)
		kw[k] = toupper(kw[k]);

	for (int i = strlen(kw) + 1;i<strlen(line);++i)
		line[0+i] = line[i];


		for (i = 0; i < CMDS; ++i)
			if (strcmp(cmd[i], kw) == 0) {
				funs[i](line);
				break;
			}

	if (i == CMDS)
		printf("Sorry, unrecognizable command '%s', type 'help' for available commands\n", line);

}


void CD(char* LINE) {

	if (strlen(LINE) == 0)
		printf("%s", PATH);
	else strcpy(PATH, LINE);

}

void CHDIR(char* LINE) {

	CD(LINE);

}

void CLS(char* LINE) {
	//clrscr(0);
}

void CMD(char* LINE) {}

void DIR(char* LINE) {}

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

	printf("\n");
}

void MKDIR(char* LINE) {}

void PRINT(char* LINE) {}

void SYSTEMINFO(char* LINE) {}

void TASKLIST(char* LINE) {}

void TITLE(char*) {}

void VER(char* LINE) {}

/*


Interface   --- √√√

help-for-commands   --- √√√

**commands
-check for recognizable commands and safety of unrecognizable   --- √√√
-working commands
-more commands


 *-PATH needs username of system
 *-VER command prints version of Operating System
 *-MKDRI , DIR
 *-List of File names, last-modified date&time, size





















*/
