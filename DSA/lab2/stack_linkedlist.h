#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OPERATORS 7

struct node {
    int data;
    struct node *next;
};

struct node *top = NULL;

/* Operators and its precedence */
char precedence[OPERATORS][2] = { {'(', 0}, {'+', 1}, {'-', 1},
                                  {'*', 2}, {'/', 2}, {'%', 2},
                                  {')', 3}
                                };

/* create a node with given data */
struct node* createNode(int data)
{
    struct node *ptr = (struct node *) malloc(sizeof (struct node));
    ptr->data = data;
    ptr->next = NULL;
}

  /* Push the given data into the stack */
void push(int data)
{
    struct node *ptr = createNode(data);
    if (top == NULL)
    {
        top = ptr;
        return;
    }
    ptr->next = top;
    top = ptr;
}

/* Pop the top element from the stack */
int pop()
{
    struct node *ptr;
    int data;

    if (top == NULL)
        return -1;

    ptr = top;
    top = top->next;
    data = ptr->data;
    free (ptr);

    return (data);
}

/* get the index of the given operator */
int getIndex(int data)
{
    int i;
    for (i = 0; i < OPERATORS; i++)
    {
        if (data == precedence[i][0])
            return i;
    }
}

/* string reverse operation */
void strrev(char str[])
{
    int i = 0, j = 0;
    char ptr[100];
    while (str[i] != '\0')
        i++;
    for (i = i-1; i >=0; i--)
    {
        ptr[j] = str[i];
        j++;
    }
    ptr[j] = '\0';
    strcpy(str, ptr);
}

/* infix to prefix conversion */
void infix2prefix(char infix[], char postfix[])
{
    int i, j = 0, data;
    int index1, index2;

    for (i = 0; i < strlen(infix); i++)
    {
        /* if the given i/p is operand, place in output buffer */
        if (tolower(infix[i]) >= 'a' && tolower(infix[i] <= 'z'))
            postfix[j++] = infix[i];
        else if (infix[i] == '(')
        {
        /*
         * if the i/p is open brace, pop the elements one
         * by one until we encounter close brace
         */
            data = pop();
            while (data != ')' && data != -1)
            {
                postfix[j++] = data;
                data = pop();
            }
        }
        else if (infix[i] == ')')
        {
            /* if the i/p is close brace, push it into stack */
            push(infix[i]);
        }
        else
        {
            data = pop();
            if (data == -1)
            {
                /* stack is empty.. so, push current i/p */
                push(infix[i]);
                continue;
            }
            else if (data == ')')
            {
                /*
                 * if stack top element is close brace, then
                 * push current input to stack
                 */
                push(data);
                push(infix[i]);
                continue;
            }
            index1 = getIndex(data);
            index2 = getIndex(infix[i]);

            /* Precedence manipulation b/w stack operator and current i/p */

            while (precedence[index1][1] > precedence[index2][1])
            {
                postfix[j++] = data;
                data = pop();
                if (data == -1 || data == ')')
                {
                    push(infix[i]);
                    break;
                }
                index1 = getIndex(data);
            }
            if (data != -1)
            {
                push(data);
                push(infix[i]);
            }

        }
    }
    /* Pop the remaining data from stack after all processing*/
    while (1)
    {
        if ((data = pop()) == -1)
            break;
            postfix[j++] = data;
    }
    postfix[j] = '\0';
}
