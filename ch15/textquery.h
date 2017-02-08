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

using namespace std; using std::vector; using std::string;
static string punchs(",./?;:\'\", ");
class QueryResult;
class TextQuery
{
public:
	using line_no = vector<string>::size_type;
	friend class QueryResult;
	TextQuery() = default;
	TextQuery(ifstream &);
	QueryResult query(const string &) const;
private:
	shared_ptr<vector<string>> file_line;
	map<string, shared_ptr<set<line_no>>> que;
	string removepunch(const string &w)
	{
		if (w.find_first_of('\"') != string::npos)
			return w.substr(1, w.find_last_not_of(punchs));
		else
			return w.substr(0, w.find_last_not_of(punchs) + 1);
	}
};

TextQuery::TextQuery(ifstream &in):file_line(new vector<string>)
{
	string line;
	for (line_no i = 0; getline(in, line); ++i)
	{
		file_line->push_back(line);
		istringstream words(line);
		string word;
		while (words >> word) 
		{
			
			auto &p = que[removepunch(word)];
			if (!p)
				p.reset(new set<line_no>);
			p->insert(i);
		}
	}
}

class QueryResult
{
public:
	using line_no = TextQuery::line_no;
	QueryResult(const string &s, shared_ptr<set<line_no>> ln, shared_ptr<vector<string>> p)
		: findword(s), lineNumber(ln), fileLine(p){}
	friend ostream& print(ostream &os, QueryResult &qr);
	friend ostream& operator<<(ostream&, const QueryResult&);
	set<line_no>::iterator begin() { return lineNumber->begin(); }
	set<line_no>::iterator end() { return lineNumber->end(); }
	shared_ptr<vector<string>> get_file() const { return fileLine; }
private:
	const string findword;
	shared_ptr<vector<string>> fileLine;
	shared_ptr<set<line_no>> lineNumber;
};

QueryResult TextQuery::query(const string &w) const
{
	static shared_ptr<set<line_no>> line_no(new set<line_no>);
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
ostream& operator<<(ostream &os, const QueryResult &t)
{
	os << t.findword << " occurs " << t.lineNumber->size() <<
		make_plura(t.lineNumber->size()) << endl;
	for (auto num : *t.lineNumber)
		os << "\t(line " << num + 1 << ")"
		<< t.fileLine->at(num) << endl;
	return os;
}
#endif // !TEXTQUERY_H_H
