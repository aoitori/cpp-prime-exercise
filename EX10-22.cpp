#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <functional>
using namespace std;

int main ()
{
    void biggies(vector<string> &words, vector<string>::size_type sz);
    vector<string> vecs;
    string word;
    ifstream inFile("test.txt");
    if (inFile.fail())
        return 1;
    while (inFile >> word)
        vecs.push_back(word);
    biggies(vecs, 6);
    return 0;
}

void elimDups (vector<string> &s)
{
    sort(s.begin(), s.end());
    auto en = unique(s.begin(), s.end());
    s.erase(en, s.end());
}

string make_plural (int c, const string &s1, const string &s2)
{
    if ( c > 1)
        return s1 + s2;
    return s1;
}
bool cmpstr (const string &s1, vector<string>::size_type i)
{
    return s1.size() <= 6;
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
    using std::placeholders::_1;
    elimDups(words);
    stable_sort(words.begin(), words.end(),
                [](const string &a, const string &b)
                {return a.size() < b.size();});
    auto fless = bind(cmpstr, _1, sz);
    auto wc = find_if(words.begin(), words.end(), [sz](const string &s)
                                    {return s.size() > 6;});

    auto counter = count_if(words.begin(), words.end(), fless);
    cout << counter << " " << make_plural(counter, "word", "s")
         << " of length " << sz << " or less" << endl;
    for_each(words.begin(), wc, [](const string &s){cout << s << " ";});
    cout << endl;
}
