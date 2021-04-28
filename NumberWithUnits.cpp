#include "NumberWithUnits.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
const double EPS = 0.00001;

using namespace std;
using namespace ariel;

namespace ariel
{
    static map<string, map<string, double>> mn;
    NumberWithUnits::NumberWithUnits(double value, const string &unit)
    {
        mn.at(unit);
        this->value = value;
        this->unit = unit;
    }
    double convert(double value, const string &from, const string &to)
    {
        if (from == to)
        {
            return value;
        }
        if (mn[from][to] == 0)
        {
            throw invalid_argument{"unmatch, impssible to change from - [" + from + "] to [" + to + "]"};
        }
        return value * mn[from][to];
    }

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        double num1 = 0;
        double num2 = 0;
        string equal, first_unit, second_unit;

        while (units_file >> num1 >> first_unit >> equal >> num2 >> second_unit)
        {
            mn[first_unit][second_unit] = num2;
            mn[second_unit][first_unit] = num1 / num2;

            for (auto &pair : mn[first_unit])
            {
                double v = mn[second_unit][first_unit] * pair.second;
                mn[second_unit][pair.first] = v;
                mn[pair.first][second_unit] = 1 / v;
            }
            for (auto &pair : mn[second_unit])
            {
                double v = mn[first_unit][second_unit] * pair.second;
                mn[first_unit][pair.first] = v;
                mn[pair.first][first_unit] = 1 / v;
            }
        }
    }
    void NumberWithUnits ::print()
    {

        for (auto &unit1 : mn)
        {
            for (auto &unit2 : unit1.second)
            {
                cout << unit1.first << "  " << unit2.first << "  " << unit2.second << endl;
            }
        }
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num2)
    {
        double change = convert(num2.value, num2.unit, this->unit);
        NumberWithUnits result(this->value + change, this->unit);
        return result;
    }
    NumberWithUnits NumberWithUnits::operator+()
    {
        NumberWithUnits result(+this->value, this->unit);
        return result;
    }
    NumberWithUnits &NumberWithUnits::operator++()
    {
        ++(this->value);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int num)
    { // post
        return NumberWithUnits((this->value)++, this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
    {
        this->value += convert(num.value, num.unit, this->unit);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num2)
    {

        double change = convert(num2.value, num2.unit, this->unit);
        NumberWithUnits result(this->value - change, this->unit);
        return result;
    }
    NumberWithUnits NumberWithUnits::operator-()
    {
        NumberWithUnits result(-this->value, this->unit);
        return result;
    }
    NumberWithUnits &NumberWithUnits::operator--()
    {
        --(this->value);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int num)
    {
        return NumberWithUnits((this->value)--, this->unit);
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
    {
        this->value -= convert(num.value, num.unit, this->unit);
        return *this;
    }

    NumberWithUnits operator*(const NumberWithUnits &num2, const double num1)
    {
        return NumberWithUnits(num2.value * num1, num2.unit);
    }

    NumberWithUnits operator*(const double num1, const NumberWithUnits &num2)
    {
        return NumberWithUnits(num2.value * num1, num2.unit);
    }
    NumberWithUnits &NumberWithUnits::operator*=(double num)
    {
        this->value *= num;
        return *this;
    }

    bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return (abs(num1.value - convert(num2.value, num2.unit, num1.unit)) <= EPS);
    }
    bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return !(num1 == num2);
    }
    bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return (num1.value < convert(num2.value, num2.unit, num1.unit));
    }
    bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return ((num1 < num2) || (num1 == num2));
    }
    bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return !(num1 < num2) && (!(num1 == num2));
    }
    bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2)
    {
        return (num1 > num2 || num1 == num2);
    }

    
    std::ostream& operator<< (std::ostream &out, const NumberWithUnits &num1)
    {
        
        out << num1.value << "[" << num1.unit << "]";
        return out;
    }
    std::istream &operator>>(std::istream &in, NumberWithUnits &num1)
    {
        double val=0;
        std::string type;
        char c=' ';
        in >> val;
        in >> c ;
        while(c!=']'){
            if(c!='['){
                type.insert(type.end(),c);
            }
            in>>c;
        }
       if(mn[type].empty()){throw invalid_argument{"unit doesnt exist"};};
        num1.value=val;
        num1.unit=type;
        return in;
    
    }
}
