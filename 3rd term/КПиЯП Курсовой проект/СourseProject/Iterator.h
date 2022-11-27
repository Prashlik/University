#pragma once

template<class T>
struct Node
{
	T obj;
	Node* next;
	Node* prev;
};

template<class T>
class Iterator
{
private:
	Node<T>* current;
public:
	Iterator(Node<T>* first = nullptr) :current(first) 	{	}
	Iterator(const Iterator& obj)
	{
		current = obj.current;
	}
	void operator+(const int n)
	{
		for (int i = 0; i < n; i++) current = current->next;
	}
	void operator-(const int n)
	{
		for (int i = 0; i < n; i++) current = current->prev;
	}
	void operator++(int)
	{
		current = current->next;
	}
	void operator--(int)
	{
		current = current->prev;
	}
	void operator=(T data)
	{
		current->obj = data;
	}
	void operator=(Node<T>* obj)
	{
		current = obj;
	}
	T& operator*()
	{
		return current->obj;
	}
	bool operator ==(Node<T>* obj)
	{
		return (current == obj);
	}
	Node<T>* GetCurrent()
	{
		return current;
	}
};