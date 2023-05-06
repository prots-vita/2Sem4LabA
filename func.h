#ifndef _func_h_
#define _func_h_

typedef struct Str{
	char *info;
} Str;

typedef struct Info{
	int info;
} Info;

typedef struct Tree{
	char* key;
	struct Tree *left, *right;
	Info *info;
} Tree;

int findPlace(Tree **, Tree **, char *);

char *readlineMy(char *s);

int add(Tree **, char *, int);

int bypass2(Tree* tree, char *elem);

Tree* find(Tree *, char *, Tree **);

int delete(Tree **, char *);

void show(Tree *, int);

void delTree(Tree **);

void bypass(Tree *);

void import(Tree *tree);

char* arr_random();

void freeStr(Str *, int);

Tree *MyFunc(Tree *, char *, int *);

#endif
