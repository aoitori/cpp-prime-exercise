#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
using std::map; using std::ostream; using std::cerr;
using std::shared_ptr; using std::vector; using std::set;
using std::string; using std::ifstream; using std::endl;
static string punchs(",./?;:\'\", ");
string  make_plura(size_t s){return (s < 2) ? " time" : " times";}

class DebugDelete
{
public:
	DebugDelete(ostream &s = cerr) : os(s) {}
	template <typename T> void operator()(T *p)const { os << "deleting unique_ptr" << endl; delete p; }
private:
	ostream &os;
};
class TextQuery
{
public:
	using line_no = vector<string>::size_type;
	friend class QueryResult;
	TextQuery() = default;
	TextQuery(ifstream &);
	auto query(const string &) const;
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

TextQuery::TextQuery(ifstream &in) :file_line(new vector<string>(), DebugDelete())
{
	string line;
	for (line_no i = 0; getline(in, line); ++i)
	{
		file_line->push_back(line);
		std::istringstream words(line);
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

auto TextQuery::query(const string &w) const
{
	static shared_ptr<set<line_no>> line_no(new set<line_no>, DebugDelete());
	auto q = que.find(w);
	if (q != que.end())
		return std::make_tuple(w, q->second, file_line);
	else
		return std::make_tuple(w, line_no, file_line);
}
#endif
