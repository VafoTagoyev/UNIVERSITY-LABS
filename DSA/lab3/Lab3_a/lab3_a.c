#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "prototypes.h"
#include "dialog_functions.h"
#define MaxSize 10

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int main()
{
    Table table = {MaxSize, 0, (Data *) calloc (MaxSize, sizeof(Data))};
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};

    int rc;
    setValues(&table);
    while(rc = dialog(msgs, NMsgs)){
        if(!fptr[rc](&table))
            break;
    }
    printf("That is all bye!\n");
    delTable(&table);
    return 0;
}

int hash(int k)
{
    int h = k % MaxSize;
    return h;
}

void setValues(Table *ptab)
{
    if(ptab->csize == 0){
        for(int i = 0; i < MaxSize; ++i){
            ptab->item[i].busy = 0;
            ptab->item[i].key = 0;
            ptab->item[i].release = 0;
            ptab->item[i].info = NULL;
        }
    }
}

int search(Table *ptab, int k, int rel)
{
    int j = hash(k);
    int p = 1;          //Шаг перемешивание
    int n = 0;
    while (ptab->item[j].busy != 0 && n < ptab->msize) {
        if(ptab->item[j].busy == 1 && ptab->item[j].key == k && ptab->item[j].release == rel)
            return j;
        j = (j + p) % ptab->msize;
        n = n + 1;
    }
    return -1;
}

int insert(Table *ptab, int k, int rel, char *info)
{
    int j = hash(k);
    int p = 1;          //Шаг перемешивание
    int n = 0;
    int res = search(ptab, k, rel);

    if (res >= 0){
        rel++;
        return 1;
    }
    while (ptab->item[j].busy == 1 && n < ptab->msize){
        j = (j + p) % ptab->msize;
        n = n + 1;
    }

    if (n < ptab->msize) {
        ptab->item[j].key = k;
        ptab->item[j].busy = 1;
        ptab->item[j].release = rel;
        ptab->item[j].info = strdup(info);
        return 0;
    }
    return 2;
}

int find(Table *ptab, int k, int rel)
{
    int res = search(ptab, k, rel);
    if(res < 0)
        return 1;
    return 0;
}

int delete(Table *ptab, int k, int rel)
{
    int res = search(ptab, k, rel);
    if (res < 0)
        return 1;
    else{
        ptab->item[res].busy = -1;
        ptab->item[res].release = -1;
        ptab->item[res].info = NULL;
        return 0;
    }
}

void delTable(Table *ptab)
{
    for(int j = 0; j < ptab->msize; ++j)
        free(ptab->item);
    ptab->csize = 0;
}

char *getStr()
{
    char *ptr = (char *) malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf(" %80[^\n]", buf);
        if (n == 0)
            scanf("%*c");
        else {
            len += strlen(buf);
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n < 1);
    return ptr;
}
