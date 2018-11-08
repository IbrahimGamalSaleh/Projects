#define _CRT_SECURE_NO_WARNINGS
#include "cmdfile.cpp"
#include "helpfile.cpp"
#include <iostream>

void Interfancy();
void VERSION();
void WELCOME();
void execute(char*);

void main(int argc, char *argv[]) {
	
	if (argc >2){
		return (void)(printf("wrong call\nonly one option (either \k or \c) and command\n"));
		system("pause");
	}
	if (argc > 1 && strcmp(argv[0], "/k") && strcmp(argv[0], "/c")) {
		return (void)(printf("Syntax error\nonly one option (either \k or \c) and command\n"));
		system("pause");
	}
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

		execute(command);
		
		//if (strcmp(args[1], "\c") == 0)			
		//	return;

		if (strcmp(PATH, "WEWANTEXIT") == 0)
			exit(0);
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
	int i, j, l = strlen(line);
	
	for (i = 0; i < l; ++i)
		if (line[i] != ' ') break;

	for (j=0; i < l && j<KW_LEN && line[i] != ' '; ++j, ++i)
		kw[j] = line[i];

	kw[j] = 0;

	for (int k = 0; kw[k]; ++k)
		kw[k] = toupper(kw[k]);

	for (j=0, i = strlen(kw) + 1; i<strlen(line); ++j, ++i)
		line[j] = line[i];
	line[j] = 0;

	for (i = 0; i < CMDS; ++i)
		if (strcmp(cmd[i], kw) == 0) {
			cmds[i](line);
			break;
		}

	if (i == CMDS)
		printf("Sorry, unrecognizable command '%s', type 'help' for available commands\n", line);

}
