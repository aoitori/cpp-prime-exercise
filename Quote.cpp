#include "Quote.h"
#include <iostream>
using std::cout; using std::cin; using std::endl;
void Quote::debug() const { cout << " Quote " << ' ' << isbn() << ' ' << price << endl; }
void Bulk_quote::debug() const { cout << " Bulk Quote " << ' ' << min_qty << ' ' << discount; Quote::debug(); }
void Lim_quote::debug() const { cout << " Limit Quote " << ' ' << max_qty << ' ' << discount; Quote::debug(); }
double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

int main()
{
	Quote a("gg", 50);
	Bulk_quote b("ddd", 40, 100, 0.3);
	print_total(cout, a, 60);
	print_total(cout, b, 200);
	b.debug();
	a.debug();
	return 0;
}