#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "prototypes.h"
#include "dialog_functions.h"

int main()
{
	Node *root = NULL;
	int rc, N = 7;
	const char *msgs[] = {"0. Quit","1. Add","2. Find","3. Find min","4. Delete","5. Show table","6. Show tree"};
	Node *(*fptr[])(Node*) = {NULL, T_Add, T_Find, T_MinNode, T_Delete, T_ShowTable, T_ShowTree};
	while(rc = dialog(msgs, N))
	    root = fptr[rc](root);
	printf("That's all, good bye!\n");
	deltree(root);
	return 0;
}

/*Node *nextNode(Node *x)
{
    Node *ptr = NULL;
    if (x == NULL)
        return 0;
    if (x->right != NULL){
        ptr = minNode(x->right);
        return ptr;
    }
    ptr = x->parent;
    while (ptr != NULL && x == ptr->right){
        x = ptr;
        ptr = x->parent;
    }
    return ptr;
}*/

Node *search(Node *root, int key)
{
    Node *ptr = root;
    while (ptr != NULL){
        if (ptr->data == key)
            return ptr;
        else if (ptr->data > key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    return 0;
}

Node *insert(Node *root, int key)
{
    Node *ptr, *x, *par;
    ptr = root;
    par  = 0;
    x = (Node *) calloc (1, sizeof(Node));
    if (ptr == NULL){
        x->data = key;
        ptr = x;
        return ptr;
    }
    while (ptr != NULL){
        par = ptr;
        if (ptr->data > key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    if (par->data > key){
        par->left = x;
        x->data = key;
    }
    else {
        par->right = x;
        x->data = key;
    }
    return root;
}

Node *minNode(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = minNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void deltree(Node *p)
{
	if (p != NULL) {
		deltree(p->left);
		deltree(p->right);
		free(p);
	}
}

void ShowTree(Node *root, int flag)
{
    flag += 5;
	if (root == NULL)
        return;
    ShowTree(root->right, flag);
    printf("\n");
    for(int i = 0; i < flag; ++i)
        printf(" ");
    printf("%d\n", root->data);
    ShowTree(root->left, flag);
}
