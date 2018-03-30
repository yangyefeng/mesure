#ifndef _MEMENTO_H_
#define _MEMENTO_H_
# include <stdio.h>
# include <stdlib.h>

void get_breakpoint(void);
void restore_breakpoint(void);
void init_breakpoint(char *name,int id);
void get_open_database(char *basePath);
#endif
