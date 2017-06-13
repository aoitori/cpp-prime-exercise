#include <iostream>
#include <string>
#include <vector>
#include "Sales_data.h"
#include <functional>
#include <algorithm>
using std::string; using std::vector; 
using std::cout; using std::endl;
void fcn(const vector<Sales_data> &v);
class Screen
{
	
public:
	typedef string::size_type pos;
	char get_cursor() const { return contents[cursor]; }
	char get() const { return contents[0]; }
	char get(pos ht, pos wd) const { return static_cast<char>(ht + wd); }
	static const pos Screen::* return_cursor()  { return &Screen::cursor; }

	/*Screen& home();
	Screen& forward();
	Screen& back();
	Screen& up();
	Screen& down();
	using Action = Screen& (Screen::*)();
	enum Directions{HOME, FORWARD, BACK, UP, DOWN};
	Screen& move(Directions);*/
private:
	string contents;
	pos cursor;
	pos height, width;
	//static Action Menu[];
};
/*Screen::Action Screen::Menu[] = { &Screen::home, &Screen::forward, &Screen::back, &Screen::up, &Screen::down };
Screen& Screen::move(Directions d)
{
	return (this->*Menu[d])();
}*/
int main()
{
	using Auto = char (Screen::*)(Screen::pos, Screen::pos) const;
	typedef char (Screen::*Get2)()const;
	Get2 pmf = &Screen::get;
	Auto pmf2 = &Screen::get;
	Screen mysc, *myscp = &mysc;
	char c1 = (mysc.*pmf)();
	char c2 = (myscp->*pmf2)(100, 100);
	cout << c1 << "," << c2 << endl;
	auto pmmf = &Screen::get_cursor;
	pmmf = &Screen::get;
	Sales_data s1("data", 20, 5.5);
	typedef double(Sales_data::*PMFS)() const;
	PMFS pas = &Sales_data::avg_price;
	cout << (s1.*pas)() << endl;
	typedef char (Screen::*GCUR)() const;
	
	std::function<bool(const string&)> fpmf = &string::empty;
	vector<string> vecs{ "", "dda", " ", "", "dadfa", "adfa" };
	cout << std::count_if(vecs.cbegin(), vecs.cend(), fpmf) << endl;

	cout << "mem_fn : " << std::count_if(vecs.cbegin(), vecs.cend(), std::mem_fn(&string::empty)) << endl;
	cout << "bind : " << std::count_if(vecs.cbegin(), vecs.cend(), std::bind(&string::empty, std::placeholders::_1)) << endl;
	vector<Sales_data> vecss{ {"sal", 200, 5.3}, {"dds", 500, 123.22}, {"ddfas", 400, 12.2}, {"ggf", 800, 22.2}, {"fjgn", 100, 1.2} };
	fcn(vecss);
	return 0;
}

void fcn(const vector<Sales_data> &v)
{
	auto pp = &Sales_data::avg_price;
	auto r = std::find_if(v.cbegin(), v.cend(), [&pp](const Sales_data &a,double b = 10.2) {return (a.*pp)() > 10.2; });
	cout << *r << endl;
}
