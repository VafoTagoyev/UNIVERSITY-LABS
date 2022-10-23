//	  |			   Для каждой строки сформировать новую строку,           |
//	  |				поместив в нее все слова исходной строки, 			  |
//	  |	начинающиеся и заканчивающиеся на ту же букву, что и первое слово |

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char *str = NULL;
    printf("Please enter the strings consecutivaly : \n");
    scanf ("%m[^\n]", &str);
    printf("\n\n");
    int n = strlen(str);
    char first = str[0];
    char last;
    int i;
    printf("Answer : ");
    for(i = 0; i < n; i++) {
        printf("%c", str[i]);
        if(str[i] == ' ') {
            last = str[i - 1];
            break;
        }
    }
    char *helper;
    helper = (char *)malloc(1);
    helper[0] = '\0';
    int k = 0, size = 1;
    i++;
    for(i; i < n; i++) {
        if(str[i] != ' ') {
            helper[k] = str[i];
            helper = realloc(helper, size + 1);
            k++;
            size++;
        }
        if(str[i] == ' ') {
            //printf("%s", helper);
            int l = strlen(helper);
            if(helper[0] == first && helper[l - 1] == last) {
                printf("%s ", helper);
            }
            k = 0;
            size = 1;
            helper = realloc(helper, size);
            helper[0] = '\0';
        }
    }
    int l = strlen(helper);
    if(helper[0] == first && helper[l - 1] == last) printf("%s ", helper);
    printf("\n\n");
    free(helper);
    free(str);

    return 0;
}
