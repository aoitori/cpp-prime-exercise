#include <iostream>
#include <regex>
#include <string>
#include <fstream>
using std::cout; using std::endl; using std::regex;
using std::cin; using std::ifstream; using std::string;


int main()
{
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	regex r(phone);
	string s;
	string fmt = "$2.$5.$7 ";
	while (std::getline(cin, s) && s != "q")
	{
		
		std::smatch result;
		std::regex_search(s, result, r);
		if (!result.empty())	
				cout << std::regex_replace(result.suffix().str(), r, fmt) << endl;
		else
			cout << "Sorry, No match." << endl;
	}

	return 0;
}
