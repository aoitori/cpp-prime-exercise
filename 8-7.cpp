#include <iostream>
#include <fstream>
#include <string>
#include "exercise.h"
using namespace std;
int main(int argc, char **argv)
{
    ifstream inf(argv[1]);
    if (inf.fail())
    {
        cout << "Couldn't open file " << argv[1] << endl;
        return 1;
    }
    else
        cout << argv[1] << " Succeeded.\n" << endl;
    Sales_date total;
    if (read(inf, total))
    {
        Sales_date trans;
        while(read(inf, trans))
        {
            if(total.isbn() == trans.isbn())
                total.combine(trans);
            else
            {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    }
    else
        cerr << "No data?!" << endl;
    return 0;
}
