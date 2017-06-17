include <iostream>
#include <string>
#include <vector>
#include "Sales_data.h"
#include <functional>
#include <algorithm>
#include <type_traits>
using std::string; using std::vector; 
using std::cout; using std::endl;

class Token
{
public:
	Token() :tok(INT), ival(0) {}
	Token(const Token &t) :tok(t.tok) { cout << "copy constructor" << endl; copyUnion(t); }
	Token & operator=(const Token&);
	~Token() { cout << "destructor" << endl;  if (tok == STR) sval.~string();  
	else if (SALE == tok) sales.~Sales_data(); 
	}

	Token& operator=(const Sales_data&);
	Token& operator=(const string&);
	Token& operator=(char);
	Token& operator=(int);
	Token& operator=(double);

	Token(Token &&t) noexcept:tok(t.tok) { cout << "move constructor" << endl;
	switch (t.tok)
	{
	case Token::STR: new(&sval)string(std::move(t.sval)); break;
	case Token::SALE: new(&sales)Sales_data(std::move(t.sales)); break;
	case Token::INT: ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL: dval = t.dval; break;
	}
	}
	Token& operator=(Token &&);
private:
	enum {INT, CHAR, DBL, STR, SALE} tok;
	union 
	{
		char cval;
		int ival;
		double dval;
		string sval;
		Sales_data sales;
	};
	void copyUnion(const Token&);
	//void moveUnion(Token&);
	void checkClass() const;
};

void Token::checkClass() const
{
	cout << "checking class" << endl;
	switch (tok)
	{
	case Token::STR: sval.~string(); break;
	case Token::SALE: sales.~Sales_data(); break;
	default: break;
	}
}
Token& Token::operator=(char c)
{
	checkClass();
	cval = c;
	tok = CHAR;
	return *this;
}

Token& Token::operator=(int i)
{
	checkClass();
	ival = i;
	tok = INT;
	return *this;
}

Token& Token::operator=(double d)
{
	checkClass();
	dval = d;
	tok = DBL;
	return *this;
}

Token & Token::operator=(Token &&rhs) 
{
	cout << "move assignment" << endl;
	if (this == &rhs) return *this;
	checkClass();
	if (STR == tok && STR == rhs.tok)
		sval = std::move(rhs.sval);
	else if (SALE == tok && SALE == rhs.tok)
		sales = std::move(rhs.sales);
	else
	{
		switch (rhs.tok)
		{
		case Token::INT: ival = rhs.ival; break;
		case Token::CHAR: cval = rhs.cval; break;
		case Token::DBL: dval = rhs.dval; break;
		}
	}
	tok = std::move(rhs.tok);
	return *this;
}

Token& Token::operator=(const Sales_data &s)
{
	if (SALE == tok)
		sales = s;
	else
		new(&sales)Sales_data(s);
	tok = SALE;
	return *this;
}

Token& Token::operator=(const string &s)
{
	if ( STR == tok)
		sval = s;
	else
		new(&sval)string(s);
	tok = STR;
	return *this;
}

void Token::copyUnion(const Token &t)
{
	cout << "used copyUnion" << endl;
	switch (t.tok)
	{
	case Token::CHAR: cval = t.cval; break;
	case Token::INT: ival = t.ival; break;
	case Token::DBL: dval = t.dval; break;
	case Token::STR: new(&sval)string(t.sval); break;
	case Token::SALE: new(&sales)Sales_data(t.sales); break;
	}
}

/*void Token::moveUnion(Token &rhs)
{
	switch (rhs.tok)
	{
	case Token::STR: new(&sval)string(std::move(rhs.sval)); break;
	//case Token::SALE: sales = std::move(rhs.sales); break;
	case Token::INT: ival = rhs.ival; break;
	case Token::CHAR: cval = rhs.cval; break;
	case Token::DBL: dval = rhs.dval; break;
	}
}*/


Token & Token::operator=(const Token &t)
{
	cout << "copy assignment" << endl;
	if(STR != t.tok || SALE != t.tok)
		switch (tok)
		{
		case Token::STR: sval.~string(); break;
		case Token::SALE: sales.~Sales_data(); break;
		}
	if (STR == tok && STR == t.tok)
		sval = t.sval;
	else if (SALE == tok && SALE == t.tok)
		sales = t.sales;
	else
		copyUnion(t);
	tok = t.tok;
	return *this;
}

int main()
{
	Token t1, t2;
	t1 = string("sflsd");
	t2 = Sales_data("test1", 50, 5.5);
	cout << "t3 move assign, t4 copy construct :" << endl;
	Token t3 = std::move(t1), t4(t2);
	t2 = 4.5;
	cout << "used move assignment :" << endl;
	t1 = std::move(t4);
	cout << "t3 assigned to t4 :" << endl;
	t4 = t3;

	return 0;
}
