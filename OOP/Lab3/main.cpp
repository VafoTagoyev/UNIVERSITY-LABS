#include <iostream>
//#include <bits/stdc++.h>
#include "array.h"
#include "Array_1.cpp"

using namespace Prog3_1;

int main()
{
    Array A;
    std::cout << "The given Array of Words : \n";
    A.print();
    A.addWord("Sarvarbek");
    A.addWord("Abdulaziz");
    A.addWord("Bahodir");
    std::cout << "After adding words the array is : \n";
    A.print();
    A.addWord("Asilbek");
    std::cout << "After adding a word the array is : \n";
    A.print();
    A.searchWord("Shahzod");
    A.searchWord("Vafo");
    A.takeWord(2);
    A.alphabaticallySortedWords();
    std::cout << "The array after alphabetically sorting is : \n";
    A.print();

    return 0;
}
