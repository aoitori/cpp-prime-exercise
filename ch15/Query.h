#pragma once
#ifndef QUERY_H
#define QUERY_H
#include<memory>
#include<string>
#include<iostream>
#include "D:\c++\textquery\TextQuery.h"
#include<algorithm>
#include<iterator>
using std::cout; using std::endl;
using std::string; using std::shared_ptr;
class Query_base
{
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual string rep() const = 0 { cout << "Query base rep" << endl; return " "; }
};

class Query
{
	friend Query operator~(const Query&);
	friend Query operator&(const Query&, const Query&);
	friend Query operator|(const Query&, const Query&);
	friend std::ostream& operator<< (std::ostream &os, const Query &query) { return os << query.rep(); }
public:
	Query(const string&);
	QueryResult eval(const TextQuery &t)const { return q->eval(t); }
	string rep() const { cout << "Query rep" << endl; return q->rep(); }
private:
	Query(shared_ptr<Query_base> query): q(query){}
	shared_ptr<Query_base> q;
};

class WordQuery : public Query_base
{
	friend class Query;
	WordQuery(const string &s) :query_word(s) { cout << "Word query constructor" << endl; }
	QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
	string rep() const override  { cout << "Word query rep" << endl; return query_word; }
	string query_word;
};
inline Query::Query(const string &s) :q(new WordQuery(s)) { cout << "Query constructor" << endl; }

class NotQuery : public Query_base
{
	friend Query operator~(const Query &);
	NotQuery(const Query &q) : query(q) { cout << "Not query constructor" << endl; }
	string rep() const override { cout << "Not query rep" << endl; return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const override;
	Query query;
};
inline Query operator~(const Query &operand)
{
	return shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery : public Query_base
{
protected:
	BinaryQuery(const Query &l, const Query &r, string s) : lhs(l), rhs(r), opSm(s) { cout << "Binary query constructor" << endl; }
	string rep() const override { cout << "Binary query rep" << endl; return "(" + lhs.rep() + " " + opSm + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	string opSm;
};

class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") { cout << "And query constructor" << endl; }
	QueryResult eval(const TextQuery&) const override;
};
inline Query operator&(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") { cout << "Or query constructor" << endl; }
	QueryResult eval(const TextQuery&) const override;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &t) const 
{
	auto right = rhs.eval(t), left = lhs.eval(t);
	auto ret_lines = std::make_shared<set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());
	return QueryResult(rep(), ret_lines, left.get_file());
}
QueryResult AndQuery::eval(const TextQuery&t) const
{
	auto left = lhs.eval(t), right = rhs.eval(t);
	auto ret_lines = std::make_shared<set<line_no>>();
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery &t) const
{
	auto result = query.eval(t);
	auto ret_lines = std::make_shared<set<line_no>>();
	auto beg = result.begin(), end = result.end();
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n)
	{
		if (beg == end || *beg != n)
			ret_lines->insert(n);
		else if (beg != end)
			++beg;
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}
#endif // !QUERY_H
