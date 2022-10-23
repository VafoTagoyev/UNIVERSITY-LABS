#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#pragma once
namespace header {
    typedef struct Item {
        int numColumn;
        int value;
        struct Item* next;
    } Item;
    typedef struct Line {
        int numLine;
        struct Item* a;
        struct Line* next;
    } Line;

    template <class T>
    int getNum(T& a) {
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }

    int dialog(const char **, int);
    int getInt(int *);
    int getRowNum();
    int getColNum();
    int reverseNum(int);
    void menu_(Line *, int, int);
    Line *insert(Line *, int, int);
    Line *reverse(Line *);
    int D_Add(Line *);
    int D_Reverse(Line *);
    int D_Show(const char*, Line *);
    Line* erase(Line *);
}

#endif // HEADER_H_INCLUDED
