#define _CRT_SECURE_NO_WARNINGS
#include "helpfile.h"


/* HELPS start here */

void HELP_ATTRIB(void) {

	printf("Displays or changes file attributes.\n");
	printf(" +   Sets an attribute.\n- Clears an attribute.\nR   Read - only file attribute."
		"A   Archive file attribute.\nS   System file attribute.\nH   Hidden file attribute.");
}

void HELP_CD(void) { 
	printf("Displays the name of or changes the current directory.\n");
	printf("CHDIR [/D] [drive:][path]\nCHDIR[..]\n"
		"CD[/ D][drive:][path]\nCD[..]\n");
	printf("Type CD drive: to display the current directory in the specified drive.\n"
		"Type CD without parameters to display the current drive and directory.\n");
}

void HELP_CLS(void) { 
	printf("Provides help information for Windows commands.\n\n");
	printf("HELP[command]\n\n");
	printf("\tcommand - displays help information on that command.\n");
}

void HELP_CMD(void) { 
	printf("Starts a new instance of the Windows command interpreter.\n\n");
	printf("CMD [[/C | /K] string]\n");
	printf("/C\tCarries out the command specified by string and then terminates\n/"
		"K\tCarries out the command specified by string but remains\n");
}

void HELP_COMP(void) { 
	printf("Compares the contents of two files or sets of files.\nCOMP[data1][data2]\n");
	printf("[/D] [/A]\n");
	printf("data1\tSpecifies location and name(s) of first file(s) to compare.\n");
	printf("data2\tSpecifies location and name(s) of second files to compare.\n");
	printf("/ D\tDisplays differences in decimal format.\n");
	printf("/ A\t Displays differences in ASCII characters.");
	printf("/N=number\tCompares only the first specified number of lines in each file.");
}

void HELP_COPY(void) { 
	printf("Copies one or more files to another location.\n");
	printf("COPY [source] [destination]\n");
}

void HELP_DEL(void) { 
	printf("Deletes one or more files.\n\n");
	printf("DEL names\n\n");
}

void HELP_DIR(void) { 
	printf("Displays a list of files and subdirectories in a directory.\nDIR[drive:][path][filename]\n[/O][/D][/N=number]\n");
	printf("/D\tSame as wide but files are list sorted by column\n");
	printf("/O\tList by files in sorted order by <DIR>\n");
}

void HELP_EXIT(void) {
	printf("Quits the CMD.EXE program\n\n");
}

void HELP_FIND(void) { 
	printf("Searches for a text string in a file or files.\n\n");
	printf("FIND \"string\"\"[path]filename\"\n\n");
	printf("  /V\tDisplays all lines NOT containing the specified string.\n");
	printf("/ C\tDisplays only the count of lines containing the string.\n");
	printf("/ N\tDisplays line numbers with the displayed lines.\n\n");
}

void HELP_HELP(void) { 
	printf("Provides help information for Windows commands.\n\n");
	printf("HELP[command]\n\n");
	printf("\tcommand - displays help information on that command.\n");
}

void HELP_MD(void) {
	printf("Creates a directory.\n\n");
	printf("MD[drive:]path\n\n");
}

void HELP_RD(void) { 
	printf("Removes (deletes) a directory.\n\n");
	printf("RMDIR [path] [/ S]\n\n");
}

void HELP_RENAME(void) { 
	printf("Renames a file or files.\n");
	printf("RENAME[drive:][path]filename1[drive:][path]filename2.\n");
}

void HELP_SORT(void) {
	printf("SORT[[drive:][path]filename]\n");
	printf("[/ r][/ o]\n");
	printf("/ r   Reverses the sort order; that is,\n");
	printf("sorts Z to A, then 9 to 0.\n");
	printf("/ o   Specifies the file where the sorted input is\n");
	printf("to be stored.If not specified, the data is\n");
	printf("written to the standard output.\n");
}

void HELP_TASKLIST(void) { 
	printf("This tool displays a list of currently running processes on\n");
	printf("either a local or remote machine.\n");
}

void HELP_TITLE(void) { 
	printf("	Sets the window title for the command prompt window.\n");	
	printf("		TITLE[string]\n");
	printf("		string       Specifies the title for the command prompt window.\n");
}

void HELP_TIME(void) { 
	printf("Displays or sets the system time.\n\nTIME");
}

void HELP_TYPE(void) { 
	printf("Displays the contents of a text file or files.\n");
	printf("TYPE[drive:][path]filename\n");
}
/* HELPS end here */