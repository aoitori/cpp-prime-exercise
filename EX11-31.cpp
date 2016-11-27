#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int main()
{
	multimap<string, string> author = { {"jay", "title"}, {"jay", "fanticy"}, {"sed", "hide"}, {"sed", "yes"} };
	for (auto beg = author.equal_range("jay"); beg.first != beg.second; ++beg.first)  //equal ver.
	{
		if (beg.first->second == "title")
			author.erase(beg.first++);
		cout << "Works: " << beg.first->second << endl;
	}

	system("pause");
	return 0;
}

/* lower & upper
* for (auto beg = author.lower_bound("jay"), end = author.upper_bound("jay"); beg != end; ++beg)
*{
*   if ( beg->second == "title")
*       author.erase(beg++);
*		cout << "Works: " << beg->second << endl;
*}
*/

/* find and count
* auto entries = author.count("jay");
* auto found = author.find("jay);
*   while(entries)
*  {
*     if (found->second == "title")
*     {
*       author.erase(found++);
*       --entries;
*     }
*     cout << "Works: " << found->second << endl;
*     --entries;
*     ++found;
*  }
*/
