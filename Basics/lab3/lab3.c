/**********Найти самую длинную последовательность цифр в записи строки**********/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
 	char *s = NULL, *s1, *s2;
 	printf("Enter the string : ");
    scanf ("%m[^\n]", &s);
    printf("\n");
    s1 = (char *) malloc(1);
    s2 = (char *) malloc(1);
 	s1[0] = '\0';
 	s2[0] = '\0';
 	int n = 0, i;
 	for(i = 0; i < strlen(s); i++) {
 		if(isdigit(s[i])) {
 			s1[n] = s[i];
 			s1 = realloc(s1, n + 1);
 			n++;
 		} else {
 			if(strlen(s1) > strlen(s2)) {
 			    s2 = realloc(s2, n);
 			    strcpy(s2, s1);
 			}
 			n = 0;
 			s1[0] = '\0';
 		}
 	}

 	printf("The string which you entered = %s\n\n", s);
 	if(s1[0] != '\0' || s2[0] != '\0') {
 	    if(strlen(s1) > strlen(s2)) printf("The result = %s", s1);
 	    else printf("s2 = %s", s2);
 	}

	free(s1);
	free(s2);
	free(s);

	return 0;
}
