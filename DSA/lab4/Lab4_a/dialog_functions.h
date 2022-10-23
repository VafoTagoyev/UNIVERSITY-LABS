#include <stdio.h>

int dialog(const char *msgs[], int N)
{
    const char *errmsg = "";
	int rc,i,n;
	do{
		puts(errmsg);
		errmsg = "You are wrong! Repeat, please!";
		for (i = 0; i < N; ++i)
            puts(msgs[i]);
		puts("Make your choice:-->");
		n = getInt(&rc);
		if(n==0)
            rc = 0;
	} while (rc < 0 || rc >= N);
	return rc;
}

int getInt(int *a)
{
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0)
            return 0;
        else if (n == 0){
            printf("Wrong input! Repeat, please!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

Node *T_Add(Node *root)
{
	int k, n = 1;
	char *info;
	printf("Enter key:-->");
	n = getInt(&k);
	if (search(root, k) == 0) {
		root = insert(root, k);
		puts("KEY ADDED");
	}
	else puts("ERROR! KEY EXISTS");
	return root;
}

Node *T_Find(Node *root)
{
	Node *x = NULL;
	int k, n = 1;
	printf("Enter key:-->");
	n = getInt(&k);
	x = search(root, k);
	if (x != 0) {
		puts("KEY FOUND");
		printf("%d \n", x->data);
	}
	else  puts("KEY NOT FOUND");
	return root;
}

Node *T_Delete(Node *root)
{
	Node *x = NULL;
	int k, n = 1;
	printf("Enter key:-->");
	n = getInt(&k);
	x = search(root, k);
	if (x != 0) {
		root = deleteNode(root, k);
		puts("KEY DELETED");
	}
	else  puts("KEY NOT FOUND");
	return root;
}

Node *T_MinNode(Node *root)
{
	Node *x;
    if (root == NULL)
        return 0;
	x = minNode(root);
	puts("MIN KEY FOUND");
	printf("%d \n", x->data);
	return root;
}

Node *T_ShowTable(Node *root)
{
	if (root == NULL)
        return 0;
    T_ShowTable(root->right);
    printf("\n");
    printf("  ");
    printf("%d\n", root->data);
    T_ShowTable(root->left);
    return root;
}

Node *T_ShowTree(Node *root)
{
    ShowTree(root, 0);
    return root;
}
