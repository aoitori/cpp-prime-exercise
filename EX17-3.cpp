#include "D:\c++\17-3.h"
using std::cout; using std::cin;
using line_no = TextQuery::line_no;
void print(ostream &os, const std::tuple<string, shared_ptr<set<line_no>>, shared_ptr<vector<string>>> r)
{
	os << std::get<0>(r) << " occurs " << std::get<1>(r)->size() << make_plura(std::get<1>(r)->size()) << endl;
	for(const auto num : *std::get<1>(r))
		os << "\t(line " << num + 1 << ")" << std::get<2>(r)->at(num) << endl;
}
int main()
{
	ifstream inFile("D:/c++/test.txt");
	TextQuery first(inFile);
	cout << "Enter word to search : ";
	string sea;
	while (true)
	{
		if (cin >> sea && sea != "q")
			print(cout, first.query(sea));
		else
			break;
	}
	return 0;
}
