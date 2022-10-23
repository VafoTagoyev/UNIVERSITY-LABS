#include <stdio.h>

int dialog(const char *msgs[], int N)
{
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
            puts("Wrong input, repeat please!");
            scanf("%*c");
        }
    }while(n == 0);
    return 1;
}

int D_Add(Table *ptab)
{
    int key, release, n, t, rc;
    char *info;
    const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

    printf("Enter key: --> ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    printf("Enter release number: --> ");
    scanf("%d", &release);
    printf("Enter info: ");
    info = getStr();

    rc = insert(ptab, key, release, info);
    printf("rc = %d\n", rc);
    free(info);

    printf("%s:\tkey: %d\n", errmsgs[rc], key);
    return 1;
}

int D_Find(Table *ptab)
{
    int key, release, n, t, rc;
    const char *errmsgs[] = {"Found key", "Not found key"};

    printf("Enter key: --> ");
    n = getInt(&key);
    if (n == 0)
        return 0;
    printf("Enter release number: --> ");
    scanf("%d", &release);
    rc = find(ptab, key, release);

    printf("%s:\tkey: %d\n", errmsgs[rc], key);
    return 1;
}

int D_Delete(Table *ptab)
{
    int key, n, release, rc;
    const char *errmsgs[] = {"Successfully removed", "Not found key"};

    printf("Enter key: --> ");
    n = getInt(&key);
    printf("Enter release number: --> ");
    scanf("%d", &release);
    if (n == 0)
        return 0;

    rc = delete(ptab, key, release);

    printf("%s:\tkey: %d\n", errmsgs[rc], key);
    return 1;
}

int D_Show(Table *ptab)
{
    printf("============ CURRENT TABLE ============\n");
    printf("index   |busy    |key     |rel     |information\n--------------------------------------\n");
    for(int i = 0; i < ptab->msize; ++i){
        printf("%-8d|%-8d|%-8d|%-8d| %s\n", i, ptab->item[i].busy, ptab->item[i].key, ptab->item[i].release, ptab->item[i].info);
    }
    return 1;
}
