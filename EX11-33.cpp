#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <sstream>

using namespace std;
int main()
{
	void trans_form(ifstream &map_file, ifstream &input);
	ifstream MapFile("d:/c++/transform.txt"), InputFile("d:/c++/input.txt");
	if (MapFile.fail() || InputFile.fail())
	{
		cerr << "no such file" << endl;
		exit(EXIT_FAILURE);
	}
	else
		trans_form(MapFile, InputFile);
	system("pause");
	return 0;
}

const string& transword(const string &s, map<string, string> &m)
{
	auto map_it = m.find(s);
	if (map_it != m.cend())
		return map_it->second;
	else
		return s;
}

map<string, string> make_map(ifstream &map_file)
{
	map<string, string> transform;
	string key, value;
	while (map_file >> key && getline(map_file, value))
	{
		if (value.size() > 1)
			transform[key] = value.substr(1);
		else
			throw("no such value " + key);
	}
	return transform;
}

void trans_form(ifstream &map_file, ifstream &input)
{
	auto translate = make_map(map_file);
	string text;
	while (getline(input, text))
	{
		string word;
		istringstream line(text);
		bool firstword = true;
		while (line >> word)
		{
			if (firstword)
				firstword = false;
			else
				cout << " ";
			cout << transword(word, translate);
		}
		cout << endl;
	}
}
