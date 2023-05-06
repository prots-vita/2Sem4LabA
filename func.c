#include "func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char *readlineMy(char *s){
	printf("%s", s);
	char buf[81] = {0};
	char *res = NULL;
	int len = 0, n;
	do{
		n = scanf("%80[^\n]", buf);
		if (n<0){
			return NULL;
		} else if (n>0) {
			int chunk_len = strlen(buf);
			int str_len = len+chunk_len;
			res = realloc(res, str_len+1);
			memcpy(res+len, buf, chunk_len);
			len = str_len;
		} else {
			scanf("%*c");
		}
	} while (n>0);
	if (len>0) {
		res[len] = '\0';
	} else {
		res = calloc(1, sizeof(char));
	}
	return res;
}


Tree* getBranch(Tree *parent, char* value, int info){
	Tree* tmp = (Tree*) malloc(1*sizeof(Tree));
	tmp->left = tmp->right = NULL;
	tmp->key = value;
	tmp->info = malloc(1*sizeof(Info));
	tmp->info->info = info;
	return tmp;
}

int findPlace(Tree **ptr, Tree **preptr, char *elem){
	while (*ptr){
		*preptr = *ptr;
		if (strcmp((*ptr)->key, elem)==0) 
			return 1;
		if (strcmp((*ptr)->key, elem)<0)
			(*ptr) = (*ptr)->right;
		else
			(*ptr) = (*ptr)->left;
	}
	return 0;
}

int add(Tree **tree, char* elem, int info){
	Tree *ptr = *tree, *preptr = NULL, *par = NULL;
	if (findPlace(&ptr, &preptr, elem))
		return 1;
	ptr = getBranch(preptr, elem, info);
	if (preptr==NULL) 
		*tree = ptr;
	else if (strcmp(preptr->key, elem)>0)
		preptr->left = ptr;
	else
		preptr->right = ptr;
	return 0;
}

Tree* find(Tree *ptr, char* key, Tree **preptr){
	while (ptr){
		if (strcmp(ptr->key, key)==0)
			return ptr;
		(*preptr) = ptr;
		if (strcmp(ptr->key, key)>0)
			ptr = ptr->left;
		else 
			ptr = ptr->right;
	}
	return NULL;
}


Tree *findMin(Tree *ptr, Tree **preptr){
	if (!ptr)
		return NULL;
	while (ptr->left!=NULL){
		(*preptr) = ptr;
		ptr = ptr->left;
	}
	return ptr;
}

Tree *podTree(Tree *ptr){
	Tree *pod = NULL;
	if (ptr->left)
		pod = ptr->left;
	else
		pod = ptr->right;
	return pod;
}

Tree* findReal(Tree *ptr, Tree **preptr){
	Tree *real = NULL;
	if (!ptr->right || !ptr->left)
		real = ptr;
	else{
		(*preptr) = ptr;
		real = findMin(ptr->right, preptr);
	}
	return real;
}

int delete(Tree **tree, char* elem){
	Tree *par = NULL, *ptr = find(*tree, elem, &par), *real = NULL, *podr = NULL;
	if (!ptr)
		return 1;
	real = findReal(ptr, &par);
	podr = podTree(real);
	if (!par)
		*tree = podr;
	else{
		if (par->left && strcmp(par->left->key, real->key)==0)
			par->left = podr;
		else 
			par->right = podr;
	}
	free(ptr->key);
	ptr->key = real->key;
	ptr->info->info = real->info->info;
	free(real->info);
	free(real);
	return 0;

}

void show(Tree *tree, int level){
	int i = level;
	if (tree){
		show(tree->right, level+1);
		while (i-- > 0){
			printf("  ");
		}
		printf("%s\n", tree->key);
		show(tree->left, level+1);
	}
}

void delTree(Tree **tree){
	if (*tree){
		delTree(&((*tree)->left));
		delTree(&((*tree)->right));
		if ((*tree)->key) free((*tree)->key);
		if ((*tree)->info) free((*tree)->info);
		if (*tree) free(*tree);
	}
	*tree = NULL;
}

void bypass(Tree* tree) {
    if (tree) {
        bypass(tree->left);
        printf("%s ", tree->key);
        bypass(tree->right);
    }
}

int bypass2(Tree* tree, char *elem) {
    if (tree) {
        if (bypass2(tree->left, elem)) return 1;
	if (strcmp(tree->key, elem)>=0)
		return 1;
        printf("%s ", tree->key);
        if (bypass2(tree->right, elem)) return 1;
    }
    return 0;
}

int disp(char *s1, char *s2){
	int i1 = 0, i2 = 0, res = 0;
	while (s1[i1]!='\0' || s2[i2]!='\0'){
		if (s1[i1]!=s2[i2]){
			res = s1[i1]-s2[i2];
			return res;
		}
		i1++;
		i2++;
	}
	return res;
}

Tree *MyFunc(Tree *tree, char* elem, int *high){
	Tree *right = tree, *left = tree;
	int highright = 0, highleft = 0;
	if (!tree)
		return NULL;
	while (right->right){
		right = right->right;
		highright++;
	}
	while (left->left){
		left = left->left;
		highleft++;
	}
	if (highright>highleft)
		*high = highright;
	else 
		*high = highleft;
	int rightNum = disp(right->key, elem), leftNum = disp(left->key, elem);
//	printf("right key - %d, left key - %d, disp right - %d, disp left - %d\n", right->info->info, left->info->info, rightNum, leftNum);
	if (rightNum<0)
		rightNum *= -1;
	else 
		leftNum *= -1;
	if (rightNum>leftNum)
		return right;
	else 
		return left;

}

char* arr_random(){
	int len = 1+rand()%9;
	char *str = malloc((len+1)*sizeof(char));
	for (int i = 0; i<len; i++){
		str[i] = rand()%150+'!';
	}
	str[len] = '\0';
	return str;
}

void freeStr(Str *str, int len){
	for (int i = 0; i<len; i++){
		if (str[i].info!=NULL) free(str[i].info);
	}
	return;
}

int getElems(Tree *pretree, Tree *tree, char **one, char **two){
        if (pretree==NULL){
                return 1;
        }
        *one = pretree->key;
        *two = tree->key;
        return 0;
}

void toImport(Tree *pretree, Tree *tree, FILE *fo){
        char *one, *two;
        if (tree) {
                toImport(tree, tree->left, fo);
                if (!getElems(pretree, tree, &one, &two)){
                        fprintf(fo, "%s", one);
                        fprintf(fo, "->");
                        fprintf(fo, "%s \n", two);
                }
                toImport(tree, tree->right, fo);
        }
}

void import(Tree *tree){
	Tree *pretree = NULL;
        int level;
        FILE *fo = fopen("g.dot","w");
        fprintf( fo, "digraph Graf {\n");
        toImport(pretree, tree, fo);
        fprintf( fo, "}");
        fclose(fo);
}
