#include <stdio.h>
#include <malloc.h>

// structure for giving row of matrix
typedef struct Line {

int n; // number of elements in row of matrix
int *a; // array elements

} Line;

// structure for giving Matrix
typedef struct Matrix {

int lines; // number of rows in matrix
Line *matr; // array of row in matrix

} Matrix;

// prototips of functions
int getInt(int *); // input of integer number
int input(Matrix *a); // input of Matrix
void output(const char *msg, Matrix a); // output of Matrix
void erase(Matrix *a); // freeing used memory
Matrix duplicatenumber(Matrix *r,Matrix a); // finding main result
int findingduplicates(int a[], int m); // finding duplicates

// main function
int main()
{
    Matrix matr = {0, NULL}; // original array
    Matrix res = {0, NULL};

    if(input(&matr) == 0){ // input of matrix
        printf("%s\n", "End of file occured");
        return 1;
    }
    output("Source matrix", matr);
    output("Result matrix", duplicatenumber(&res, matr));
    erase(&matr);
    erase(&res); // freeing memory
    return 0;
}

// input integer number
// if an error is detected, the input is lost
// function returns 1 if the input is valid
// and 0 on detection of a file cons
int getInt(int *a)
{
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0) // end of file detected
            return 0;
        if (n == 0){ // invalid character detected - error
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

// input of matrix
// if an error is detected, the input is lost function returns 1 if the input is valid
// if the end of the file is found in the middle of the input - you need to free the allocated memory
int input(Matrix *rm)
{
    const char *pr = "";
    int m, i, j;
    int *p;
    // first we will input number of rows
    do
    {
        printf("%s\n", pr);
        printf("Enter number of lines: --> ");
        pr = "You are wrong; Repeat, please!";
        if(getInt(&m) == 0)
            return 0; // file crash detected; memory was not allocated
    } while(m < 1);
    rm->lines = m;

    // allocate memory for an array of structures - matrix rows
    rm->matr = (Line *)calloc(m, sizeof(Line));

    for(i = 0; i < rm->lines; i++)
    {  // now for each row of the matrix we enter the number of column
        pr = "";
        do{
            printf("%s\n", pr);
            printf("Enter number of items in line %d: --> ", i + 1);
            pr = "You are wrong; Repeat, please!";
            if(getInt(&m) == 0){
                rm->lines = i;
                erase(rm);
                return 0;
            }
        } while(m < 1);
        rm->matr[i].n = m;
        // and allocate the necessary memory for the elements of the string
        p = (int *)malloc(sizeof(int)* m);
        rm->matr[i].a = p;

        // now you can enter the elements of this row of the matrix
        printf("Enter items for matrix line #%d: \n", i + 1);
        for(j = 0; j < m; ++j, ++p)
            if(getInt(p) == 0){
                // freeing allocated memory
                rm->lines = i + 1; // allocate memory for both the current and -th line
                erase(rm);
                return 0;
            }
    }
    return 1;
}

// function of output
void output(const char *msg, Matrix a)
{
    int i, j;
    int *p;
    printf("%s:\n", msg);
    for (i = 0; i < a.lines; ++i){
        p = a.matr[i].a;
        for (j = 0; j < a.matr[i].n; ++j, ++p)
            printf("%d ", *p);
        printf("\n");
    }

}
// clearing memory function
void erase(Matrix *a)
{
    int i;
    for (i = 0; i < a->lines; ++i)
        free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}

// function for finding main result
Matrix duplicatenumber(Matrix *res, Matrix pm)
{
    res->lines = pm.lines;

    res->matr = (Line *)calloc(pm.lines, sizeof(Line));

    for(int i = 0; i < pm.lines; i++) {
        int index = 0;
        int size = 1;
        res->matr[i].a = (int *)malloc(size * sizeof(int));
        for(int j = 0; j < pm.matr[i].n - 1; j++) {
            int t = 1;
            for(int k = j + 1; k < pm.matr[i].n; k++) {
                if(pm.matr[i].a[j] == pm.matr[i].a[k]) t++;
            }
            if(t == 2) {
                res->matr[i].a[index] = pm.matr[i].a[j];
                res->matr[i].n = size;
                index++;
                size++;
                res->matr[i].a = realloc(res->matr[i].a, size * sizeof(int));
            }
        }
    }
    return *res;
}
