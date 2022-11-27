#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Iterator.h"

using namespace std;

template <typename T>
class Ring
{
private:

	Node<T>* head;
	Node<T>* current;
	int size;

public:

	Ring()
	{
		head = NULL;
		current = NULL;
		size = 0;
	}
	Ring(Ring& r)
	{
		head = r.head;
		current = r.current;
		size = r.size;
	}
	Ring(T x)
	{
		head = NULL;
		current = NULL;
		size = 0;
		push(x);
	}
	Ring(const Ring<T>& C)
	{
		this->head = NULL;
		this->current = NULL;
		this->size = 0;
		Node<T>* p = C.current;
		for (int i = 0; i < C.size; i++)
		{
			push(p->obj);
			p = p->next;
		}
	}
	~Ring()
	{
		for (int i = 0; i < size; i++) DeleteNode(i);
	}

	int IsNotEmpty()
	{
		if (current == NULL) return 0;
		else return 1;
	}
	int getsize()
	{
		return size;
	}
	void PrintRing()
	{
		if (IsNotEmpty())
		{
			Iterator<T> temp = head;
			for (int i = 0; i < size; i++)
			{
				cout << *temp;
				temp++;
			}
		}
		else cout << "||   List is empty!                           ||\n";
	}

	void push(T data)
	{
		Node<T>* inserted;
		inserted = new Node<T>;
		inserted->obj = data;
		if (!IsNotEmpty())
		{
			head = inserted;
			current = inserted;
			current->next = inserted;
			current->prev = inserted;
		}
		else
		{
			inserted->next = current->next;
			inserted->next->prev = inserted;
			current->next = inserted;
			inserted->prev = current;
		}
		size++;
		current = inserted;
	}
	T pop()
	{
		T tag;
		Node<T>* temp = current;
		tag = temp->obj;
		if (size == 1)
		{
			head = NULL;
			current = NULL;
		}
		else
		{
			current->next->prev = current->prev;
			current->prev->next = current->next;
			current = current->next;
		}
		if (temp == head) head = head->next;
		size--;
		delete temp;
		return tag;
	}

	void DeleteNode(int n)
	{
		Iterator<T> temp = head; Node<T>* del;
		if (IsNotEmpty())
		{
			n--; temp + n;
			current = temp.GetCurrent();
			del = current;
			if (size == 1)
			{
				head = NULL;
				current = NULL;
			}
			else
			{
				current->next->prev = current->prev;
				current->prev->next = current->next;
				current = current->next;
			}
			if (temp.GetCurrent() == head) head = head->next;
			size--;
			delete del;
		}
	}
	void Delete()
	{
		for (int i = 0; i < size;) DeleteNode(i);
	}
	void sort()
	{
		for (int k = 0; k < 2; k++) {
			Node<T>* uns, * min, * temp;
			uns = head;
			do
			{
				temp = uns->next;
				min = uns;
				do
				{
					if (temp->obj < uns->obj) min = temp;
					temp = temp->next;
				} while (temp != head);
				if (min != uns)
				{
					if (head == uns) head = min;
					min->prev->next = min->next;
					min->next->prev = min->prev;
					uns->prev->next = min;
					min->next = uns;
					min->prev = uns->prev;
					uns->prev = min;
				}
				else uns = uns->next;
			} while (uns->next != head);
		}
	}
	T& operator[](int numb)
	{
		Iterator<T> temp = head;
		temp + numb;

		return temp.GetCurrent()->obj;
	}
	Node<T>* begin()
	{
		return head;
	}
	Node<T>* tail()
	{
		return head->prev;
	}
};