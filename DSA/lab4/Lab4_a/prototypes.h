#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

int dialog(const char **, int);
int getInt(int *);
Node *search(Node *, int);
Node *minNode(Node *);
//Node *nextNode (Node *);
Node *insert(Node *, int);
Node *deleteNode(Node *, int);
void deltree(Node *);
Node *T_Add (Node *);
Node *T_Find(Node *);
Node *T_MinNode(Node *);
Node *T_Delete(Node *);
Node *T_ShowTable(Node *);
Node *T_ShowTree(Node *);
void ShowTree(Node *, int);
