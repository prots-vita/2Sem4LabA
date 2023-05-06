#ifndef _dialog_h_
#define _dialog_h_
#include "func.h"

typedef struct str{
	char *info;
} str;

int dialog(const char **, int);

int Dfile(Tree **tree);

int Dadd(Tree **);

int Dfind(Tree **);

int Ddelete(Tree **);

int Dshow(Tree **);

int Dbypass(Tree **tree);

int Dtime(Tree **);

int DMyFunc(Tree **tree);

#endif
