#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;
int main ()
{
    istream_iterator<int> in_iter(cin), endof;
    vector<int> veci;
    copy(in_iter, endof, back_inserter(veci));
    sort(veci.begin(), veci.end());
    ostream_iterator<int> out_in(cout, " ");
    copy(veci.cbegin(), veci.cend(), out_in);

    return 0;
}
