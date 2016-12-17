#include "...\textquery\TextQuery.h"

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
