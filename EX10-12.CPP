#include "d:\GCC\7\Sales_data.h"
#include <vector>
#include <algorithm>
using namespace std;
int main ()
{
    vector<Sales_data> vecSale = {{"7888912301564", 2, 2.2}, {"156489798", 5, 6},
                                  {"54565551533", 7, 8.8}};
    sort(vecSale.begin(), vecSale.end(), compareIsbn);
    for(const auto &s : vecSale)
        cout << s.isbn() << endl;
}
