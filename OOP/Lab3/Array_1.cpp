#include <iostream>
//#include <bits/stdc++.h>
#include "array.h"
#include <cstring>
#include <algorithm>
#include <iterator>

namespace Prog3_1 {
    
   	void Array::addWord(std::string word)
    {
        arr.push_back(word);
    }

    void Array::searchWord(std::string word)
    {
        int i;
        for(i = 0; i < arr.size(); i++){
            if(arr[i] == word){
                std::cout << "Word " << word << " is found!" << std::endl;
                std::cout << "The position of " << word << " is " << i+1 << std::endl;
                break;
            }
        }

        if(i == arr.size())
            std::cout << "The word " << word << " is not found!" << std::endl;
    }

    void Array::takeWord(int k)
    {
        std::cout << "\nThe word in position " << k << " is : " << arr[k-1] << std::endl;
        std::cout << std::endl;
    }

    bool comparator(std::string a, std::string b)
    {
        return a < b;
    }

    void Array::alphabaticallySortedWords()
    {
        std::sort(arr.begin(), arr.end(), comparator);
    }

    void Array::print()
    {
        for(int k = 0; k < arr.size(); k++)
            std::cout << arr[k] << "\n";
        std::cout << std::endl;
    }

}
