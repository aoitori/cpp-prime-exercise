#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int>  PTR;
auto make_ptr()
{
	return new PTR();
}

void read_input(PTR *p)
{
	int i;
	while (cin >> i)
		p->push_back(i);
}

void output(PTR *p)
{
	for (const auto &i : *p)
		cout << i << ' ';
	cout << endl;
}
int main()
{
	auto q = make_ptr();
	read_input(q);
	output(q);
	delete q;
	system("pause");
	return 0;
}
