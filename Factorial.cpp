﻿//Factorial
//by Lizhi
//date 2018.9.21

#include "stdafx.h"
#include "LinkedList.hpp"
#include <iostream>
#include <string>
using namespace std;

char cJudge(string str);
string Print(string str);
bool Cal(int num, List<int>* ptr);
List<int>* Carry(List<int>* ptr);

int main()
{
	cout << "         Factorial Calculator" << endl;
	cout << "                       by Lizhi" << endl;
	bool bExit = false;
	string com = "Y";
	string str;
	while (!bExit)
	{
		if (cJudge(com) == 'Y')
		{
			cout << "Please enter an integer:";
			cin >> str;
			cout << Print(str) << endl;
			cout << "Continue(Y/N)? ";
			cin >> com;
		}
		else if (cJudge(com) == 'N')
		{
			bExit = true;
		}
		else if (cJudge(com) == 'X')
		{
			cout << "Continue(Y/N)? ";
			cin >> com;
		}
	}
	return 0;
}

char cJudge(string str)
{
	string pArray[10] = { "Y","y","YES","Yes","yes","N","n","NO","No","no" };
	for (int i = 0; i < 10; i++)
	{
		if (str == pArray[i])
		{
			return i < 5 ? 'Y' : 'N';
		}
	}
	return 'X';
}

string Print(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] < 48 || str[i] > 57)
		{
			return "Enter Error";
		}
	}
	if (atoi(str.c_str()) == 0)
	{
		return "1";
	}
	List<int>Total_List;
	LinkNode<int> *current = Total_List.getHead();
	current->data = 1;
	current->link = NULL;
	for (int i = 1; i <= atoi(str.c_str()); i++)
	{
		List<int> *ptr = &Total_List;
		if (!Cal(i, &Total_List))
		{
			return "Calculate Error";
		}
	}
	return Total_List.Print();
}

bool Cal(int num, List<int>* ptr)
{
	if (ptr == NULL)
	{
		return false;
	}
	LinkNode<int> *current = ptr->getHead();
	while (current != NULL)
	{
		current->data *= num;
		current = current->link;
	}
	if (Carry(ptr) == NULL)
	{
		return false;
	}
	return true;
}

List<int> *Carry(List<int> *ptr)
{
	LinkNode<int> *current = ptr->getHead();
	while (current != NULL)
	{
		if (current->data / 10 != 0)
		{
			if (current->link != NULL)
			{
				current->link->data += current->data / 10;
				current->data % 10;
			}
			else
			{
				current->link = new LinkNode<int>();
				current->link->data = current->data / 10;
				ptr->Locate(ptr->Length())->link = NULL;
			}
			current->data = current->data % 10;
		}
		current = current->link;
	}
	return ptr;
}
