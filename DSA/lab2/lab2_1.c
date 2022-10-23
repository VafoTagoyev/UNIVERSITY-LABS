#include "stack_linkedlist.h"

int main()
{
    char str[100], output[100];

    printf("Enter your infix expression :");

    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    strrev(str);
    infix2prefix(str, output);
    // reverse the output to get prefix notation
    strrev(output);

    printf("Prefix form of you expression is : %s\n", output);

    return 0;
}
