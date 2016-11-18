#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

int main ()
{
    map<string, size_t> word_count;
    string word;
    while (cin >> word)
    {
        for (auto &c : word)
            c = tolower(c);
        word.erase(remove_if(word.begin(), word.end(), [](const char c){return ispunct(c);}), word.end());
        ++word_count[word];
    }
    for (const auto &s : word_count)
        cout << s.first << " ouccurs" << s.second
             << ((s.second > 1)? " times" : " time") << endl;
}
