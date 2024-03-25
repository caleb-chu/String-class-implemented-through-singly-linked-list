
#include "string.hpp"
#include "list.hpp"
#include <iostream>
using namespace std;

String::String(const char *s)
	:head{list::from_string(s)}
{
}

String::String(const String &s)
	:head{list::copy(s.head)}
{
}

String::String(String &&s)
	:head(s.head)
{
	
}

void String::swap(String &s)
{
	list::Node* temp = head;
	head = s.head;
	s.head = temp;
	temp = nullptr;
}

String &String::operator=(const String &s)
{
	if (&s == this)
		return *this;
	if (head)
	{
		list::free(head);
	}
	head = list::copy(s.head);
	return *this;
}

String &String::operator=(String &&s)
{
	if (&s == this)
		return *this;
	list::free(head);
	head = s.head;
	s.head = nullptr;
	return *this;
}

bool String::in_bounds(int index) const
{
	return index >= 0 && index < size();
}

char String::operator[](int index) const
{
	if (in_bounds(index))
	{
		list::Node* temp = list::nth(head, index);
		return temp->data;
	}
	else
	{
		cout << "ERROR: out of bounds";
		if (head == nullptr)
			return '\0';
		else
			return head->data;
	}
}

int String::size() const
{
	return list::length(head);
}

String String::reverse() const
{
	list::Node* reversed{list::reverse(head)};
	return String(reversed);
}

int String::indexOf(char c) const
{
	if (!head && !c)
		return 0;
	else
	{
		list::Node* temp = list::find_char(head, c);
		return !temp ? -1 : list::index(head, temp);
	}
}

int String::indexOf(const String &s) const
{
	if (!head && !s.head)
	{
		return 0;
	}
	else
	{
		list::Node* temp = list::find_list(head, s.head);
		return !temp ? -1 : list::index(head, temp);
	}
}

bool String::operator==(const String& s) const
{
	return list::compare(head, s.head) == 0;
}

strong_ordering String::operator<=>(const String &s) const
{
	return list::compare(head, s.head) <=> 0;
}

String String::operator+(const String& s) const
{
	String newStr{list::append(head, s.head)};
	return newStr;
}

String &String::operator+=(const String& s)
{
	list::Node* last = list::last(head);
	list::Node* dup = list::copy(s.head);
	last->next = dup;
	return *this;
}

void String::print(ostream &out) const
{
	list::print(out, head);
}

void String::read(istream &in)
{
	if (head)
		list::free(head);
	else
	{
		char temp[1024];
		in >> temp;
		head = list::from_string(temp);
	}
}

String::~String() 
{
	list::free(head);
}

String::String(list::Node* head)
	:head{head}
{
}

ostream &operator<<(ostream &out, const String &s)
{
	s.print(out);
	return out;
}

istream &operator>>(istream &in, String &s)
{
	s.read(in);
	return in;
}
