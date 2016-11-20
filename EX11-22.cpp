#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main()
{
	multimap<string, string> family;
	cout << "Please enter the family's name(q to exit): ";
	for (string word; cin >> word && word != "q";)
	{
		cout << "Enter the name(q to exit): ";
		for (string name; cin >> name && name != "q";)
		{
			family.insert({ word, name });
			cout << "Next name: ";
		}
		cin.clear();
		cout << "Next family or q to exit " << endl;
	}
	for (const auto &s : family)
			cout << s.first << " " << s.second << endl;
	system("pause");
	return 0;
}
