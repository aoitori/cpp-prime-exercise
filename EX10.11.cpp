#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int main ()
{
    void elimDups (vector<string> &words);
    vector<string> vecs;
    elimDups(vecs);
    return 0;
}

bool isShorter (const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void elimDups (vector<string> &words)
{
    cout << "Pleas enter words:" << endl;
    string word;
    while (cin >> word)
        words.push_back(word);
    if (!words.empty())
    for (const auto &s : words)
        cout << s << ' ';
        cout << endl;
    cout << "after unique" << endl;
    stable_sort(words.begin(), words.end(), isShorter);
    auto end_unique = unique(words.begin(), words.end());
    for (const auto &s : words)
        cout << s << ' ';
        cout << endl << "after earse" << endl;
    words.erase(end_unique, words.end());
    for (const auto &s : words)
        cout << s << ' ';
        cout << endl;
}
