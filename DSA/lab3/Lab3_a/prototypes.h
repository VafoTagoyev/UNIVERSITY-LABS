#include <stdio.h>

typedef struct Data{
    char *info;
    int busy;
    int key;
    int release;
}Data;

typedef struct Table{
    int msize;
    int csize;
    Data *item;
}Table;

int dialog(const char **, int);
int getInt(int *);
int hash(int);
void setValues(Table *);
int search(Table *, int, int);
int find(Table *, int, int);
int insert(Table *, int, int, char *);
int delete(Table *, int, int);
void delTable(Table *);
char *getStr();
int D_Add(Table *);
int D_Find(Table *);
int D_Delete(Table *);
int D_Show(Table *);
