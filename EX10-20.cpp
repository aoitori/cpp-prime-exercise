#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
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

void biggies(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);
    stable_sort(words.begin(), words.end(),
                [](const string &a, const string &b)
                {return a.size() < b.size();});
    auto wc = find_if(words.begin(), words.end(),
                      [sz](const string &a){return a.size() >= sz;});
    auto counter = count_if(words.begin(), words.end(),
                      [sz](const string &a){return a.size() >= sz;});
    cout << counter << " " << make_plural(counter, "word", "s")
         << " of length " << sz << " or longer" << endl;
    for_each(wc, words.end(), [](const string &s){cout << s << " ";});
    cout << endl;
}
