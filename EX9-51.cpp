#include <iostream>
#include <string>
using namespace std;
class Date
{
private:
    unsigned year = 1900;
    unsigned month = 1;
    unsigned day = 1;
public:
    Date(const string &s)
    {
        if (s.find_first_of('/') != string::npos){
            month = stoi(s.substr(0, s.find_first_of('/')));
            day = stoi(s.substr(s.find_first_of('/')+1, s.find_last_of('/')));
            year = stoi(s.substr(s.find_last_of('/')+1, 4));
            }
        else if (s.find_first_of(',') > 4)
        {
            day = stoi(s.substr(s.find_first_of("0123456789"), s.find_first_of(',')));
            year = stoi(s.substr(s.find_first_of(',')+ 1));
            if(s.find("Jan") != string::npos) month = 1;
            if(s.find("Feb") != string::npos) month = 2;
            if(s.find("Mar") != string::npos) month = 3;
            if(s.find("Apr") != string::npos) month = 4;
            if(s.find("May") != string::npos) month = 5;
            if(s.find("Jun") != string::npos) month = 6;
            if(s.find("Jul") != string::npos) month = 7;
            if(s.find("Aug") != string::npos) month = 8;
            if(s.find("Sep") != string::npos) month = 9;
            if(s.find("Oct") != string::npos) month = 10;
            if(s.find("Nov") != string::npos) month = 11;
            if(s.find("Dec") != string::npos) month = 12;
        }
    }
    void print(){cout << "month: " << month << " day: " << day << " year: " << year << endl;}
};
int main()
{
    Date d("June 11, 2016");
    d.print();
    return 0;
}
