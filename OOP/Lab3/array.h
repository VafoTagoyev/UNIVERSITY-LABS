#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
//#include <bits/stdc++.h>

namespace Prog3_1 {
    class Array{
    private:
        static const int size = 6;
        static const int sizeStr = 10;
        std::vector<std::string> arr;
    public:
        Array(){
            arr.push_back("Vafo");
            arr.push_back("Imomali");
        }
        void addWord(std::string word);
        void searchWord(std::string word);
        void takeWord(int);
        void alphabaticallySortedWords();
        void print();
    };

}

#endif // ARRAY_H_INCLUDED
