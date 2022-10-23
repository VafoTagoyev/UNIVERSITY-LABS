#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
 
typedef struct Item {
    char c;
    struct Item *next;
} Item;
 
int getList ( Item ** ) ;  // input string 
void putList ( const  char  *, Item * ) ;  // output line 
Item * modifyList ( Item * ) ;  // free memory 
Item * newString ( Item * ) ; 
Item * delSpace ( Item * ) ; 
Item * skipWord ( Item *);
Item *delWord(Item *);
 
int getList(Item **pptr)
{
    char buf[21], *str;
    Item head = {'*', NULL};
    Item *last = &head;
    int n, rc = 1;
    do{
        n = scanf("%20[^\n]", buf);
        if(n < 0){
            modifyList(head.next);
            head.next = NULL;
            rc = 0;
            continue;
        }
        if(n > 0){
            for(str = buf; *str != '\0'; ++str){
                last->next = (Item *)malloc(sizeof(Item));
                last = last->next;
                last->c = *str;
            }
            last->next = NULL;
        }
        else
            scanf("%*c");
    } while(n > 0);
    *pptr = head.next;
    return rc;
}
 
void putList(const char *msg, Item *ptr)
{
    printf("%s: \"", msg);
    for(; ptr != NULL; ptr = ptr->next)
        printf("%c", ptr->c);
    printf("\"\n");
}
 
Item *modifyList(Item *ptr)
{
    Item *tmp = NULL;
    while(ptr != NULL){
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    return ptr;
}
 
int main()
{ 
	clock_t starttime, endtime; // data type for calculating time 
	double totaltime; // variable for calculating total time 
    Item *ptr = NULL;
    while(puts("Input String Here:"), getList(&ptr)){
        putList("Entered", ptr);
        // calculating clock when modification starts..
		 
		starttime = clock(); 
		printf("start time : %f\n", (float)starttime);
        ptr = newString(ptr);
        putList("Result string", ptr);
        ptr = modifyList( ptr ) ; 
        
         //find the final time
        endtime = clock();
	    totaltime = ((double)(endtime - starttime)) / CLOCKS_PER_SEC; 
	    printf("endtime : %f\n", (float)endtime); 
    	printf("total time of execution = %f\n", totaltime);
    } 
    return  0 ; 
}
 
Item * newString ( Item * p ) 
{ 
    Item head =  { '*' , p } ; 
    Item * cur =  & head ,  * prev =  & head ;  // prev - for correct processing of the end of the list 
    // A list with a head element is used; so cur points 
    // to the list item before the one to be parsed 
    cur -> next = delSpace ( cur ->next);
    char first = (cur->next)->c;
    cur = skipWord(cur->next);
    prev = cur;
    cur = cur->next;
    if(cur)
        cur->c = ' ';
    while(cur && (cur->next = delSpace( cur -> next ) ) ) { 
        if ( cur ->next-> c == first ) { 
            cur = skipWord( cur -> next ) ; 
            prev = cur ;  // * save the last character of the word * / 
            cur = cur -> next ;  // * now cur points to the item after the word * / 
            if ( cur ) {  // there is some continuation of the list, cur points to
                     //whitespace list item //
                cur -> c =  ' ' ; 
            } 
        } 
        else 
            cur -> next = delWord ( cur -> next ) ; 
    } 
    // there may be an extra space at the end of the list line / 
    if ( prev -> next ) { 
        free ( prev -> next ) ; 
        prev -> next = NULL ; 
    } 
    return head.next;
}
 
Item *delSpace(Item *p)
{
    Item *tmp;
    while(p && (p->c == ' ' || p->c == '\t')){
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}
 
Item *skipWord(Item *p)
{
    while(p->next && p->next->c != ' ' && p->next->c != '\t')
        p = p->next;
    return p;
}
 
Item *delWord(Item *p)
{
    Item *tmp;
    while(p && p->c != ' ' && p->c != '\t'){
        tmp = p;
        p = p->next;
        free(tmp);
    }
    return p;
}
