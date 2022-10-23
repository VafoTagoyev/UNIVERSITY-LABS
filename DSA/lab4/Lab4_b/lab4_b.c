#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ncurses.h>
#define T 2

typedef struct Node{
    int n;                     //Number of keys
    int nS;                    //Number of sons in knot
    int key[2*T-1];            //Array of values of keys
    struct Node *ptr[2*T];     //Pointers on affiliated knots
    struct Node *parent;       //Pointer on parent knot
    char *info[2*T-1];
    bool leaf;                 //Leaf or not leaf
    int kprev;                 //Number of prev key
}Node;

Node *root = NULL; //корень дерева

int getint(int *);
char *getstring();
Node * CreateNode();
void insert_to_node(int, Node *, char *);
void PrintNode(Node *, int);
void Split(Node *);
Node * NodeKeyMin(Node *);
void PrintMinimum(void);
Node * NodeKeyMax(Node *);
void PrintMaximum(void);
void NumberPrevPlus();
void NumberPrevMinus();
void PrintTree(void);
Node * TreeSearch(int, Node *);
Node * SearchPlace(int);
Node *NodeForSplit(Node *);
void NodeInsert(int, char *);
void AddKey(void);
void GetTextFile(void);
void SearchKey(void);
void SearchKeyNext(void);
Node * NodeKeyNext(int);
void PrintSequential(void);
void PrintRevSequential(void);
void removeFromNode(int, Node *);
void lconnect(Node *, Node *);
void rconnect(Node *, Node *);
void repair(Node *);
void removeLeaf(int, Node *);
void remove_(int, Node *);
void delete_key(int);
void DeleteKey();
int Menu ();

int getint(int *a)
{
    int n;
    do{
        n=scanf("%d",a);
        if (n<0)
            return 0;
        if (n==0){
           printf("%s\n","Repeat input");
           scanf("%*c",0);
        }

      }while (n==0);
    return 1;
}

char *getstring()
{
	char *p = (char*)malloc(1);
	char buf[51];
	int n, len = 0;
	*p = '\0';
	do
	{
		n = scanf("%50[^\n]", buf, 51);
		if (n<0)
		{
			free(p);
			p = NULL;
			continue;
		}
		if (n == 0)
			scanf("%*c");
		else
		{
			len += strlen(buf);
			p = (char*)realloc(p, len + 1);
			strcat(p, buf);
		}
	} while (n>0);
	return p;
}

Node * CreateNode()
{
    Node * node;
    node = (Node*)calloc(1, sizeof(Node));
    for(int i=0;i<2*T;i++)
        node->ptr[i]=NULL;
    return node;
}

void insert_to_node(int key, Node *node, char *info)
{
    if (key<node->key[0])
    {
        for (int j=node->n; j>0; j--)
        {
            node->key[j]=node->key[j-1];
            node->info[j]=node->info[j-1];
        }
        if (node->leaf!=true)
        {
            for (int j=node->n+1; j>0; j--)
            {
                node->ptr[j]=node->ptr[j-1];
                node->ptr[j]->parent=node;
            }
        }
        node->key[0]=key;
        node->info[0]=info;
    }
    else
    {
        for (int i=0; i<node->n-1; i++)
        {
            if (key>node->key[i] && key<node->key[i+1])
            {
                for (int j=node->n; j>i+1; j--)
                {
                    node->key[j]=node->key[j-1];
                    node->info[j]=node->info[j-1];
                }
                if (node->leaf!=true)
                {
                    for (int j=node->n+1; j>i+1; j--)
                    {
                        node->ptr[j]=node->ptr[j-1];
                        node->ptr[j]->parent=node;
                    }
                }
                node->key[i+1]=key;
                node->info[i+1]=info;
                break;
            }
        }
    }
    if (key>node->key[node->n-1])
    {
        node->key[node->n]=key;
        node->info[node->n]=info;
    }
    node->n=node->n+1;
    node->kprev=node->n;
}

void PrintNode(Node *node, int space)
{
    printf("\n");

    for (int i=0; i<space; i++)
        printf(" ");
    for (int i=0; i<node->n; i++)
        printf(" key=%d, info=%s; ", node->key[i], node->info[i]);
    printf("\n");
}

void Split(Node *node)
{
    Node *s, *r, *z;
    if (node->parent==NULL)
    {
        r=root;
        s=CreateNode();
        s->ptr[0]=r;
        s->parent=NULL;
        s->n=0;
        s->kprev=s->n;
        s->nS=1;
        s->leaf=false;

        root=s;
        r->parent=s;
    }
    z=CreateNode();
    for(int i=0; i<T-1; i++)
    {
        z->key[i]=node->key[i+T];
        z->info[i]=node->info[i+T];

    }
    z->n=T-1;
    z->kprev=z->n;
    if (node->leaf!=true)
    {
        for(int i=0; i<T; i++)
        {
            z->ptr[i]=node->ptr[i+T];
            z->ptr[i]->parent=z;
        }
        z->leaf=false;
        z->nS=T;
    }
    else
    {
        z->leaf=true;
        z->nS=0;
    }

    insert_to_node(node->key[T-1], node->parent, node->info[T-1]);

    for(int i=0; i<node->parent->n; i++)
    {
        if (node->key[T-1]==node->parent->key[i])
        {
            node->parent->ptr[i+1]=z;
            node->parent->ptr[i+1]->parent=node->parent;
            z->parent=node->parent;
            node->parent->nS=node->parent->nS+1;
        }
    }
    node->n=T-1;
    node->kprev=node->n;
}

Node *NodeKeyMin(Node *node)
{
    while (node->leaf==false)
        node=node->ptr[0];
    return node;
}

void PrintMinimum()
{
    Node *node;
    if (root)
    node = NodeKeyMin(root);
    printf("\nMinimum differenced key : ");
    PrintNode(node, 0);
}

Node * NodeKeyMax(Node *node)
{
    while (node->leaf==false)
        node=node->ptr[node->n];
    return node;
}

void PrintMaximum(void) //В программе не используется
{
    Node *node;
    if (root)
        node=NodeKeyMax(root);
    printf("\nMaximum of keys: ");
    PrintNode(node, 0);
}

void NumberPrevPlus()
{
    Node *node;
    int t;
    if(root)
    {
        node = NodeKeyMin(root);
        while(1)
        {
            if (node->leaf==true)
            {
                node->kprev=node->n;
                if (node->key[node->n-1]==NodeKeyMax(root)->key[NodeKeyMax(root)->n-1])
                    break;

                node=node->parent;
                t=0;
            }
            if (node->leaf!=true)
            {
                if (node->kprev==node->n)
                {
                    node=node->parent;
                    t=0;
                }
                else
                {
                    if (t==1)
                        node=node->ptr[node->kprev];
                    if (t==0)
                    {
                        node->kprev=node->kprev+1;
                        node=node->ptr[node->kprev];
                        t=1;
                    }
                }
            }
        }
    }
}

void NumberPrevMinus()
{
    Node *node;
    int t;
    if(root)
    {
        node=NodeKeyMax(root);
        while(2!=1)
        {
            if (node->leaf==true)
            {
                node->kprev=0;
                if (node->key[0]==NodeKeyMin(root)->key[0])
                    break;

                node=node->parent;
                t=0;
            }
            if (node->leaf!=true)
            {
                if (node->kprev==0)
                {
                    node=node->parent;
                    t=0;
                }
                else
                {
                    if (t==1)
                        node=node->ptr[node->kprev];
                    if (t==0)
                    {
                        node->kprev=node->kprev-1;
                        node=node->ptr[node->kprev];
                        t=1;
                    }
                }
            }
        }
    }
}

void PrintTree(void)
{
    Node *node;
    int t=2, space=0;
    if(root)
    {
        node=root;
        if (node->kprev!=0)
        NumberPrevMinus();
        while (2!=1)
        {
            if (node->leaf==true){
                if (node->kprev==0)
                    PrintNode(node, space);
                node->kprev=node->n;
                if (node==NodeKeyMax(root))
                    break;
               node=node->parent;
                t=0;
                space=space-2;
            }
            if (node->leaf!=true)
            {
                if (t==2)
                {
                    PrintNode(node, space);
                    node=node->ptr[node->kprev];
                    t=1;
                    space=space+2;
                }
                else
                {
                    if (node->kprev==node->n)
                    {
                        node=node->parent;
                        t=0;
                        space=space-2;
                    }
                    else
                    {
                        if (t==1)
                        {
                            if (node->kprev==0)
                                PrintNode(node, space);
                            node=node->ptr[node->kprev];
                            space=space+2;
                        }
                        if (t==0)
                        {
                            node->kprev=node->kprev+1;
                            node=node->ptr[node->kprev];
                            t=1;
                            space=space+2;
                        }
                    }
                }
            }
        }
    }
    else
        printf ("\nNo tree");
}

Node * TreeSearch(int key, Node *node)
{
    if (node!=NULL){
        if (node->leaf==false){
            int i;
            for (i=0; i<(2*T-1); i++){
                if (node->key[i]!=0) {
                    if(key==node->key[i])
                        return node;
                    if ((key<node->key[i])){
                        return TreeSearch(key, node->ptr[i]);
                        break;
                    }
                } else break;
            }
            return TreeSearch(key, node->ptr[i]);
        } else {
            for(int j=0; j<(2*T-1); j++)
                if (key==node->key[j])
                    return node;
            return NULL;
        }
    } else return NULL;
}

Node * SearchPlace(int ikey)
{
    Node *p=root;
    while (p->leaf==false){ //выбор ребенка до тех пор, пока узел не будет являться листом
        if ((ikey>p->key[p->n-1])) {
            p=p->ptr[p->n]; //перенаправляем к самому последнему ребенку, если цикл не "сломался"
        } else {
            for (int i=0; i<(p->n); i++){ //перебираем все ключи
                if (ikey<p->key[i]){
                    p=p->ptr[i];
                    break;
                }
            }
        }
    }
    return p;
}

Node *NodeForSplit(Node *p)
{
    if (p->n==2*T-1)
    {
        if (p!=root)
        {
            if (p->parent->n==2*T-1)
                p=p->parent;
        }
        return p;
        p=NodeForSplit(p);
    }
    return p;
}

void NodeInsert(int ikey, char *sInfo)
{
    Node *node;
    if (root==NULL)
    {
        Node *newRoot = CreateNode();
        newRoot->key[0]=ikey;
        newRoot->info[0]=sInfo;
        for(int j=1; j<(2*T-1); j++) newRoot->key[j]=0;
        for (int i=0; i<(2*T); i++) newRoot->ptr[i]=NULL;
        newRoot->n=1;
        newRoot->kprev=newRoot->n;
        newRoot->nS=0;
        newRoot->leaf=true;
        newRoot->parent=NULL;
        root=newRoot;
    }
    else
    {
        Node *p;
        node = TreeSearch(ikey, root);
        if (node)
            printf("\n Dubble key. Key was not added. \n");
        else
        {
            p=SearchPlace(ikey);
            while(p->n==2*T-1)
            {
                p=NodeForSplit(p);
                Split(p);
                p=SearchPlace(ikey);
            }
            insert_to_node(ikey, p, sInfo);
        }
    }
}

void AddKey(void)
{
    int  iKey;
    char *sInfo;
    Node *node=NULL;
    if (root!=NULL && root->kprev==0)
        NumberPrevPlus();
    printf("\nEnter key: ");
    getint(&iKey);

    sInfo=(char*)malloc(sizeof(char));
    printf("\nEnter info: ");
    do
    {
        sInfo = getstring();
    }while(0==sInfo[0]);   //строка должна быть непустой!
    NodeInsert(iKey, sInfo);  //заносим в дерево
    printf("Node added");
}






//ввод данных из текстового файла
//Ключ 1
//Информация 1
//Ключ 2
//......
void GetTextFile()
{
    char filename[256];
    char line[256], *inf;
    int  key, c;
    Node *node, *p;

    if (root!=NULL && root->kprev==0)
        NumberPrevPlus();
    printf ("\nInput file name: "); //запрашиваем имя файла
    fgets(filename, 256, stdin);
    if (filename[0])    //если имя введено
    {
        FILE* file = fopen (filename, "r"); //открываем

        if (file)     //если открыто
        {
            while(2!=1)    //бесконечный цикл
            {
                c=0;
                if (fgets(line, 256, file)) //читаем строку с ключом
                {
                    if (line[strlen(line)-1] == 0x0a)
                    line[strlen(line)-1] = 0;//удаляем последний код 0ah
                    key=atoi(line);
                    if (fgets(line, 256, file)) //читаем строку с Info
                    {
                        if (line[strlen(line)-1] == 0x0a)
                        line[strlen(line)-1] = 0;//удаляем последний код 0ah
                        inf=(char*)malloc(sizeof(char));
                        strcpy(inf, line);

                        NodeInsert(key, inf); //добавляем узел;

                    }
                    else
                        break;
                }
                else
                    break;
                }
            fclose (file);   //закрываем файл
            printf ("Success.");
        }
        else
            printf ("Error. File not found.");
    }
    else
    printf("Reenter file name.");
}

void SearchKey(void)
{
    int  iKey;
    Node *node;

    if (root)      //проверим на существование дерева
    {
        printf("\nEnter key: "); //введем ключ
        getint(&iKey);

        node = TreeSearch(iKey, root); //ищем узел с ключом
        if (node)
        {
            for (int i=0; i<node->n; i++)
                if (iKey==node->key[i])
                    printf("\n key=%d, info=%s \n", node->key[i], node->info[i]);
        }
        else
            printf("Key not found");
    }
    else
        printf ("\nNo tree");
}

Node * NodeKeyNext(int key)
{
    Node *node;
    if (root)
    {
        node=TreeSearch(key, root);
        if (node)
        {
            for (int i=0; i<node->n; i++)
            {if (key==node->key[i] && i!=node->n-1 && node->leaf==true)
                return node;

                if (key==node->key[i] && node->leaf==false)
                    return node->ptr[i+1];

                if (key==node->key[i] && i==node->n-1 && node->leaf==true && node!=NodeKeyMax(root))
                {if (node->key[i]<node->parent->key[0])
                    return node->parent;
                    for (int j=0; j<node->parent->n-1; j++)
                    {
                        if (node->key[i]>node->parent->key[j] && node->key[i]<node->parent->key[j+1])
                            return node->parent;
                    }
                    if (node->key[i]>node->parent->key[node->parent->n-1])
                    {
                        do
                        {
                            node=node->parent;
                        } while (key >= node->parent->key[0]);
                        return node->parent;
                    }
                }
                if (key==node->key[i] && i==node->n-1 && node==NodeKeyMax(root))
                    printf("\n Is't the last element \n");
            }
        }
        else
            printf("Key not found");
    }
    else
        printf("No Tree");
}

//Вывод ключей по порядку
void PrintSequential(void)
{
    Node *node;
    int t;

    if (root)
    {
        node=NodeKeyMin(root);
        if (root->kprev!=0)
        NumberPrevMinus();
        while(1)
        {
            if (node->leaf==true)
            {  for (int i=0; i<=node->n-1; i++)
                {   printf("\n key=%d, info=%s", node->key[i], node->info[i]);
                    node->kprev=node->kprev+1;
                }
                if (node->key[node->kprev-1]==NodeKeyMax(root)->key[NodeKeyMax(root)->n-1])
                    break;

                node=node->parent;
                t=0;
            }

            if (node->leaf!=true)
            {
                if (node->kprev==node->n)
                {
                    node=node->parent;
                    t=0;
                }
                else
                {
                    if (t==1)
                        node=node->ptr[node->kprev];
                    if (t==0)
                    {
                        printf("\n key=%d, info=%s", node->key[node->kprev], node->info[node->kprev]);

                        node->kprev=node->kprev+1;
                        node=node->ptr[node->kprev];
                        t=1;

                    }
                }
            }
        }
    }
    else
        printf("\n No Tree");
}

// Вывод ключей в обратном порядке
void PrintRevSequential(void)
{
    Node *node;
    int t;

    if (root)
    {
        node=NodeKeyMax(root);
        if (root->kprev!=root->n)
            NumberPrevPlus();

        while(1)
        {
            if (node->leaf==true)
            {  for (int i=node->n-1; i>=0; i--)
                {   printf("\n key=%d, info=%s", node->key[i], node->info[i]);
                    node->kprev=node->kprev-1;
                }
                if (node->key[node->kprev]==NodeKeyMin(root)->key[0])
                    break;

                node=node->parent;
                t=0;
            }

            if (node->leaf!=true)
            {
                if (node->kprev==0)
                {
                    node=node->parent;
                    t=0;
                }
                else
                {
                    if (t==1)
                        node=node->ptr[node->kprev];
                    if (t==0)
                    {
                        printf("\n key=%d, info=%s", node->key[node->kprev-1], node->info[node->kprev-1]);

                        node->kprev=node->kprev-1;
                        node=node->ptr[node->kprev];
                        t=1;
                    }
                }
            }
        }
    }
    else
        printf("\n No Tree");
}

//Удаление
void removeFromNode(int key, Node *node)
{
    for (int i=0; i<node->n; i++){
        if (node->key[i]==key){
            for (int j=i; j<node->n; j++) {
                node->key[j]=node->key[j+1];
                node->info[j]=node->info[j+1];
                node->ptr[j]=node->ptr[j+1];
            }
            node->key[node->n-1]=0;
            node->ptr[node->n-1]=node->ptr[node->n];
            node->ptr[node->n]=NULL;
            break;
        }
    }
    node->n--;
}

void lconnect(Node *node, Node *othernode){
    if (node==NULL) return;
    for (int i=0; i<=(othernode->n-1); i++){
        node->key[node->n]=othernode->key[i];
        node->info[node->n]=othernode->info[i];
        node->ptr[node->n]=othernode->ptr[i];
        node->n=node->n+1;
        node->kprev=node->n;
    }
    node->ptr[node->n]=othernode->ptr[othernode->n];
    for (int j=0; j<=node->n; j++){
        if (node->ptr[j]==NULL) break;
        node->ptr[j]->parent=node;
    }
    free(othernode);
}

void rconnect(Node *node, Node *othernode){
    if (node==NULL) return;
    for (int i=0; i<=(othernode->n-1); i++){
        node->key[node->n]=othernode->key[i];
        node->info[node->n]=othernode->info[i];
        node->ptr[node->n+1]=othernode->ptr[i+1];
        node->n=node->n+1;
        node->kprev=node->n;
    }
    for (int j=0; j<=node->n; j++){
        if (node->ptr[j]==NULL) break;
        node->ptr[j]->parent=node;
    }
    free(othernode);
}

//Метод починки узла
void repair(Node *node){
    if ((node==root)&&(node->n==0)){
        if (root->ptr[0]!=NULL){
            root->ptr[0]->parent=NULL;
            root=root->ptr[0];
        } else {
            free(root);
        }
         return;
    }
    Node *ptr=node, *p;
    int k1;
    int k2;
    int positionSon;
    Node *parent=ptr->parent;
    for (int j=0; j<=parent->n; j++){
        if (parent->ptr[j]==ptr){
            positionSon=j; //позиция узла по отношению к родителю
            break;
        }
    }
    //если ptr-первый ребенок (самый левый)
    if (positionSon==0){
        insert_to_node(parent->key[positionSon], ptr, parent->info[positionSon]);
        lconnect(ptr, parent->ptr[positionSon+1]);
        parent->ptr[positionSon+1]=ptr;
        parent->ptr[positionSon]=NULL;
        removeFromNode(parent->key[positionSon], parent);
        if(ptr->n==2*T-1){
            p=ptr;
            while(p->n==2*T-1)
        {
         p=NodeForSplit(p);
         Split(p);
         p=ptr;
        }
        } else
            if (parent->n<=(T-2)) repair(parent);
    } else {
        //если ptr-последний ребенок (самый правый)
        if (positionSon==parent->n){
            insert_to_node(parent->key[positionSon-1], parent->ptr[positionSon-1], parent->info[positionSon-1]);
            lconnect(parent->ptr[positionSon-1], ptr);
            parent->ptr[positionSon]=parent->ptr[positionSon-1];
            parent->ptr[positionSon-1]=NULL;
            removeFromNode(parent->key[positionSon-1], parent);
            Node *temp=parent->ptr[positionSon];
            if(ptr->n==2*T-1){
                p=ptr;
                while(p->n==2*T-1)
                {
                  p=NodeForSplit(p);
                  Split(p);
                  p=ptr;
                }
            } else
            if (parent->n<=(T-2)) repair(parent);
        } else { //если ptr имеет братьев справа и слева
            insert_to_node(parent->key[positionSon], ptr, parent->info[positionSon]);
            lconnect(ptr, parent->ptr[positionSon+1]);
            parent->ptr[positionSon+1]=ptr;
            parent->ptr[positionSon]=NULL;
            removeFromNode(parent->key[positionSon], parent);
            if(ptr->n==2*T-1){
                p=ptr;
                while(p->n==2*T-1)
                {
                  p=NodeForSplit(p);
                  Split(p);
                  p=ptr;
                }
            } else
            if (parent->n<=(T-2)) repair(parent);
        }
    }
}

//Метод удаления ключа из листа
void removeLeaf(int key, Node *node){
    if ((node==root)&&(node->n==1)){
        removeFromNode(key, node);
        root->ptr[0]=NULL;
        free(root);
        root=NULL;
        return;
    }
    if (node==root) {
        removeFromNode(key, node);
        return;
    }
    if (node->n>(T-1)) {
        removeFromNode(key, node);
        return;
    }
    Node *ptr=node;
    int k1;
    int k2;
    int position;
    int positionSon;
    int i;
    for (int i=0; i<=node->n-1; i++){
        if (key==node->key[i]) {
            position=i; //позиция ключа в узле
            break;
        }
    }
    Node *parent=ptr->parent;
    for (int j=0; j<=parent->n; j++){
        if (parent->ptr[j]==ptr){
            positionSon=j; //позиция узла по отношению к родителю
            break;
        }
    }
    //если ptr-первый ребенок (самый левый)
    if (positionSon==0){
        if (parent->ptr[positionSon+1]->n>(T-1)){ //если у правого брата больше, чем t-1 ключей
            k1=parent->ptr[positionSon+1]->key[0]; //k1 - минимальный ключ правого брата
            k2=parent->key[positionSon]; //k2 - ключ родителя, больше, чем удаляемый, и меньше, чем k1
            insert_to_node(k2, ptr, parent->info[positionSon]);
            removeFromNode(key, ptr);
            parent->key[positionSon]=k1; //меняем местами k1 и k2
            parent->info[positionSon]=parent->ptr[positionSon+1]->info[0];
            removeFromNode(k1, parent->ptr[positionSon+1]); //удаляем k1 из правого брата
        } else { //если у правого <u>единственного</u> брата не больше t-1 ключей
            removeFromNode(key, ptr);
            if (ptr->n<=(T-2)) repair(ptr);
        }
    } else {
        //если ptr-последний ребенок (самый правый)
        if (positionSon==parent->n){
            //если у левого брата больше, чем t-1 ключей
            if (parent->ptr[positionSon-1]->n>(T-1)){
                Node *temp=parent->ptr[positionSon-1];
                k1=temp->key[temp->n-1]; //k1 - максимальный ключ левого брата
                k2=parent->key[positionSon-1]; //k2 - ключ родителя, меньше, чем удаляемый и больше, чем k1
                insert_to_node(k2, ptr, parent->info[positionSon-1]);
                removeFromNode(key, ptr);
                parent->key[positionSon-1]=k1;
                parent->info[positionSon-1]=temp->info[temp->n-1];
                removeFromNode(k1, temp);
            } else { //если у <u>единственного</u> левого брата не больше t-1 ключей
                removeFromNode(key, ptr);
                if (ptr->n<=(T-2)) repair(ptr);
            }
        } else { //если ptr имеет братьев справа и слева
            //если у правого брата больше, чем t-1 ключей
            if (parent->ptr[positionSon+1]->n>(T-1)){
                k1=parent->ptr[positionSon+1]->key[0]; //k1 - минимальный ключ правого брата
                k2=parent->key[positionSon]; //k2 - ключ родителя, больше, чем удаляемый и меньше, чем k1
                insert_to_node(k2, ptr, parent->info[positionSon]);
                removeFromNode(key, ptr);
                parent->key[positionSon]=k1; //меняем местами k1 и k2
                parent->info[positionSon]=parent->ptr[positionSon+1]->info[0];
                removeFromNode(k1, parent->ptr[positionSon+1]); //удаляем k1 из правого брата
            } else {
                //если у левого брата больше, чем t-1 ключей
                if (parent->ptr[positionSon-1]->n>(T-1)){
                    Node *temp=parent->ptr[positionSon-1];
                    k1=temp->key[temp->n-1]; //k1 - максимальный ключ левого брата
                    k2=parent->key[positionSon-1]; //k2 - ключ родителя, меньше, чем удаляемый и больше, чем k1
                    insert_to_node(k2, ptr, parent->info[positionSon-1]);
                    removeFromNode(key, ptr);
                    parent->key[positionSon-1]=k1;
                    parent->info[positionSon-1]=temp->info[temp->n-1];
                    removeFromNode(k1, temp);
                } else { //если у обоих братьев не больше t-1 ключей
                    removeFromNode(key, ptr);
                    if (ptr->n<=(T-2)) repair(ptr);
                }
            }
        }
    }
}

//Метод удаления из произвольного узла
void remove_(int key, Node *node){
    Node *ptr=node;
    int position; //номер ключа
    int i;
    for (int i=0; i<=node->n-1; i++){
        if (key==node->key[i]) {
            position=i;
            break;
        }
    }
    int positionSon; //номер сына по отношению к родителю
    if (ptr->parent!=NULL){
        for(int i=0; i<=ptr->parent->n; i++){
            if (ptr->ptr[i]==ptr){
                positionSon==i;
                break;
            }
        }
    }
    //находим наименьший ключ правого поддерева
    ptr=ptr->ptr[position+1];
    int newkey=ptr->key[0];
    char *newinfo;
    newinfo=ptr->info[0];
    while (ptr->leaf==false) ptr=ptr->ptr[0];
    //если ключей в найденном листе не больше 1 - ищем наибольший ключ в левом поддереве
    //иначе - просто заменяем key на новый ключ, удаляем новый ключ из листа
    if (ptr->n>(T-1)) {
        newkey=ptr->key[0];
        newinfo=ptr->info[0];
        removeFromNode(newkey, ptr);
        node->key[position]=newkey;
        node->info[position]=newinfo;
    } else {
        ptr=node;
        //ищем наибольший ключ в левом поддереве
        ptr=ptr->ptr[position];
        newkey=ptr->key[ptr->n-1];
        newinfo=ptr->info[ptr->n-1];
        while (ptr->leaf==false) ptr=ptr->ptr[ptr->n];
        newkey=ptr->key[ptr->n-1];
        newinfo=ptr->info[ptr->n-1];
        node->key[position]=newkey;
        node->info[position]=newinfo;
        if (ptr->n>(T-1)) removeFromNode(newkey, ptr);
        else {
            //если ключей не больше, чем t-1 - перестраиваем
            removeLeaf(newkey, ptr);
        }
    }
}

//Основной метод удаления
void delete_key(int key){
    Node *ptr=root;
    int position;
    int positionSon;
    int i;
    if (TreeSearch(key, ptr)==NULL) {
        return;
    } else {
        //ищем узел, в котором находится ключ для удаления
        for (i=0; i<=ptr->n-1; i++){
            if (ptr->key[i]!=0) {
                if(key==ptr->key[i]) {
                    position=i;
                    break;
                } else {
                    if ((key<ptr->key[i])){
                        ptr=ptr->ptr[i];
                        positionSon=i;
                        i=-1;
                    } else {
                        if (i==(ptr->n-1)) {
                            ptr=ptr->ptr[i+1];
                            positionSon=i+1;
	                    i=-1;
                        }
                    }
                }
            } else break;
        }
    }
    if (ptr->leaf==true) {
        if (ptr->n>(T-1)) removeFromNode(key,ptr);
        else removeLeaf(key, ptr);
    } else remove_(key, ptr);
}

//Удаление ключа
void DeleteKey()
{
    int key;
    if (root)
    {
        printf("\n Input key \n");
        getint(&key);
        if (TreeSearch(key, root)!=NULL)
        {
            delete_key(key);
            printf("\n Key is removed \n");
        }
        else
            printf ("\n Key not found \n");
    }
    else
        printf("\n No tree \n");
}

int Menu () //вывод меню
{
    int c, n = 0;

    printf("0. Exit.\n1. Add.\n2. Delete.\n");
    printf("3. Search.\n4. Print in sequential order.\n");
    printf("5. Print in reversed order.\n6. Get tree from file.\n");
    printf("7. Print TREE.\n8. Print the element with min difference from specified key.\n");
    printf("Enter menu item: ");

    n = getint(&c);
    while (n == 1 && (c<0 || c>8))
        {
        printf("\nIncorrect! Reenter: ");
        n = getint(&c);
        }
    return c;
}

void freeTree(Node *ptr){
    for(int i = 0; i < 2 * T; i++)
        free(ptr->ptr[i]);
    free(ptr);
}

int main()
{
    while (1)
    {
        switch (Menu())    //вывод меню и получение кода выбора
        {
            case 1:
                AddKey();   //добавление ключа
                break;
            case 2:
                DeleteKey();  //удаление ключа
                break;
            case 3:
                SearchKey();  //поиск ключа
                break;
            case 4:
                PrintSequential(); //последовательный вывод
                break;
            case 5:
                PrintRevSequential();//вывод в обратном порядке
                break;
            case 6:
                GetTextFile();  //ввод из текстового файла
                break;
            case 7:
                PrintTree();  //вывод в виде дерева
                break;
            case 8:
                PrintMinimum();
                break;
            case 0:  //выход
                return 0;
        }
        printf ("\nPress any key to continue.\n");
    }
    freeTree(root);     //освободим память
    return 0;
}
