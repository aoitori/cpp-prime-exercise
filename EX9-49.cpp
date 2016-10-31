#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <deque>
#include <forward_list>
#include <cstdlib>
using namespace std;

int main ()
{
    cout << "Please enter the file name that contianning words: ";
    string file;
    cin >> file;
    ifstream infile(file);
    if (infile.fail())
    {
        cout << "Failed to open " << file << endl;
        cerr << "Program terminated." << endl;
        exit(EXIT_FAILURE);
    }
    else
        cout << "Succeeded open " << file << endl;

    vector<string> words;
    if (!infile.eof())
    {
        string line, word;
        while(getline(infile, line))
        {
             istringstream ist(line);
            while (ist >> word)
                words.push_back(word);
        }
    }

    for (auto s = words.begin(); s != words.end();)
    {
        if ((string::npos != (*s).find_first_of("bdfhikl")) ||
            (string::npos != (*s).find_first_of("gjpqy")))
            s = words.erase(s);
        else
            ++s;
    }

    string longest = words[0];
    for (vector<string>::size_type i = 1; i < words.size(); ++i)
    {
        if (longest.size() < words[i].size())
            longest = words[i];
    }
    cout << "longest: " << longest << endl;

    return 0;
}
