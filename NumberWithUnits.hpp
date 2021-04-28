#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <list>
#include <stdexcept>

using namespace std;

namespace ariel
{
    class NumberWithUnits
    {

    private:
        double value;
        string unit;

    public:
        NumberWithUnits(double value, const string &unit);

        static void read_units(ifstream &units_file);
        static void print();

        friend ostream &operator<<(ostream &out, const NumberWithUnits &num1);
        friend istream &operator>>(istream &in, NumberWithUnits &num1);

        NumberWithUnits operator+(const NumberWithUnits &num2);
        NumberWithUnits operator+();
        NumberWithUnits &operator+=(const NumberWithUnits &num2);

        NumberWithUnits operator-();
        NumberWithUnits operator-(const NumberWithUnits &num2);
        NumberWithUnits &operator-=(const NumberWithUnits &num2);

        NumberWithUnits operator++(int num);
        NumberWithUnits &operator++();
        NumberWithUnits operator--(int num);
        NumberWithUnits &operator--();

        friend NumberWithUnits operator*(const double num1, const NumberWithUnits &num2);

        friend NumberWithUnits operator*(const NumberWithUnits &num2, const double num1);
        NumberWithUnits &operator*=(double num);

        friend bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2);
    };
}
