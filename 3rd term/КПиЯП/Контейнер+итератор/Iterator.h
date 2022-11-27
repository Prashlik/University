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
	Node<T>* Current;
public:
	Iterator(Node<T>* first = nullptr) :Current(first) {	}
	Iterator(const Iterator& obj)
	{
		Current = obj.Current;
	}
	void operator+(const int n)
	{
		for (int i = 0; i < n; i++) Current = Current->next;
	}
	void operator-(const int n)
	{
		for (int i = 0; i < n; i++) Current = Current->prev;
	}
	void operator++(int)
	{
		Current = Current->next;
	}
	void operator--(int)
	{
		Current = Current->prev;
	}
	void operator=(T data)
	{
		Current->obj = data;
	}
	void operator=(Node<T>* obj)
	{
		Current = obj;
	}
	T& operator*()
	{
		return Current->obj;
	}
	bool operator==(Node<T>* obj)
	{
		return (Current == obj);
	}
	Node<T>* GetCurrent()
	{
		return Current;
	}
};