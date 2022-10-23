#ifndef SOURCE_H
#define SOURCE_H
#pragma once
#pragma once
#include <iostream>
#include <math.h>
#include <string.h>
#include <ctime>
#include <vector>
#include <map>
namespace Prog4
{
    class Group
    {
    protected:
        int index;
        int groupSize;
        std::string profileNumber;
        int studyPeriod;

    public:
        Group();
        Group(int index, int size, std::string number, int period);
        int getIndex();
        int getSize();
        std::string getProfileNumber();
        int getStudyPeriod();
        Group &setSize(int size);
        Group &setStudyPeriod(int period);
        virtual std::ostream &print(std::ostream &) const = 0;
        ~Group() {}
    };

    class DayBudget : public Group
    {
    private:
        std::string specialization;
        double scolarshipAmount;
        int scolarshipStudents;

    public:
        DayBudget();
        DayBudget(int i, int s, std::string n, int p, std::string spe, double scholar, int students);
        double getScholarship();
        DayBudget &setScholarship(double amount);
        int getScholarshipStudents();
        DayBudget &setScholarshipStudents(int students);
        virtual std::ostream &print(std::ostream &) const override;
    };

    class NightBudget : public Group
    {
    private:
        std::string contingent;
        std::string qualification;

    public:
        NightBudget();
        NightBudget(int i, int s, std::string n, int p, std::string c, std::string q);
        virtual std::ostream &print(std::ostream &) const override;
    };

    class Payable : public Group
    {
    private:
        int contractNumber;
        double paymentAmount;

    public:
        Payable();
        Payable(int i, int s, std::string n, int p, int contract, double payment);
        double getPayment();
        Payable &setPayment(double amount);
        virtual std::ostream &print(std::ostream &) const override;
    };

    class Table
    {
    private:
        std::vector<Group *> table;

    public:
        Table(const Table &t);
        Table &setGroup(Group *g);
        Group *searchGroup(int index);
        void removeGroup(int index);
        virtual std::ostream &print(std::ostream &) const;
    };
}

#endif
