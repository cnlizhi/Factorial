//LinkedList.hpp

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <cassert>
#include <string>
using namespace std;

#ifndef INSMOD_INF_INR
#define INSMOD_INF_INR

enum InsMod { INF, INR };//定义向前还是向后生成

#endif

template <typename T>
struct LinkNode
{
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr = NULL)
	{
		link = ptr;
	}
	LinkNode(const T &item, LinkNode<T> *ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};

template <typename T>
class List
{
public:
	List();
	List(const T &x);
	List(List<T> &L);
	~List();
	void makeEmpty();
	int Length() const;
	LinkNode<T> *getHead() const;
	LinkNode<T> *Search(const T &x);
	LinkNode<T> *Locate(int i);
	bool getData(int i, T&x)const;
	bool setData(int i, T &x);
	bool Insert(int i, T &x);
	bool Remove(int i, T &x);
	bool IsEmpty() const;
	void Inverse();
	void input(T endTag, InsMod im = INR);
	void output();
	List<T> &operator = (List<T> &L);
	friend ostream& operator<< (ostream &out, List<T> &L);
	friend istream& operator>> (istream &in, List<T> &L);
	string Print();
protected:
	LinkNode<T> *first;
	void inputFront(T endTag);
	void inputRear(T endTag);
};

template <typename T>
List<T>::List()
{
	first = new LinkNode<T>;
}

template <typename T>
List<T>::List(const T &x)
{
	first = new LinkNode<T>(x);
}

template <typename T>
List<T>::List(List<T> &L)
{
	T value;
	LinkNode<T> *srcptr = L.first();
	LinkNode<T> *destptr = first = new LinkNode<T>;
	while (srcptr->link)
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
}

template <typename T>
List<T>::~List()
{
	makeEmpty();
	delete first;
}

template <typename T>
void List<T>::makeEmpty()
{
	LinkNode<T> *q;
	while (first->link)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	return;
}

template <typename T>
int List<T>::Length() const
{
	LinkNode<T> *p = first->link;
	int count = 0;
	while (p) {
		p = p->link;
		count++;
	}
	return count;
}

template <typename T>
LinkNode<T> *List<T>::getHead() const
{
	return first;
}

template <typename T>
LinkNode<T> *List<T>::Search(const T &x)
{
	LinkNode<T> *current = first->link;
	while (current && current->data != x)
	{
		current = current->link;
	}
	return current;
}

template <typename T>
LinkNode<T> *List<T>::Locate(int i)
{
	if (i < 0)
	{
		return NULL;
	}
	LinkNode<T> *current = first;
	int k = 0;
	while (current && k < i)
	{
		current = current->link;
		k++;
	}
	return current;
}

template <typename T>
bool List<T>::getData(int i, T &x) const
{
	if (i <= 0)
	{
		return NULL;
	}
	LinkNode<T> *current = Locate(i);
	if (!current)
	{
		return false;
	}
	else
	{
		x = current->data;
		return true;
	}
}

template <typename T>
bool List<T>::setData(int i, T &x)
{
	if (i <= 0)
	{
		return false;
	}
	LinkNode<T> *current = Locate(i);
	if (!current)
	{
		return false;
	}
	else
	{
		current->data = x;
		return true;
	}
}

template <typename T>
bool List<T>::Insert(int i, T &x)
{
	LinkNode<T> *current = Locate(i);
	if (!current)
	{
		return false;
	}
	LinkNode<T> *newNode = new LinkNode<T>(x);
	if (!newNode)
	{
		cerr << "Memory Allocating Error!" << endl;
		exit(1);
	}
	newNode->link = current->link;
	current->link = newNode;
	return true;
}

template <typename T>
bool List<T>::Remove(int i, T &x)
{
	LinkNode<T> *current = Locate(i - 1);
	if (!current || !current->link)	return false;
	LinkNode<T> *del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

template <typename T>
void List<T>::output()
{
	LinkNode<T> *current = first->link;
	while (current)
	{
		cout << current->data << endl;
		current = current->link;
	}
}

template <typename T>
List<T> &List<T>::operator = (List<T> &L)
{
	T value;
	LinkNode<T> *destptr = first, *srcptr = L.first;
	makeEmpty();
	while (srcptr->link)
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
	return *this;
}

template <typename T>
void List<T>::input(T endTag, InsMod im)
{
	if (im == INF)
	{
		inputFront(endTag);
	}
	else
	{
		inputRear(endTag);
	}
	return;
}

template <typename T>
void List<T>::inputFront(T endTag)
{
	LinkNode<T> *newNode;
	T val;
	cin >> val;
	while (val != endTag)
	{
		newNode = new LinkNode<T>(val);
		if (!newNode)
		{
			cerr << "Memory allocating error!" << endl;
			exit(1);
		}
		newNode->link = first->link;
		first->link = newNode;
		cin >> val;
	}
	return;
}

template <typename T>
void List<T>::inputRear(T endTag)
{
	LinkNode<T> *newNode, *last = first;
	T val;
	while (last->link != NULL) last = last->link;
	cin >> val;
	while (val != endTag)
	{
		newNode = new LinkNode<T>(val);
		if (!newNode)
		{
			cerr << "Memory allocating error!" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
		cin >> val;
	}
	last->link = NULL;
	return;
}

template <typename T>
void List<T>::Inverse()
{
	LinkNode<T> *h, *p, *pr;
	h = NULL;
	p = first->link;
	while (p) {
		pr = h;
		h = p;
		p = h->link;
		h->link = pr;
	}
	first->link = h;
}

template <typename T>
bool List<T>::IsEmpty() const
{
	return (first->link == NULL) ? true : false;
}

template <typename T>
ostream& operator<< (ostream &out, List<T> &L)
{
	LinkNode<T> *current = L.first->link;
	while (current)
	{
		out << current->data;// << '\t';
		current = current->link;
	}
	out << endl;
	return out;
}

template <typename T>
istream& operator>> (istream &in, List<T> &L)
{
	LinkNode<T> *newNode, *last;
	T val;
	L.makeEmpty();
	last = L.first;
	while (!in.eof())
	{
		in >> val;
		newNode = new LinkNode<T>(val);
		assert(newNode);
		last->link = newNode;
		last = newNode;
	}
	last->link = NULL;
	return in;
}

template <typename T>
string List<T>::Print()
{
	string str;
	str.clear();
	LinkNode<T> *current = this->first;
	while (current)
	{
		string buffer = str;
		str = current->data + 48;
		str.append(buffer);
		buffer.clear();
		current = current->link;
	}
	return str;
}

#endif