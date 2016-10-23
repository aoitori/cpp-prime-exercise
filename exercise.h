#ifndef EXERCISE_H_
#define EXERCISE_H_
#include <string>
#include <iostream>
using std::string;
using namespace std;
class Person
{
private:
    string name;
    string address;
public:
    Person () = default;
    Person(string &n, string &ad): name(n), address(ad){}
    const string& re_name () const {return name;}
    const string& re_address() const {return address;}
};

class Sales_date
{
private:
    string bookNo = "";
    unsigned solds = 0;
    double price = 0.0;
    double revenue = 0.0;
public:
    Sales_date(string b, unsigned s, double p)
    :bookNo(b), solds(s), price(p), revenue(s * p){cout << "excuting 3" << endl;}
    Sales_date():Sales_date(" ", 0, 0) {cout << "excuting ()" << endl;}
    Sales_date(string b): Sales_date(b, 0, 0){cout << "excuting 1" << endl;}
    Sales_date(istream &is);
    string &isbn() {return bookNo;}
    double &avg_price() {return price;}
    Sales_date& combine(const Sales_date &rhs);
    friend istream& read(istream &is, Sales_date &item);
    friend ostream &print (ostream &os, const Sales_date &item);
};
istream& read(istream &is, Sales_date &item)
{
    double price = 1;
    is >> item.bookNo >> item.solds >> price;
    item.revenue = price * item.solds;
    return is;
}

ostream &print (ostream &os, const Sales_date &item)
{
    os << "Book: " << item.bookNo << endl
       << "solds: " << item.solds << " revenue: "
       << item.revenue << " pirce: " << item.price;
       return os;
}

Sales_date::Sales_date(istream &is):Sales_date()
{
    cout << "executing is" << endl;
    read(is, *this);
}
Sales_date& Sales_date::combine(const Sales_date &rhs)
{
    solds += rhs.solds;
    revenue += rhs.revenue;
    price = revenue / solds;
    return *this;
}
#endif // EXERCISE_H_
