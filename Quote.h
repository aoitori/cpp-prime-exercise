#ifndef QUOTE_H
#define QUOTE_H
#include <string>
using std::string;
class Quote
{
public:
	Quote() = default;
	Quote(const string &book, double sales_price):bookNo(book), price(sales_price){}
	string isbn() const { return bookNo; }

	virtual double net_price(std::size_t n) const { return n * price; }
	virtual ~Quote() = default;
	virtual void debug() const;
private:
	string bookNo;
protected:
	double price = 0.0;
};

class Bulk_quote : public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const string&, double, std::size_t, double);
	double net_price(std::size_t) const  override;
	void debug() const override;
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};
Bulk_quote::Bulk_quote(const string &book, double p, std::size_t n, double d):Quote(book, p), min_qty(n), discount(d){}

double Bulk_quote::net_price(std::size_t cnt) const 
{
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	else
		return cnt * price;
}

class Lim_quote :public Quote
{
public:
	Lim_quote() = default;
	Lim_quote(const string &book, double p, std::size_t max, double dic):Quote(book, p), max_qty(max), discount(dic){}
	double net_price(std::size_t) const override;
	void debug() const override;
private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};

double Lim_quote::net_price(std::size_t cnt) const
{
	if (cnt <= max_qty)
		return cnt * (1 - discount) * price;
	else
		return max_qty * (1 - discount) * price + (cnt - max_qty) * price;
}
#endif // !QUOTE_H
