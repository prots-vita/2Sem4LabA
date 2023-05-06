#include <stdio.h>
#include "func.h"
#include "dialog.h"
//#include <readline/readline.h>
#include "toFile.h"
#include <stdlib.h>
#include <time.h>

int getInt(int *pn){
	char *error = "";
	int n;
	do {
		puts(error);
		error = "Incorrect input, try again";
		n = scanf("%d", pn);
		if (n < 0)
			return 1;
		scanf("%*[^\n]");
		scanf("%*c");
	} while (n == 0);
	return 0;
}


int dialog(const char *msgs[], int N)
{
	const char *errmsg = "";
	int rc;
	int i, n;

	do{
		puts(errmsg);
		errmsg = "You are wrong. Repeat, please!";

		// вывод списка альтернатив
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		puts("Make your choice: --> ");

		n = getInt(&rc); // ввод номера альтернативы
		if (n == 1) // конец файла - конец работы
			rc = 0;
	} while (rc < 0 || rc >= N);

	return rc;
}

int Dadd(Tree **tree){
	char *str = readlineMy("Put branch key: ");
	if (str==0) return 1;
	printf("Put branch info: ");
	int elem;
	if (getInt(&elem)){
		return 1;
	}
	if (add(tree, str, elem)){
		free(str);
		printf("Duplicate key\n");
	} else {
		printf("OK\n");
	}
	return 0;
}


int Dfile(Tree **tree){
	char *file = "file.txt";
	FILE *fp;
	int elem, rel = 1;
	char *key = NULL;
	OpenRead(file, &fp);
       	while (1){
		if (Read(fp, &elem, &key)){
			if (add(tree, key, elem))
				free(key);
		} else {
			break;
		}
	}
	fclose(fp);
	return 0;
}


int Dfind(Tree **tree){
	char *str = readlineMy("Put key: ");
	if (str==0) return 1;
	Tree *preptr = NULL;
	Tree *ptr = *tree, *real;
	if (!(real = find(ptr, str, &preptr))){
		printf("Key was not found\n");
	} else {
		printf("Key was found: %d\n", real->info->info);
	}
	free(str);
	return 0;
}

int Dshow(Tree **tree){
	printf("-----Tree-----\n");
	show(*tree, 0);
	return 0;
}

int Ddelete(Tree **tree){
	char *str = readlineMy("Put key: ");
	if (str==0) return 1;
	if (delete(tree, str)){
		printf("Key was not found\n");
	} else {
		printf("Key was deleted\n");
	}
	free(str);
	return 0;
}

int Dbypass(Tree **tree){
	printf("--Bypass--\n");
	printf("elem/with out elem (1/-1): ");
	int ch;
	if (getInt(&ch)){
		return 1;
	}
	if (ch==1){
		char *str = readlineMy("Put key: ");
		if (str==0) return 1;
		bypass2(*tree, str);
		free(str);
	}
	else{
		bypass(*tree);
	}
	printf("\n\n");
	return 0;
}

int DMyFunc(Tree **tree){
	char *str = readlineMy("Put key: ");
	if (str==0) return 1;
	int high;
	Tree *to = MyFunc(*tree, str, &high);
	if (!to){
		printf("no elements\n");
	} else {
		printf("%s - key, %d - info", to->key, to->info->info);
	}
	free(str);
	return 0;
}

double randAddWith(Tree **tree, Str **key, int cnt){
	int arr[10000];
	for (int i = 0; i<10000; i++)
		arr[i] = rand()*rand();
	double first = clock();
	for (int i = 0; i<cnt; ){
		(*key)[i].info = arr_random();
		if (!add(tree, (*key)[i].info, arr[i]))
			i++;
		else
			free((*key)[i].info);
	}
	double last = clock();
	return (last-first)/(CLOCKS_PER_SEC);
	
}

double randAdd(Tree **tree, Str *key, int *arr, int cnt){
	double first = clock();
	for (int i = 0; i < cnt; ){
		if (!add(tree, key[i].info, arr[i]))
			i++;
	}
	double last = clock();
	return (last-first)/(CLOCKS_PER_SEC);
}

double randMy(Tree *tree, Str *key, int *high){
	int high2 = 0;
	double first = clock();
	for (int i = 0; i < 10000; ++i)
		MyFunc(tree, key[i].info, &high2);
	double last = clock();
	*high = high2;
	return (last-first)/(CLOCKS_PER_SEC);
}

double randDel(Tree **tree, Str *key){
	double first = clock();
	for (int i = 0; i < 10000; ++i)
		delete(tree, key[i].info);
	double last = clock();
	return (last-first)/(CLOCKS_PER_SEC);
}

double randFind(Tree *tree, Str *key){
	Tree *nt = NULL;
	double first = clock();
	for (int i = 0; i < 10000; ++i)
		find(tree, key[i].info, &nt);
	double last = clock();
	return (last-first)/(CLOCKS_PER_SEC);
}

int Dtime(Tree **){
	Tree *tree = NULL, *tree2 = NULL;
	int n = 10, k = 6, cnt = 10000, i, m, arr[cnt], high;
	FILE *fadd = fopen("add.txt", "w");
	FILE *ffind = fopen("find.txt", "w");
	FILE *fdel = fopen("del.txt", "w");
	FILE *fmy = fopen("my.txt", "w");
	FILE *fnum = fopen("num.txt", "w");
	FILE *fhigh = fopen("high.txt", "w");
	Str *key = malloc(cnt*sizeof(Str));
	Str *key2 = malloc(cnt*sizeof(Str));
	double randA, randD, randF, randM, randB;
	srand(time(NULL));
	while (n-- > 0){
		for(i = 0; i<cnt; i++)
			key2[i].info = arr_random();
		for (i = 0; i<10000; i++)
			arr[i] = rand()*rand();
		randB = randAddWith(&tree, &key, cnt);
		randM = randMy(tree, key2, &high);
		randF = randFind(tree, key2);
		randD = randDel(&tree, key2);

//		randA = randAdd(&tree2, key, arr, cnt);
		printf("%d high\n", high);
		fprintf(fhigh, "%d\n", high);
		printf("test #%d, number of nodes = %d:\n", 10 - n, (10 - n)*cnt);
		fprintf(fnum, "%d\n", (10-n)*cnt);
//		printf("	time add = %.8lf\n", randA);
		printf("	time add = %.8lf\n", randB);
		fprintf(fadd, "%.8lf\n", randB);
		printf("	time find = %.8lf\n", randF);
		fprintf(ffind, "%.8lf\n", randF);
		printf("	time My = %.8lf\n", randM);
		fprintf(fmy, "%.8lf\n", randM);
		printf("	time delete = %.8lf\n", randD);
		fprintf(fdel, "%.8lf\n", randD);
		
//		freeStr(key, cnt);
		freeStr(key2, cnt);
	}
	fclose(fhigh);
	fclose(fnum);
	fclose(fadd);
	fclose(ffind);
	fclose(fmy);
	fclose(fdel);
	delTree(&tree);
//	delTree(&tree2);
	free(key);
	free(key2);
	return 0;
}
