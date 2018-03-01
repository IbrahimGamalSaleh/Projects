#ifndef _cmdfile_H
#define _cmdfile_H

#include <iostream>
#include <conio.h>
#include <console.h>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <ostream>
#include <regex>

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <utility>
#include <windows.h>

#define KW_LEN 14
#define CMDS 30

char command[1024];
char PATH[1024];
char DRIVE[26];

/* commands prototypes start here */
void ATTRIB(char*);
void CD(char*);
void CLS(char*);
void CMD(char*);
void COMP(char*);
void COPY(char*);
void DEL(char*);
void DIR(char*);
void EXIT(char*);
void FIND(char*);
void HELP(char*);
void MD(char*);
void RD(char*);
void RENAME(char*);
void SORT(char*);
void TASKLIST(char*);
void TITLE(char*);
void TIME(char*);
void TYPE(char*);
/* commands prototypes end here */

char cmd[CMDS][14] = { "ATTRIB", "CD", "CHDIR", "CLS", "CMD", "COMP", "COPY", "DEL"
, "DIR", "CHDIR", "EXIT", "FIND", "HELP", "MD", "MKDIR", "RD", "RMDIR", "RENAME", "SORT"
, "TASKLIST", "TITLE", "TIME", "TYPE"};

char drvs[][1024] = { "A:", "B:", "C:", "D:", "E:", "F:", "G:", "H:"
, "I:", "J:", "K:", "L:", "M:", "N:", "O:", "P:", "Q:", "R:", "S:",
"T:", "U:", "V:", "W:", "X:", "Y:", "Z:"};

void(*cmds[CMDS]) (char*) = { ATTRIB, CD, CD, CLS, CMD, COMP, COPY, DEL
, DIR, DIR, EXIT, FIND, HELP, MD, MD, RD, RD, RENAME, SORT
, TASKLIST, TITLE, TIME, TYPE};

#endif