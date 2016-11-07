#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;
int main ()
{
    ifstream inf("test.txt");
    if (inf.fail())
        exit(EXIT_FAILURE);
    istream_iterator<string> file_iter(inf), eof;
    vector<string> vecs;
    while (file_iter != eof)
        vecs.push_back(*file_iter++);
    for (const auto &s : vecs)
        cout << s << endl;
    return 0;
}
