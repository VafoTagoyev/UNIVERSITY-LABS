#include <iostream>
#include "header.h"

using namespace std;

const char *msgs[] = {"0. Quit", "1. Add", "2. Show", "3. Reverse"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

namespace header {
    int dialog(const char *msgs[], int N)
    {
        const char *errmsg = "";
        int rc;
        int i, p;
        do{
            puts(errmsg);
            errmsg = "You are wrong, repeat please!";
            for(i = 0; i < N; ++i)
                puts(msgs[i]);
            puts("Make your choice: --> ");

            p = getInt(&rc);
            if(p==0)
                rc = 0;
        }while(rc < 0 || rc >= N);
        return rc;
    }

    int getInt(int *a)
    {
        int n;
        do{
            n = scanf("%d", a);
            if(n<0)
                return 0;
            else if(n==0){
                puts("Wrong input, repeat please!");
                scanf("%*c");
            }
        }while(n == 0);
        return 1;
    }

    int getRowNum()   // function for taking number of rows in sparse matrix
    {
        const char* error_message = "";
        int m;
        do {
            cout << error_message << std::endl;
            std::cout << "Enter number of rows: ";
            error_message = "You are wrong! Please, repeat!";
            if (getNum(m) < 0)
                return -1;
        } while (m < 1);
        return m;
    }

    int getColNum()     // function for taking number of columns in sparse matrix
    {
        const char* error_message = "";
        int m;
        do {
            std::cout << error_message << std::endl;
            std::cout << "Enter number of columns: ";
            error_message = "You are wrong! Please, repeat!";
            if (getNum(m) < 0)
                return -1;
        } while (m < 1);
        return m;
    }

    Line* input(Line* firstLine, int column, int row)
    {
        int x, y, value;
        Line* newLine = nullptr;
        Line* tmpLine = nullptr;
        Item* newItem = nullptr;
        Item* tmpItem = nullptr;
        const char* error_message = "";

        std::cout << "Enter number of line --> ";
        do {
            std::cout << error_message << std::endl;
            error_message = "You are wrong! Please, repeat!";
            if (getNum(y) < 0)
                return nullptr;
        } while (y < 0 || y > row);

        error_message = "";
        std::cout << "Enter number of column --> ";
        do {
            std::cout << error_message << std::endl;
            error_message = "You are wrong! Please, repeat!";
            if (getNum(x) < 0)
                return nullptr;
        } while (x < 0 || x > column);

        error_message = "";
        std::cout << "Enter value of cell --> ";
        do {
            std::cout << error_message << std::endl;
            error_message = "You are wrong! Please, repeat!";
            if (getNum(value) < 0)
                return nullptr;
        } while (value < 1);
        newItem = new Item;
        newItem->next = nullptr;
        newItem->numColumn = x;
        newItem->value = value;
        if (firstLine == nullptr) {
            newLine = new Line;
            newLine->next = nullptr;
            newLine->numLine = y;
            newLine->a = newItem;
            firstLine = newLine;
            return firstLine;
        }
        else {
            tmpLine = firstLine;

            if (y < tmpLine->numLine) {
                newLine = new Line;
                newLine->numLine = y;
                newLine->a = newItem;
                newLine->next = firstLine;
                firstLine = newLine;
            }

            else if (y == tmpLine->numLine) {
                if (x < tmpLine->a->numColumn) {
                    newItem->next = tmpLine->a;
                    tmpLine->a = newItem;
                }
                else if (x == tmpLine->a->numColumn)
                    std::cout << "Coordinates are doubled! Cannot allocate memory in one place!" << std::endl;
                else {
                    tmpItem = tmpLine->a;
                    while (tmpItem->next != nullptr) {
                        if (tmpItem->next->numColumn > x) {
                            newItem->next = tmpItem->next;
                            tmpItem->next = newItem;
                            return firstLine;
                        }
                        else if (tmpItem->next->numColumn == x) {
                            std::cout << "Coordinates are doubled! Cannot allocate memory in one place!" << std::endl;
                            return firstLine;
                        }
                        tmpItem = tmpItem->next;
                    }
                    tmpItem->next = newItem;
                }
            }

            else {
                while (tmpLine->next != nullptr) {
                    if (tmpLine->next->numLine > y) {
                        newLine = new Line;
                        newLine->numLine = y;
                        newLine->a = newItem;
                        newLine->next = tmpLine->next;
                        tmpLine->next = newLine;
                    }
                    else if (tmpLine->next->numLine == y) {
                        if (x < tmpLine->next->a->numColumn) {
                            newItem->next = tmpLine->next->a;
                            tmpLine->next->a = newItem;
                        }
                        else if (x == tmpLine->next->a->numColumn)
                            std::cout << "Coordinates are doubled! Cannot allocate memory in one place!" << std::endl;
                        else {
                            tmpItem = tmpLine->next->a;
                            while (tmpItem->next != nullptr) {
                                if (tmpItem->next->numColumn > x) {
                                    newItem->next = tmpItem->next;
                                    tmpItem->next = newItem;
                                    return firstLine;
                                }
                                else if (tmpItem->next->numColumn == x) {
                                    std::cout << "Coordinates are doubled! Cannot allocate memory in one place!" << std::endl;
                                    return firstLine;
                                }
                                tmpItem = tmpItem->next;
                            }
                            tmpItem->next = newItem;
                        }
                    }
                    tmpLine = tmpLine->next;
                }
                newLine = new Line;
                newLine->numLine = y;
                newLine->a = newItem;
                tmpLine->next = newLine;
            }
        }
        return firstLine;
    }

    int D_Add(Line *firstLine)
    {
        return 0;
    }

    int D_Show(Line* firstLine)    // function for output the sparse matrix
    {
        Line* tmp;
        Item* tempItem;
        tmp = firstLine;
        /*if (tmp == nullptr) {
            std::cout << "Matrix is empty!" << std::endl;
            return 1;
        }*/
        std::cout << "Matrix :" << std::endl;
        while (tmp != nullptr) {
            std::cout << "#" << tmp->numLine << ": ";
            tempItem = tmp->a;
            while (tempItem != nullptr) {
                std::cout << "--> (x: " << tempItem->numColumn << "value: " << tempItem->value << ")";
                tempItem = tempItem->next;
            }
            std::cout << std::endl;
            tmp = tmp->next;
        }

        return 1;
    }

    int reverseNum(int num)   // function for reversing number
    {
        int k = 0;
        while(num != 0) {
            int r = num % 10;
            k = 10 * k + r;
            num /= 10;
        }
        return k;
    }

    Line *reverse(Line *firstLine)     // function for reversing elements in sparse matrix
    {
        Line* tmp;
        Item* tempItem;
        tmp = firstLine;
        if (tmp == nullptr) {
            std::cout << "Matrix is empty!" << std::endl;
            return 0;
        }
        while (tmp != nullptr) {
            tempItem = tmp->a;
            while (tempItem != nullptr) {
                tempItem->value = reverseNum(tempItem->value);
                tempItem = tempItem->next;
            }
            tmp = tmp->next;
        }

        return firstLine;
    }

    int D_Reverse(Line *firstLine)
    {
        firstLine = reverse(firstLine);
        return 1;
    }

    void menu_(Line* firstLine, int m, int n)
    {
        int (*fptr[])(Line *) = {NULL, D_Add, D_Show, D_Reverse};

        int b, rc;
        do{
            while(rc = dialog(msgs, NMsgs)){
                if(!fptr[rc](firstLine))
                    break;
            }

            if(rc == 1) firstLine = input(firstLine, m, n);

        } while (rc != 0);
    }

    Line* erase(Line* firstLine)      // function for erasing the sparse matrix
    {
        if (firstLine == nullptr)
            return nullptr;
        while (firstLine != nullptr) {
            firstLine = firstLine->next;
            delete firstLine;
        }
        delete firstLine;
        return nullptr;
    }

}

