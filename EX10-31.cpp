#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;
int main ()
{
    ifstream inf("test.txt");
    if (inf.fail())
        exit(EXIT_FAILURE);
    istream_iterator<string> file_iter(inf), eof;
    vector<string> vecs;
    while(file_iter != eof)
        vecs.push_back(*file_iter++);
    ostream_iterator<string> out_iter(cout, " ");
        unique_copy(vecs.begin(), vecs.end(), out_iter);

    return 0;
}
