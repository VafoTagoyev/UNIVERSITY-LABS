#include <stdio.h>

int dialog(const char *msgs[], int N){
    char *errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong, repeat please!";
        for(i = 0; i < N; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");

        n = getInt(&rc);
        if(n==0)
            rc = 0;
    }while(rc < 0 || rc >= N);
    return rc;
}

int getInt(int *a)
{
    int n;
    do{
        n = scanf("%d", a);
        if(n<0)
            return 0;
        else if(n==0){
            puts("Error input, repeat please!");
            scanf("%*c");
        }
    }while(n == 0);
    return 1;
}

int D_Add(Table *ptab)
{
    int k, rel, rc, n;
    char *info = NULL;
    const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

    printf("Enter key: -->");
    n = getInt(&k);
    if(n == 0)
        return 0;

    printf("Enter release number: -->");
    scanf("%d", &rel);
    printf("Enter info: ");
    info = getStr();
    if (info == NULL)
        return 0;

    rc = insert(ptab, k, rel, info);
    free(info);

    printf("%s:\tkey: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Load(Table *ptab)
{
    int SZ;
    char *fname = NULL;
    printf("Enter file name: --> ");
    fname = getStr();
    if(fname == NULL)
        return 0;
    if (load(ptab, fname) == 0){
        printf("Enter possible vector size: -->");
        if (getInt(&SZ) == 0)
            return 0;
        create(ptab, fname, SZ);
    }
    free(fname);
    return 1;
}

int D_Find(Table *ptab)
{
    char *info = NULL;
    int k, rel, n, i;
    puts("Enter key: -->");
    n = getInt(&k);
    if(n == 0)
        return 0;

    puts("Enter release number: -->");
    scanf("%d", &rel);
    info = findInfo(*ptab, k, rel);
    if(info){
        printf("key = %d, release = %d, info = \"%s\"\n", k, rel, info);
        free(info);
    }
    else
        printf("Item %d %d was not found\n", k, rel);
    return 1;
}

int D_Delete(Table *ptab)
{
    int k, n, rel, rc;
    const char *errmsgs[] = {"Successfully removed", "Not found key"};

    printf("Enter key: --> ");
    n = getInt(&k);
    printf("Enter release number: --> ");
    scanf("%d", &rel);
    if (n == 0)
        return 0;

    rc = delete(&ptab, k, rel);

    printf("%s:\tkey: %d\n", errmsgs[rc], k);
    return 1;
}

int D_Show(Table *ptab)
{
    printf("============ CURRENT TABLE ============\n");
    printf("index    |busy     |key     |rel     |information\n--------------------------------------------------\n");
    for(int i = 0; i < ptab->SZ; ++i){
        printf("%-8d|%-8d|%-8d|%-8d| %s\n", i, ptab->first[i].busy, ptab->first[i].key, ptab->first[i].release, ptab->first[i].info);
    }
    return 1;
}
