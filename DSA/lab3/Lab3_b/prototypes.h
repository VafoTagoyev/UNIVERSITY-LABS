#include <stdio.h>

typedef struct Item{
    char *info;
    int busy;
    int key;
    int release;
    int offset;
    int len;
}Item;

typedef struct Table{
    int SZ;
    int csize;
    Item *first;
    FILE *fd;
}Table;

int getInt(int *);
int dialog(const char **, int);
int search(Table *, int, int);
int find(Table *ptab, int, int);
char *findInfo(Table ptab, int, int);
int insert(Table *, int, int, char *);
int load (Table *, char *);
int create(Table *, char *, int);
int save(Table *);
int D_Add(Table *);
int D_Find(Table *);
int D_Load(Table *);
int D_Delete(Table *);
int D_Show(Table *);
int D_Save(Table *);
char *getStr();
void delTable(Table *);
