#include <iostream>
#include "header.h"
#include "functions.cpp"

using namespace header;

int main() {
    Line* firstLine = nullptr;

    int m, n;
    m = getRowNum();
    n = getColNum();

    menu_(firstLine, m, n);
    std::cout << "That is all bye!\n";
    erase(firstLine);
    return 0;
}
