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
	~Ring()
	{
		for (int i = 0; i < size; i++) DeleteOneNode(i);
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
	int NotEmpty()
	{
		if (current == NULL) return 0;
		else return 1;
	}
	int getsize()
	{
		return size;
	}

	void push(T data)
	{
		Node<T>* inserted;
		inserted = new Node<T>;
		inserted->obj = data;
		if (!NotEmpty())
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
	void DeleteOneNode(int n)
	{
		Iterator<T> temp = head; Node<T>* del;
		if (NotEmpty())
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
	void PrintRing()
	{
		if (NotEmpty())
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
	void DeleteRing()
	{
		for (int i = 0; i < size; i++) DeleteOneNode(i);
	}
	void sort(sort(T))
	{
		for (int k = 0; k < 2; k++) {
			Node<T>* unsorted, * min, * temp;
			unsorted = head;
			do
			{
				temp = unsorted->next;
				min = unsorted;
				do
				{
					if (temp->obj.sort(unsorted->obj)) min = temp;
					temp = temp->next;
				} while (temp != head);
				if (min != unsorted)
				{
					if (head == unsorted) head = min;
					min->prev->next = min->next;
					min->next->prev = min->prev;
					unsorted->prev->next = min;
					min->next = unsorted;
					min->prev = unsorted->prev;
					unsorted->prev = min;
				}
				else unsorted = unsorted->next;
			} while (unsorted->next != head);
		}
	}
	T& operator[](int numb)
	{
		Iterator<T> temp = head;
		for (int i = 0;i < numb;i++)
			temp++;

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