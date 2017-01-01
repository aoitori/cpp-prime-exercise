#ifndef Message_H_
#define Message_H_
#include <set>
#include <string>
#include <iostream>
class Folder;

class Message
{
	friend class Folder;
public:
	explicit Message(const std::string &str = " ") :contents(str) {}
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	
	void print_msg() { std::cout << contents << std::endl; }
	void save(Folder&);
	void remove(Folder&);
	friend void swap(Message&, Message&);
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folder(const Message&);
	void remove_from_Folders();
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
};

class Folder
{
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder &f) : msgs(f.msgs) { add_to_Message(f); }
	Folder& operator=(const Folder&);
	void add_to_Message(const Folder &f) { for (auto m : f.msgs) m->addFldr(this); }
	void remove_from_Message() { for (auto m : msgs) m->remFldr(this); }
	void print_fld() {
		for (const auto &m : msgs)
			std::cout << m->contents << " " << std::endl;
	}
	~Folder() { remove_from_Message(); }
private:
	void addMsg(Message*);
	void remMsg(Message*);
	std::set<Message*> msgs;
};

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folder(const Message &m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}

void Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(this);
}

Message::Message(const Message& m):contents(m.contents), folders(m.folders)
{
	add_to_Folder(m);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folder(rhs);
	return *this;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;
	lhs.remove_from_Folders();
	rhs.remove_from_Folders();
	swap(lhs.contents, rhs.contents);
	swap(lhs.folders, rhs.folders);
	lhs.add_to_Folder(lhs);
	rhs.add_to_Folder(rhs);
}

void Folder::addMsg( Message *m)
{
	msgs.insert(m);
}

void Folder::remMsg( Message *m)
{
	msgs.erase(m);
}

Folder& Folder::operator=(const Folder &f)
{
	remove_from_Message();
	msgs = f.msgs;
	add_to_Message(f);
	return *this;
}
#endif // !Message_H_
