//	  |	Удалить числа, которые лежат в заданном диапазоне значений, |
//	  |		   и вывести последовательность удалённых чисел         |
//    |                   отсортированном виде						|

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for(i = 0; i <  n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

void bubbleSort(int arr[], int n) {
    int i, j;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

int main() {
    FILE* file1;
    int n, i = 0;
    char c;
    int *data = (int *)malloc(1 * sizeof(int));
    printf("SELECT INPUT MODE  : \n");
    printf("1. From Console\n");
    printf("2. From File\n");
    printf("3. Random generate data\n");
    scanf("%d", &n);
    int k = 2, m;
    switch(n) {
        case 1:
            printf("Please enter the elements : ");
            while(1) {
                scanf("%d%c", &data[i], &c);
                if(c == '\n') break;

                data = (int *)realloc(data, k * sizeof(int));
                k++;
                i++;
            }
            break;
        case 2:
            file1 = fopen("input.txt", "r");
            if (!file1){
                printf("File can't be read\n");
                exit(-1);
            }
            while(fscanf(file1, "%d", &data[i]) == 1) {
                data = (int *)realloc(data, k * sizeof(int));
                k++;
                i++;
            }
            break;
        case 3:
            printf("INPUT COUNT OF NUMBER : ");
            scanf("%d", &m);
            srand(time(0));
            for(i; i < m; i++) {
                data[i] = rand() % 1000;
                data = (int *)realloc(data, k * sizeof(int));
                k++;
            }
            break;
        default : printf("WRONG NUMBER!");
    }

    if(n == 1) i = i + 1;

    printf("\nARRAY ELEMENTS : ");
    for(int p = 0; p < i; p++) {
        printf("%d ", data[p]);
    }
    printf("\n");

    printf("\nSELECT MODIFY DATA MODE: \n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Own task\n");
    scanf("%d", &n);
    int s, a, b;
    switch(n) {
        case 1:
            bubbleSort(data, i);
            printf("\nArray elements after bubble sort : ");
            for(int p = 0; p < i; p++) {
                printf("%d ", data[p]);
            }
            printf("\n");
            break;
        case 2:
            selectionSort(data, i);
            printf("\nArray elements after selection sort : ");
            for(int p = 0; p < i; p++) {
                printf("%d ", data[p]);
            }
            printf("\n");
            break;
        case 3:
            printf("Input diapazone:\n");
            scanf("%d", &a);
            scanf("%d", &b);
            printf("\nARRAY ELEMENTS IN THIS DIAPAZONE : ");
            for(s = 0; s < i; s++) {
                if(data[s] >= a && data[s] <= b) {
                    printf("%d ", data[s]);
                }
            }
            printf("\n\n");
            break;
        default: printf("WRONG NUMBER!");
    }
    free(data);

    return 0;
}
