#ifndef _helpfile_H
#define _helpfile_H

#define KW_LEN 14
#define CMDS 30

/* HELPS prototypes start here*/
void HELP_ATTRIB(void);
void HELP_CD(void);
void HELP_CLS(void);
void HELP_CMD(void);
void HELP_COMP(void);
void HELP_COPY(void);
void HELP_DEL(void);
void HELP_DIR(void);
void HELP_EXIT(void);
void HELP_FIND(void);
void HELP_HELP(void);
void HELP_MD(void);
void HELP_RD(void);
void HELP_RENAME(void);
void HELP_SORT(void);
void HELP_TASKLIST(void);
void HELP_TITLE(void);
void HELP_TIME(void);
void HELP_TYPE(void);
/* HELPS prototypes end here*/

void(*helps[CMDS]) (void)= { HELP_ATTRIB, HELP_CD, HELP_CD, HELP_CLS, HELP_CMD, HELP_COMP, HELP_COPY, HELP_DEL
, HELP_DIR, HELP_EXIT, HELP_FIND, HELP_HELP, HELP_MD, HELP_MD, HELP_RD, HELP_RD, HELP_RENAME
, HELP_SORT, HELP_TASKLIST, HELP_TITLE, HELP_TIME, HELP_TYPE };

#endif