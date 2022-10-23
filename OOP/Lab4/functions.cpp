#include "header.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <ctime>
#include <vector>
#include <map>

namespace Prog4
{
    Group::Group() : index(0), groupSize(0), profileNumber(""), studyPeriod(0) {}
    Group::Group(int index, int size, std::string number, int period) : index(index), groupSize(size), profileNumber(number), studyPeriod(period) {}
    int Group::getIndex() { return index; }
    int Group::getSize() { return groupSize; }
    std::string Group::getProfileNumber() { return profileNumber; }
    int Group::getStudyPeriod() { return studyPeriod; }
    Group &Group::setSize(int size)
    {
        if (size < 0)
            throw std::exception(); // "Size can't be negative!"
        groupSize = size;
        return *this;
    }
    Group &Group::setStudyPeriod(int period)
    {
        if (period < 0)
            throw std::exception(); // "Study period can't be negative!"
        studyPeriod = period;
        return *this;
    }

    DayBudget::DayBudget() : Group(0, 0, "", 0) {}
    DayBudget::DayBudget(int i, int s, std::string n, int p, std::string spe, double scholar, int students) : Group(i, s, n, p), specialization(spe), scolarshipAmount(scholar), scolarshipStudents(students) {}
    double DayBudget::getScholarship() { return scolarshipAmount; }
    DayBudget &DayBudget::setScholarship(double amount)
    {
        if (amount < 0)
            throw std::exception(); // "Scholarship amount can't be negative!"
        scolarshipAmount = amount;
        return *this;
    }
    int DayBudget::getScholarshipStudents() { return scolarshipStudents; }
    DayBudget &DayBudget::setScholarshipStudents(int students)
    {
        if (students < 0)
            throw std::exception(); // "Number of students who get scholarship can't be negative!"
        scolarshipStudents = students;
        return *this;
    }
    std::ostream &DayBudget::print(std::ostream &s) const
    {
        s << "************This is Day Budget group, it contains the following info************\n";
        s << "Group index -- " << index << "\n";
        s << "Size of this group - " << groupSize << "\n";
        s << "Profile Number -- " << profileNumber << "\n";
        s << "Study Period for this group - " << studyPeriod << "\n";
        s << "Group specialization is -- " << specialization << "\n";
        s << "The amount of scholarship -- " << scolarshipAmount << "\n";
        s << "The number of students getting this scholarship - " << scolarshipStudents << "\n";

        return s;
    }

    NightBudget::NightBudget() : Group(0, 0, "", 0) {}
    NightBudget::NightBudget(int i, int s, std::string n, int p, std::string c, std::string q) : Group(i, s, n, p), contingent(c), qualification(q) {}
    std::ostream &NightBudget::print(std::ostream &s) const
    {
        s << "\n\n************This is Night Budget group, it contains the following info************\n";
        s << "Group index -- " << index << "\n";
        s << "Size of this group - " << groupSize << "\n";
        s << "Profile Number -- " << profileNumber << "\n";
        s << "Study Period for this group - " << studyPeriod << "\n";
        s << "Contingent of Students -- " << contingent << "\n";
        s << "Qualification of student -- " << qualification << "\n";
        return s;
    }

    Payable::Payable() : Group(0, 0, "", 0) {}
    Payable::Payable(int i, int s, std::string n, int p, int contract, double payment) : Group(i, s, n, p), contractNumber(contract), paymentAmount(payment) {}
    double Payable::getPayment() { return paymentAmount; }
    Payable &Payable::setPayment(double amount)
    {
        if (amount < 0)
            throw std::exception(); // "Payment amount can't be negative!"
        paymentAmount = amount;
        return *this;
    }
    std::ostream &Payable::print(std::ostream &s) const
    {
        s << "\n************This is Payable group, it contains the following info************\n";
        s << "Group index -- " << index << "\n";
        s << "Size of this group - " << groupSize << "\n";
        s << "Profile Number -- " << profileNumber << "\n";
        s << "Study Period for this group - " << studyPeriod << "\n";
        s << "Contract Number of this group -- " << contractNumber << "\n";
        s << "Amount of payment per semester -- " << paymentAmount << "\n";
        return s;
    }

    Table::Table(const Table &t) : table(t.table) {}
    Table &Table::setGroup(Group *g)
    {
        table.push_back(g);
        return *this;
    }

    Group *Table::searchGroup(int index)
    {
        int len = table.size();
        for (int i = 0; i < len; i++)
        {
            if (table[i]->getIndex() == index)
            {
                return table[i];
            }
        }
        throw std::exception(); // "Table does not have this group!"
    }

    void Table::removeGroup(int index)
    {
        int len = table.size();
        bool hasGroup = false;
        for (int i = 0; i < len; i++)
        {
            if (table[i]->getIndex() == index)
            {
                hasGroup = true;
                table.erase(table.begin() + i);
            }
        }
        if (!hasGroup)
            throw std::exception(); // "Table does not have this group!"
    }

    std::ostream &Table::print(std::ostream &s) const
    {
        int len = table.size();
        if (len == 0)
        {
            s << "No group table!\n";
        }
        else
        {
            for (int i = 0; i < len; i++)
            {
                table[i]->print(s);
            }
        }
        return s;
    }

}
