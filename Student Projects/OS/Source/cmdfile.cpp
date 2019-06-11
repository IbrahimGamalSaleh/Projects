#define _CRT_SECURE_NO_WARNINGS
#include "TASKLIST.cpp"
#include "cmdfile.h"
#include "helpfile.h"


// COMMANDS start here
void ATTRIB(char* LINE) {

	std::string fi = "";
	for (int i = 3; i < strlen(LINE); i++)
		fi += LINE[i];

	wchar_t file[1000];
	mbstowcs(file, (char*)fi.c_str(), 1000);
	bool b = 0;
	for (int i = 0; i < strlen(LINE); ++i) {
		if (LINE[i] == '+' && (b = 1))
			if (toupper(LINE[i + 1]) == 'H') SetFileAttributes(file, FILE_ATTRIBUTE_HIDDEN);
			else if (toupper(LINE[i + 1]) == 'A') SetFileAttributes(file, FILE_ATTRIBUTE_ARCHIVE);
			else if (toupper(LINE[i + 1]) == 'S') SetFileAttributes(file, FILE_ATTRIBUTE_SYSTEM);
			else if (toupper(LINE[i + 1]) == 'R') SetFileAttributes(file, FILE_ATTRIBUTE_READONLY);
			else {
				char c[20] = { 0 };
				for (int j = 0; i<20; ++j, ++i)
					if (LINE[i] != ' ') c[j] = LINE[i];
				printf("Invalid switch -'%s'\n", c);
				return;
			}
		else if (LINE[i] == '-' && (b = 1))
			if (toupper(LINE[i + 1]) == 'H') SetFileAttributes(file, !FILE_ATTRIBUTE_HIDDEN);
			else if (toupper(LINE[i + 1]) == 'A') SetFileAttributes(file, !FILE_ATTRIBUTE_ARCHIVE);
			else if (toupper(LINE[i + 1]) == 'S') SetFileAttributes(file, !FILE_ATTRIBUTE_SYSTEM);
			else if (toupper(LINE[i + 1]) == 'R') SetFileAttributes(file, !FILE_ATTRIBUTE_READONLY);
			else {
				char c[20] = { 0 };
				for (int j = 0; i<20; ++j, ++i)
					if (LINE[i] != ' ') c[j] = LINE[i];
				printf("Invalid switch -'%s'\n", c);
				return;
			}
			if (!b) {
				printf("Syntax Error\n");
				return;
			}
	} 

}

void CD(char* LINE) {

	bool d = 0;
	// the coming block (18 lines) for separated options line
	char options[20];
	printf("Options: ");
	std::cin.getline(options,20);
	for (int i = 0; i < strlen(options); ++i) {
		if (options[i] == '/')
			if (options[i + 1] == 'd') d = 1;
			else {
				char c[20] = { 0 };
				for (int j = 0; i<20; ++j, ++i)
					if (options[i] != ' ') c[j] = options[i];
				printf("Invalid switch -'%s'\n", c);
				return;
			}
		else {
			printf("Syntax error\n");
			return;
		}
	}  /*block ends here*/
	

	if (strlen(LINE) == 2) {
		LINE[0] = toupper(LINE[0]);
		LINE[2] = '\\';
		LINE[3] = 0;

		char volname[100];
		if (GetVolumeNameForVolumeMountPointA(LINE, volname, 100)) {
			printf("%s\n", drvs[LINE[0] - 'A']);
			strcpy(PATH, drvs[LINE[0] - 'A']);
		}
		return;
	}
	
	WIN32_FIND_DATAA path;
	HANDLE Hpath = FindFirstFileA(LINE, &path);

	if (path.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
		printf("it's a directory\n");
		strcpy(PATH, LINE);
		PATH[strlen(PATH)] = '\\';
		PATH[strlen(PATH)] = 0;
		printf("Copied\n");
	} else if (path.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
			if (path.dwReserved0 == IO_REPARSE_TAG_MOUNT_POINT)
				printf("it's drive");
	}
	else {
		printf("%s\n", LINE);
		printf("you've entered a wrong path\n");
		return;
	}
	
	if (strlen(LINE) == 0)
		printf("%s\n", PATH);
	else strcpy(PATH, LINE);
	if (PATH[0] >= 'a')
		PATH[0] = PATH[0] + ('A' - 'a');

}

void CLS(char* LINE) {

	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);

}

void CMD(char* LINE) {

	STARTUPINFOA info = { sizeof(info),0,0,"NEW" };
	PROCESS_INFORMATION processInfo;
	
	char CONSOLEPATH[1024];
	HMODULE s;
	DWORD ints;
	EnumProcessModules(GetCurrentProcess(), &s,sizeof(s),&ints);
	GetModuleFileNameA(s, CONSOLEPATH, 1024);
	
	printf("%s\n%s\n", CONSOLEPATH, LINE);
	fflush(stdin);
	if (!CreateProcessA(CONSOLEPATH,
			LINE, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &info, &processInfo)) {
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

}

void COMP(char* LINE) {
	
	bool a = 0, d = 0, n= 0, c=0;
	int num=0;
	char options[20] = { 0 };

	printf("options: ");
	std::cin.getline(options, 20);

	for (int i = 0; i < 20; ++i)
		if (options[i] == '/')
			if (options[i + 1] == 'd') d = 1;
			else if (options[i + 1] == 'a') a = 1;
			else if (options[i + 1] == 'c') c = 1;
			//else if (options[i + 1] == 'n') {
			//	n = 1;
			//	int lines = 0;
			//	for (int j = i + 3; j < 100; ++j)
			//		if (options[j] >= '0' && options[j] <= '9') lines = lines * 10 + options[j] - '0';
			//		else break; }
			 else {
				char sw[20] = { 0 };
				for (int j = 0; i<20; ++j,++i)
					if (options[i] != ' ') sw[j] = options[i];
				printf("Invalid switch -'%s'\n", sw);
			}

	int y = strlen(LINE);
	std::string firstfile = "";
	std::string secondfile = "";
	std::fstream f1;
	std::fstream f2;

	char ch1, ch2;
	
	int i;
	for (i = 0; i < y; ++i)
		if (LINE[i] == '\"') break;

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
		else firstfile += LINE[i];
	
	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
	
	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
		else secondfile += LINE[i];
		
	f1.open(firstfile);
	if (!f1.is_open())
		printf("first file not found!\n");
	f2.open(secondfile);
	if (!f2.is_open())
		printf("second file not found!\n");

	f1.seekg(0, std::ios_base::end);
	f2.seekg(0, std::ios_base::end);
	int size_of_first = f1.tellg();
	int size_of_second = f2.tellg();
	
	if (f1.is_open() && f2.is_open()){
		if (size_of_first != size_of_second)
			printf("files aren't same size\n");
		else if (size_of_first == size_of_second) {
			f1.seekg(0, std::ios::beg);
			f2.seekg(0, std::ios::beg);
			int er;
			while (f1.good()) {
				ch1 = f1.get();
				ch2 = f2.get();

				if (c) 
					if (tolower(ch1) != tolower(ch2)) {
						er = (int)f1.tellg() - 1;
						printf("Compare error at OFFSET %d \n", er);
						if (d) printf("File 1 = %d\n File 2 = %d\n", ch1, ch2);
						else printf("File 1 = %c\n File 2 = %c\n", ch1, ch2);
					} else;
				else if (ch1 != ch2) {
					er = (int)f1.tellg() - 1;
					printf("Compare error at OFFSET %d \n", er);
					if (d) printf("File 1 = %d\n File 2 = %d\n", ch1, ch2);
					else printf("File 1 = %c\n File 2 = %c\n", ch1, ch2);
				} 
			}
		}
	}
	f1.close();
	f2.close();
	printf("Compare more files (Y/N) ? \n");
	scanf("%c", &ch1);
	while (ch1 == 'y') {
		do {
			printf("first file : ");
			std::getline(std::cin, firstfile);
		} while (firstfile.length() == 0);
		do {
			printf("second file : ");
			std::getline(std::cin, secondfile);
		} while (secondfile.length() == 0);

		printf("options: ");
		std::cin.getline(options, 20);

		for (int i = 0; i < 20; ++i)
			if (options[i] == '/')
				if (options[i + 1] == 'd') d = 1;
				else if (options[i + 1] == 'a') a = 1;
				else if (options[i + 1] == 'c') c = 1;

				else {
					char sw[20] = { 0 };
					for (int j = 0; i < 20; ++j, ++i)
						if (options[i] != ' ') sw[j] = options[i];
					printf("Invalid switch -'%s'\n", sw);
				}


				f1.open(firstfile);
				if (!f1.is_open())
					printf("first file not found!\n");
				f2.open(secondfile);
				if (!f2.is_open())
					printf("second file not found!\n");
				f1.seekg(0, std::ios_base::end);
				f2.seekg(0, std::ios_base::end);
				int size_of_first = f1.tellg();
				int size_of_second = f2.tellg();
				if (size_of_first != size_of_second)
					printf("files aren't same size\n");
				else {
					if (size_of_first == size_of_second) {
						f1.seekg(0, std::ios::beg);
						f2.seekg(0, std::ios::beg);
						int er;
						while (f1.good()) {
							ch1 = f1.get();
							ch2 = f2.get();
							if (c)
								if (tolower(ch1) != tolower(ch2)) {
									er = (int)f1.tellg() - 1;
									printf("Compare error at OFFSET %d \n", er);
									if (d) printf("File 1 = %d\n File 2 = %d\n", ch1, ch2);
									else printf("File 1 = %c\n File 2 = %c\n", ch1, ch2);
								}
								else;
							else if (ch1 != ch2) {
								er = (int)f1.tellg() - 1;
								printf("Compare error at OFFSET %d \n", er);
								if (d) printf("File 1 = %d\n File 2 = %d\n", ch1, ch2);
								else printf("File 1 = %c\n File 2 = %c\n", ch1, ch2);
							}
						}
					}
					f1.close();
					f2.close();
					printf("Compare more files (Y/N) ? \n");
					scanf("%c", &ch1);
				}
	}
}

void COPY(char* LINE) {

	std::string file = "";
	std::string newpath = "";
	std::string filename = "";
	WIN32_FIND_DATAA d;
	
	int i, y=strlen(LINE);
	for (i = 0; i < y; ++i)
		if (LINE[i] == '\"') break;

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
		else file += LINE[i];

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
		else newpath += LINE[i];

	HANDLE hfile = FindFirstFileA(newpath.c_str(), &d);
	if (hfile != INVALID_HANDLE_VALUE) {
		if (d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			i = file.length() - 1;
			int j = 0;
			for (; file[i] != '\\'; ++j, i--)
				filename += file[i];

			for (i = 0; i < j / 2; ++i) {
				char c = filename[i];
				filename[i] = filename[j - i - 1];
				filename[j - i - 1] = c;
			}
			newpath += "\\" + filename;
			//printf("%s %s %s\n", file, newpath, filename);
			if (CopyFileA(file.c_str(), newpath.c_str(), 1))
				printf("File copied successfully!");
			else {
				printf("Error: %d\n", GetLastError());
				printf("File could not be copied successfully");
			}
		} else {
			char r;
			printf("do you want to overwrite the specified file as distance? (y/n)\t");
			do {
				scanf("%c", &r);
			} while (r != 'y' && r != 'n');
			if (r == 'n') return;
			if (CopyFileA(file.c_str(), newpath.c_str(), 0))
				printf("File copied successfully!");
			else {
				printf("Error: %d\n", GetLastError());
				printf("File could not be copied successfully");
			}
		}
	}
	else {
		if (CopyFileA(file.c_str(), newpath.c_str(), 1))
			printf("File copied successfully!");
		else {
			printf("Error: %d\n", GetLastError());
			printf("File could not be copied successfully");
		}
	}
}

void DEL(char* LINE) {

	int i;
	char pat[1024];

	strcpy(pat, LINE);

	for (i = strlen(LINE) - 1; i >= 0 && LINE[i] != '\\'; i--) 
		pat[i] = 0;
	pat[i] = 0;

	WIN32_FIND_DATAA d;
	HANDLE hfile = FindFirstFileA(LINE, &d);

	if (hfile != INVALID_HANDLE_VALUE)
	{
		do
		{
			strcpy(pat + i, d.cFileName);
			if(DeleteFileA(pat))
				printf("Deleted sucessfully: %s\n", pat);
			else {
				printf("File isn't deleted (%d): %s\n", GetLastError(), pat);
			}
		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}
}

void DIR(char* LINE) {

	bool d = 0, l = 0, o = 0;

	WIN32_FIND_DATAA data;
	FILETIME ftLocal;
	SYSTEMTIME stCreate;
	int dir = 0, file = 0;
	INT64 size;
	INT64 totalsize = 0;
	char options[20];
	printf("options: \n");
	std::cin.getline(options, 20);

	{
		int i, l;
		for (i = 0, l = strlen(options); i < l; ++i) {
			if (options[i] == '/')
				if (options[i + 1] == 'd') d = 1;
				else if (options[i + 1] == 'l') l = 1;
				else if (options[i + 1] == 'o') o = 1;
				else {
					char c[20] = { 0 };
					for (int j = 0; i < 20; ++j, ++i)
						if (options[i] != ' ') c[j] = options[i];
					printf("Invalid switch -'%s'\n", c);
				}
		}

		for (i = 0, l = strlen(LINE); i < l; ++i)
			if (LINE[i] != ' ') break;
		if (i == l) {
			strcpy(LINE, PATH);
			LINE[strlen(LINE)] = '\\';
			LINE[strlen(LINE)] = '*';
			LINE[strlen(LINE)] = 0;
		}

	}

	HANDLE hfile = FindFirstFileA(LINE, &data);

	if (hfile != INVALID_HANDLE_VALUE) {

		if (d) {
			std::string filename[777];
			HANDLE hfile = FindFirstFileA(LINE, &data);
			if (hfile != INVALID_HANDLE_VALUE)
			{
				int max = 0;
				int i = 0;
				do {
					filename[i] = '[';
					filename[i] += data.cFileName;
					filename[i] += ']';
					i++;
					if (strlen(data.cFileName) > max)
						max = strlen(data.cFileName);
				} while (FindNextFileA(hfile, &data) != 0);
				for (int y = 0; y < i; y++)
				{
					if (l)
						for (int len = 0; len < filename[i].length(); ++len)
							filename[i][len] = tolower(filename[i][len]);
					printf("%-*s", max + 2, filename[y].c_str());
					if ((y + 1) % (120 / max) == 0)
						printf("\n");
				}
				printf("\n");
			}
			return;
		}

		if (o) {
			
			do {
				if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

					FileTimeToLocalFileTime(&data.ftCreationTime, &ftLocal);
					FileTimeToSystemTime(&ftLocal, &stCreate);
					printf("%02d/%02d/%d %02d:%02d:%02d",
						stCreate.wMonth, stCreate.wDay, stCreate.wYear,
						stCreate.wHour, stCreate.wMinute, stCreate.wSecond);
					printf("\t<DIR>\t\t");
					dir++;
					if (l)
						for (int len = 0; len < strlen(data.cFileName); ++len)
							data.cFileName[len] = tolower(data.cFileName[len]);
					printf("%s\n", data.cFileName);
				} } while (FindNextFileA(hfile, &data) != 0);
				
			hfile = FindFirstFileA(LINE, &data);
			do
			{
				if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					FileTimeToLocalFileTime(&data.ftCreationTime, &ftLocal);
					FileTimeToSystemTime(&ftLocal, &stCreate);
					printf("%02d/%02d/%d %02d:%02d:%02d",
						stCreate.wMonth, stCreate.wDay, stCreate.wYear,
						stCreate.wHour, stCreate.wMinute, stCreate.wSecond);
					size = data.nFileSizeHigh << 32;
					size += data.nFileSizeLow;
					printf("\t%15lld ", size);
					file++;
					totalsize += size;
					if (l)
						for (int len = 0; len < strlen(data.cFileName); ++len) 
							data.cFileName[len] = tolower(data.cFileName[len]);
					printf("%s\n", data.cFileName);
				}
				
			} while (FindNextFileA(hfile, &data) != 0);
			
			printf("   DIR = %8d \n", dir);
			printf("   FILE = %8d \n", file);
			printf("total files size =%8d \n", totalsize);
			return;
		}
	}

	do
	{
		FileTimeToLocalFileTime(&data.ftCreationTime, &ftLocal);
		FileTimeToSystemTime(&ftLocal, &stCreate);
		printf("%02d/%02d/%d %02d:%02d:%02d",
			stCreate.wMonth, stCreate.wDay, stCreate.wYear,
			stCreate.wHour, stCreate.wMinute, stCreate.wSecond);

		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("\t<DIR>\t\t");
			dir++;
		}
		else {
			size = data.nFileSizeHigh << 32;
			size += data.nFileSizeLow;
			printf("\t%15lld ", size);
			file++;
		}
		printf("%s\n", data.cFileName);
	} while (FindNextFileA(hfile, &data) != 0);
	FindClose(hfile);

	printf("   DIR = %8d \n", dir);
	printf("   FILE = %8d \n", file);
}

void EXIT(char* LINE) {

	strcpy(PATH, "WEWANTEXIT");
	// at main I'm checking for this change.

	/*another way to execute this command
	HANDLE Console = GetCurrentProcess();
	TerminateProcess(Console,0);
	*/
}

void FIND(char* LINE) {

	bool v = 1, n = 0, c = 0;
	char wrd[1024] = {};
	int i, st=0, j;

	for (i = 0; LINE[i] && LINE[i] != '"'; ++i) ;

	for (; LINE[i + 1] && LINE[i + 1] != '"'; ++i)
		wrd[st++] = LINE[i + 1];
	wrd[st] = 0;
	st = i+2;
	for (;LINE[st] &&  LINE[st] == ' '; ++st);
	for (j=0; st+j < strlen(LINE); ++j)
		LINE[j] = LINE[st+j];
	LINE[j] = 0;
	
	std::string cont = "";

	// the coming block (18 lines) for separated options line
	char options[20];
	printf("Options: ");
	std::cin.getline(options, 20);
	for (int i = 0; i < strlen(options); ++i) {
		if (options[i] == '/')
			if (options[i + 1] == 'v') v = 0;
			else if (options[i + 1] == 'n') n = 1;
			else if (options[i + 1] == 'c') c = 1;
			else {
				char c[20] = { 0 };
				for (int j = 0; i<20; ++j, ++i)
					if (options[i] != ' ') c[j] = options[i];
				printf("Invalid switch -'%s'\n", c);
				return;
			}
	}  /*block ends here*/

	char pat[1024];
	strcpy(pat, LINE);

	for (i = strlen(LINE) - 1 ; i >= 0 && LINE[i] != '\\'; i--) pat[i] = 0;
	
	WIN32_FIND_DATAA d;
	HANDLE hfile = FindFirstFileA(LINE, &d);

	if (hfile != INVALID_HANDLE_VALUE) {
		
		do {
			strcpy(pat + i+1, d.cFileName);
			std::fstream File;
			File.open(pat, std::fstream::in);
			if (!File.is_open()) continue;			
			int num = 0, cnt=0;
			if (!c) printf("---------- %s\n", pat);
			else printf("---------- %s", pat);
			while (getline(File, cont)) {
				++num;
				for (int i = 0, k, l = cont.length() - strlen(wrd); i < l+1; ++i) {
					for (k = 0; k < strlen(wrd); ++k)
						if (cont[i + k] != wrd[k])
							break;
					if (k == strlen(wrd)) {
						++cnt;
						if (v) 
							if (!c)
								if (n) printf("(%d) %s\n", num, cont.c_str());
								else printf("%s\n", cont.c_str());
						
						else
							if (!c)
								if (n) printf("(%d) %s\n", num, cont.c_str());
								else printf("%s\n", cont.c_str());
					
						break;
					}
				}
			}
			if (c) printf("    %d\n", cnt);
			File.close();
			printf("\n\n");

		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}

}

void HELP(char* LINE) {
	
	printf("\n");
	int i,l;
	for (i = 0, l = strlen(LINE);i < l;++i)
		if (LINE[i] != ' ') break;


	if (i==l) {

		printf("For more information on a specific command, type HELP command-name\n\n");

		printf("CD\n");
		printf("CHDIR\t\tDisplays the name of or changes the current directory.\n");
		printf("CLS\t\tClears the screen.\n");
		printf("CMD\t\tStarts a new instance of the Windows command interpreter.\n");
		printf("DIR\t\tDisplays a list of files and subdirectories in a directory.\n");
		printf("EXIT\t\tQuits the CMD.EXE program (command interpreter).\n");
		printf("HELP\t\tProvides Help information for Windows commands.\n");
		printf("MD\n");
		printf("MKDIR\t\tCreates a directory.\n");
		printf("PRINT\t\tPrints a text file.\n");
		printf("SYSTEMINFO\tDisplays machine specific properties and configuration.\n");
		printf("TASKLIST\tDisplays all currently running tasks including services.\n");
		printf("TITLE\t\tSets the window title for a CMD.EXE session.\n");
		printf("TYPE\t\tDisplays the contents of a text file.\n");
		
		
		printf("\nFor more help, think about it twice; there's no online-help :P\n\n");
		return;
	}
	
	for (int k = 0; LINE[k]; ++k)
		LINE[k] = toupper(LINE[k]);
	printf("%s", LINE);
	{ // scope for 'i' variable
		int i;
		for (i = 0; i < CMDS; ++i)
			if (strcmp(LINE, cmd[i]) == 0) {
				helps[i];
				break;
			}

		if (i == CMDS)
			printf("This command is not supported by the help utility.  Try \"%s / ? \".\n", LINE);
	}
}

void MD(char* LINE) {
	const size_t cSize = strlen(LINE) + 1;
	wchar_t wc[100];
	mbstowcs(wc, LINE, cSize);
	_wmkdir(wc);
}

void RD(char* LINE) {
	const size_t cSize = strlen(LINE) + 1;
	wchar_t wc[100];
	mbstowcs(wc, LINE, cSize);
	printf("done %d", _wrmdir(wc));
}

void RENAME(char* LINE) {

	std::string oldname = "";
	std::string newname = "";

	//for (int i = 0, x = 0, y = strlen(LINE); i < y; i++)


	int i, y = strlen(LINE);
	for (i = 0; i < y; ++i)
		if (LINE[i] == '\"') break;

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
		else oldname += LINE[i];

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;

	for (++i; i < y; ++i)
		if (LINE[i] == '\"') break;
		else newname += LINE[i];

	bool abs = 0;
	for (int i = 0; i < oldname.length(); ++i)
		if (oldname[i] == '\\') abs = 1;

	int c = oldname.length() - 1;
	for (; oldname[c] != '\\'; c--);
	std::string filename = "";

	for (int i = 0; i <= c; ++i)
		filename += oldname[i];

	for (int i=0;i<newname.length();++i)
		if (newname[i] == '\\') {
			printf("second parameter isn't proper, it should be name\n");
			return;
		}

	filename += newname;
	printf("%s %s\n", oldname.c_str(), filename.c_str());
	if (MoveFileA(oldname.c_str(), filename.c_str()))
		printf("File successfully renamed\n");
	else printf("Error renaming file\n");
}

void SORT(char* LINE) {
	char option[1024];
	std::vector<std::string> myvector;
	std::fstream file(LINE);
	std::cout << "Option :";
	std::cin.getline(option, sizeof(option));

	//****************************************
	//sort file in new file if option ="-o"
	if (strcmp(option, (char*)"-o") == 0)
	{
		std::cout << "Newpath :";
		char ss[1024];
		std::cin.getline(ss, sizeof(ss));

		std::ofstream f(ss, std::ios::out);
		std::string word;
		std::cout << myvector.empty() << "\n";
		while (getline(file, word))
		{
			std::cout << word << "\n";
			myvector.push_back(word);
		}
		std::cout << myvector.empty() << "\n";
		std::sort(myvector.begin(), myvector.end());
		for (int i = 0; i < myvector.size(); i++)
		{
			f << myvector[i] << "\n";
			std::cout << myvector[i] << "\n";
		}
		file.close();
		f.close();
		std::cout << "done\n";
	}
	//******************************************************

	//******************************************************
	//option -r
	else if (strcmp(option, (char*)"-r") == 0)
	{
		std::cout << "option ==-r";
		std::string word;
		std::cout << myvector.empty() << "\n";
		while (getline(file, word))
		{
			std::cout << word << "\n";
			myvector.push_back(word);
		}
		std::cout << myvector.empty() << "\n";
		std::sort(myvector.begin(), myvector.end());
		file.close();
		file.open(LINE, std::ios::out | std::ios::trunc);
		for (int i = myvector.size() - 1; i >= 0; i--)
		{
			file << myvector[i] << "\n";
			std::cout << myvector[i] << "\n";
		}
		file.close();
	}
	else if (!file.is_open())
		std::cout << "Unable to open file\n";
	else
	{
		std::cout << "is open\n";
		std::string word;
		std::cout << myvector.empty() << "\n";
		while (getline(file, word))
		{
			std::cout << word << "\n";
			myvector.push_back(word);
		}
		std::cout << myvector.empty() << "\n";
		std::sort(myvector.begin(), myvector.end());
		file.close();
		file.open(LINE, std::ios::out | std::ios::trunc);
		if (!file.is_open());
		std::cout << "trunc";
		for (int i = 0; i < myvector.size(); i++)
		{
			file << myvector[i] << "\n";
			std::cout << myvector[i] << "\n";
		}
		file.close();
	}
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
	SYSTEMTIME st;	
	tm * tt = new tm();
	char n;
	time(&ct);
	localtime_s(tt, &ct);
	printf("%d/%d/%d  %d:%d:%d\n", tt->tm_mday, tt->tm_mon + 1, tt->tm_year + 1900, tt->tm_hour, tt->tm_min, tt->tm_sec);
	do { 
		printf("New time? (y/N) :"); 
		scanf("%c", &n);
	} while (tolower(n) != 'y' &&tolower(n) != 'n');
	if (tolower(n) == 'y') {
		printf("Enter the new time: YYYY\MM\DD HH:MM:SS.MS\n");
		scanf("%d%d%d%d%d%d%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		if(SetSystemTime(&st))
			printf("Time's been changed successfully\n");
		else printf("");
	}
}

void TYPE(char* LINE) {

	std::string cont = "";

	WIN32_FIND_DATAA d;
	HANDLE hfile = FindFirstFileA(LINE, &d);
	char pat[1024];
	int i;
	for (i = 0; i < strlen(LINE) && LINE[i] != '\\'; ++i)
		pat[i] = LINE[i];

	if (hfile != INVALID_HANDLE_VALUE) {
		do {
			strcpy(pat + i, d.cFileName);
			std::fstream File;
			File.open(pat, std::fstream::in);
			while (getline(File, cont))
				printf("%s\n", cont.c_str());
			File.close();
			printf("\n\n");

		} while (FindNextFileA(hfile, &d) != 0);
		FindClose(hfile);
	}

}

/* COMMANDS end here */
