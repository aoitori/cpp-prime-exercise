#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>

using namespace std;

class QueryResult;
class TextQuery
{
public:
	friend class QueryResult;
	TextQuery();
	TextQuery(ifstream &);
	QueryResult query(const string &);
private:
	shared_ptr<vector<string>> file_line;
	map<string, shared_ptr<set<size_t>>> que;
};

TextQuery::TextQuery(ifstream &in):file_line(new vector<string>)
{
	string line;
	for (size_t i = 0; getline(in, line); ++i)
	{
		file_line->push_back(line);
		istringstream words(line);
		string word;
		while (words >> word) 
		{
			auto &p = que[word];
			if (!p)
				p.reset(new set<size_t>);
			p->insert(i);
		}
	}
}

class QueryResult
{
public:
	QueryResult(const string &s, shared_ptr<set<size_t>> ln, shared_ptr<vector<string>> p)
		: findword(s), lineNumber(ln), fileLine(p){}
	friend ostream& print(ostream &os, QueryResult &qr);
private:
	const string findword;
	shared_ptr<vector<string>> fileLine;
	shared_ptr<set<size_t>> lineNumber;
};

QueryResult TextQuery::query(const string &w)
{
	static shared_ptr<set<size_t>> line_no(new set<size_t>);
	auto q = que.find(w);
	if (q != que.end())
		return QueryResult(w, q->second, file_line);
	else
		return QueryResult(w, line_no, file_line);
}

string  make_plura(size_t s)
{
	return (s < 2) ? " time" : " times";
}

ostream& print(ostream &os, QueryResult &qr) 
{
	os << qr.findword << " occurs " << qr.lineNumber->size() <<
		make_plura(qr.lineNumber->size()) << endl;
	for (auto num : *qr.lineNumber)
		os << "\t(line " << num + 1 << ")"
		<< *(qr.fileLine->begin() + num) << endl;
	os << "next word: ";
	return os;
}
#endif // !TEXTQUERY_H_H