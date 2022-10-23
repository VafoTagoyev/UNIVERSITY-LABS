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
    Table table = {0, 0, NULL, NULL};
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};
    int rc;

    if (D_Load(&table) == 0)
        return 1;
    while(rc = dialog(msgs, NMsgs))
        if(!fptr[rc](&table))
            break;

    //D_Save(&table);

    printf("That's all. Bye!\n");
    delTable(&table);
    return 0;
}

/*int D_Save(Table *ptab)
{

}*/

int hash(int k)
{
    int h = k % MaxSize;
    return h;
}

int search(Table *ptab, int k, int rel)
{
    int j = hash(k);
    int p = 1;          //Шаг перемешивание
    int n = 0;
    while (ptab->first[j].busy != 0 && n < ptab->SZ) {
        if(ptab->first[j].busy == 1 && ptab->first[j].key == k && ptab->first[j].release == rel)
            return j;
        j = (j + p) % ptab->SZ;
        n = n + 1;
    }
    return -1;
}

int insert(Table *ptab, int k, int rel, char *str)
{
    int j = hash(k);
    int p = 1;          //Шаг перемешивание
    int n = 0;
    int res = search(ptab, k, rel);

    if(res >= 0){
        rel++;
        return 1;
    }
    if(ptab->csize >= ptab->SZ)
        return 2;

    while (ptab->first[j].busy == 1 && n < ptab->SZ) {
        j = (j + p) % ptab->SZ;
        n = n + 1;
    }

    if(n < ptab->SZ){
        ptab->first[ptab->csize].key = k;
        ptab->first[ptab->csize].busy = 1;
        ptab->first[ptab->csize].release = rel;
        ptab->first[ptab->csize].info = strdup(str);
        ptab->first[ptab->csize].len = strlen(str) + 1;

        fseek(ptab->fd, 0, SEEK_END);
        ptab->first[ptab->csize].offset = ftell(ptab->fd);


        fwrite(str, sizeof(char), ptab->first[ptab->csize].len, ptab->fd);
        ++(ptab->csize);
        return 0;
    }
}

int delete(Table *ptab, int k, int rel)
{
    int res = find(ptab, k, rel);
    if (res < 0)
        return 1;
    else{
        ptab->first[res].busy = -1;
        ptab->first[res].release = -1;
        ptab->first[res].info = NULL;
        return 0;
    }
}

int find(Table *ptab, int k, int rel)
{
    int res = search(ptab, k, rel);
    if(res < 0)
        return -1;
    return 1;
}

char *findInfo(Table ptab, int k, int rel)
{
    char *info = NULL;
    int i = find(&ptab, k, rel);
    if (i >= 0){
        info = (char *)malloc(ptab.first[i].len);
        fseek(ptab.fd, ptab.first[i].offset, SEEK_SET);
        fread(info, sizeof(char), ptab.first[i].len, ptab.fd);
    }
    return info;
}

int load(Table *ptab, char *fname)
{

    ptab->fd = fopen(fname, "r+b");
    if (ptab->fd == NULL)
        return 0;

    fread(&ptab->SZ, sizeof(int), 1, ptab->fd);
    ptab->first = (Item *)calloc(ptab->SZ, sizeof(Item));
    fread(&ptab->csize, sizeof(int), 1, ptab->fd);
    fread(ptab->first, sizeof(Item), ptab->csize, ptab->fd);

    return 1;
}

int create(Table *ptab, char *fname, int sz)
{
    ptab->SZ = sz;
    ptab->csize = 0;
    ptab->fd = fopen(fname, "w+b");
    if (ptab->fd != 0){
        ptab->first = NULL;
        return 0;
    }

    ptab->first = (Item *)calloc(ptab->SZ, sizeof(Item));
    fwrite(&ptab->SZ, sizeof(int), 1, ptab->fd);
    fwrite(&ptab->csize, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->SZ, ptab->fd);
    return 1;
}

int save(Table *ptab)
{
    fseek(ptab->fd, sizeof(int), SEEK_SET);
    fwrite(&ptab->csize, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->csize, ptab->fd);
    fclose(ptab->fd);
    ptab->fd = NULL;
    return 1;
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

void delTable(Table *ptab)
{
    for(int j = 0; j < ptab->SZ; ++j)
        free(ptab->first);
    ptab->csize = 0;
}
