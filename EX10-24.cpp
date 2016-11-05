#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
using namespace std;

int main ()
{
    using std::placeholders::_1;
    bool check_size(int i, string::size_type sz);
    vector<int> veci {1, 2, 3, 4, 7, 8, 5, 6, 10, 12, 70};
    sort(veci.begin(), veci.end());
    auto fe = find_if(veci.begin(), veci.end(), bind(check_size, _1, 6));
    for_each(fe, veci.end(), [](vector<int>::value_type i)
                            {cout << i << ' ';});
    cout << endl;
    return 0;
}

bool check_size(int i, string::size_type sz)
{
    return i > sz;
}
