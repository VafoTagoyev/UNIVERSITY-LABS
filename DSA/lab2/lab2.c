#include "stack_vector.h"

int main()
{
    char expression[50];
    printf("Enter the expression in infix form : ");
    scanf("%s", expression);

    InfixtoPrefix(expression);

    printf("\nThe expression in prefix form is : %s\n", expression);

    return 0;
}

