#include "list.hpp"
#include <string.h>
#include <iostream>
using namespace std;

list::Node* list::from_string(const char* s)
{
	Node* head = nullptr;
	for (int i = strlen(s)-1; i >= 0; i--)
	{
		Node* newNode = new Node;
		newNode->data = s[i];
		newNode->next = head;
		head = newNode;

	}
	return head;
}

void list::free(Node* head)
{
	Node* current = head;
	for (; current != nullptr;)
	{
		Node* temp = current;
		current = current->next;
		delete temp;
	}
}

void list::print(ostream& out, Node* head)
{
	Node* current = head;
	for(; current != nullptr; current = current->next)
	{
		out << current->data;
	}
}

int list::length(Node* head)
{
	Node* current = head;
	int count = 0;
	for(; current != nullptr; current = current->next)
	{
		count++;
	}
	return count;
}

list::Node* list::copy(Node* head)
{
	if (head == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new Node{head->data, copy(head->next)};
	}
}

int list::compare(Node* lhs, Node* rhs)
{
	Node* left = lhs;
	Node* right = rhs;
	for (; left != nullptr && right != nullptr; left=left->next, right=right->next)
	{
		if(left->data < right->data)
			return -1;
		else if(right->data < left->data)
			return 1;
	}
	if (left == nullptr && right != nullptr)
	{
		return -1;
	}
	else if (right == nullptr && left != nullptr)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
}

int list::compare(Node* lhs, Node* rhs, int n)
{
	Node* left = lhs;
	Node* right = rhs;
	for (int i = 0; i < n; left=left->next, right=right->next, ++i)
	{
		if (left == nullptr && right == nullptr)
			return 0;
		else if (left == nullptr && right != nullptr)
			return -1;
		else if (right == nullptr && left != nullptr)
			return 1;
		else if(left->data < right->data)
			return -1;
		else if(right->data < left->data)
			return 1;
	}
	return 0;
}

list::Node* list::reverse(Node* head)
{
	Node* reversedHead = nullptr;
	for (Node* current = head; current != nullptr; current = current->next)
	{
		Node* newNode = new Node;
		newNode->data = current->data;
		newNode->next = reversedHead;
		reversedHead = newNode;
	}
	return reversedHead;
}

list::Node* list::append(Node* lhs, Node* rhs)
{
	return !lhs ? list::copy(rhs) : new Node{lhs->data, list::append(lhs->next, rhs)};
}

int list::index(Node* head, Node* node)
{
	int count = 0;
	if (!node)
		return -1;
	for (Node* temp = head; temp != nullptr; temp = temp->next)
	{
		if (temp == node)
		{
			return count;
		}
		else
		{
			count++;
		}
	}
	return -1;
}
list::Node* list::last(Node* head)
{
	return !head->next ? head : list::last(head->next);
}

list::Node* list::find_char(Node*head, char c)
{
	if(!c)
	{
		return nullptr;
	}
	for(Node* temp = head; temp != nullptr; temp = temp->next)
	{
		if (temp->data == c)
			return temp;
	}
	return nullptr;
}

list::Node* list::find_list(Node* haystack, Node* needle)
{
	int length = list::length(needle);
	if (length == 0)
		return haystack;
	for(Node* temp = haystack; temp = find_char(temp, needle->data); temp=temp->next)
	{
		if (list::compare(temp, needle, length) == 0)
			return temp;
	}
	return nullptr;
}

list::Node* list::nth(Node* head, int n)
{
	return !n ? head : list::nth(head->next, n-1);
}
