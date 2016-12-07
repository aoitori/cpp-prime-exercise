#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory>
using namespace std;


auto make_ptr()
{
	return make_shared<vector<int>>();
}

void read_input(shared_ptr<vector<int>> p)
{
	int i;
	while (cin >> i)
		p->push_back(i);
}

void output(shared_ptr<vector<int>> p)
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
	
	system("pause");
	return 0;
}
