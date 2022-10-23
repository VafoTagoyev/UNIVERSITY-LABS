#include "header.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <ctime>
#include <vector>
#include <map>

using namespace Prog4;

void test()
{
    DayBudget day = DayBudget(1, 30, "A12", 4, "Computer Science", 1000, 7);
    day.print(std::cout);
    std::cout << "\n";
    day.setSize(27);
    day.setStudyPeriod(3);
    day.setScholarship(850);
    std::cout << "Scolarship amount after update -- " << day.getScholarship();
    day.setScholarshipStudents(12);
    std::cout << "\n\n\t\t------After updating the group------\n\n\n";
    day.print(std::cout);

    NightBudget night = NightBudget(2, 32, "B3", 2, "Social Behaviour", "Master on Social Science");
    night.print(std::cout);
    night.setSize(29);
    std::cout << "\nGroup size after update -- " << night.getSize() << "\n\n";

    Payable pay = Payable(3, 25, "A5", 3, 7, 45000);
    pay.print(std::cout);
    pay.setPayment(40000);
    std::cout << "\n\t\t------After updating the payment for group------\n\n";
    pay.print(std::cout);
}

int main()
{
    test();
    return 0;
}
