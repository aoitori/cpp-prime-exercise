#include <algorithm>
#include <string>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;
int main ()
{
    void elimDups(list<string> &word);
    list<string> lst;
    cout << "Please enter words: ";
    istream_iterator<string> in_iter(cin), in_eof;
    copy(in_iter, in_eof, back_inserter(lst));
    elimDups(lst);
    for_each(lst.cbegin(), lst.cend(), [](const string &s){cout << s << " ";});
    return 0;
}
void elimDups(list<string> &word)
{
    word.sort();
    word.unique();
}
