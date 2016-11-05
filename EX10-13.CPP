#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;
int main ()
{
    bool morethanfive (const string &s);
    ifstream infile("test.txt");
    if (infile.fail())
        return 1;
    vector<string> words;
    string temp;
    while (infile >> temp)
        words.push_back(temp);
    auto ed = partition(words.begin(), words.end(), morethanfive);
    for (auto be = words.begin(); be != ed; ++be)
        cout << *be << endl;
}

bool morethanfive (const string &s)
{
    return s.size() >= 5;
}
