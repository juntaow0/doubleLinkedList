// File: list.h
// Author: Juntao Wang & Nam Pham
// Data: April 19, 2018

#ifndef DLIST
#define DLIST

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

template <class T>
class Node
{
	public:
		Node();
		Node(T d);
		Node(T d, Node<T>* n);

	private:
		T data;
		Node<T>* next;
    Node<T>* prev;

template <class U>
friend class List;
};

template <class T>
class List
{
private:
  Node<T> *head;
  Node<T> *tail;
  int count;
	void deepCopy(const List<T>& src);

public:
  List();                   // default constructor
  List(const List<T>& src);    // copy constructor
  ~List();                  // destructor

  void add(T item);                 // append
  int size() const;                           // return the number of items
  int index(T item) const;          // return the index of item, or -1 if not found
  void insert(int index, T item);   // insert item in position index
  void remove(int index);                     // remove item in position index
  std::string toString() const;               // return string form of the list

  T& operator[](int index) const;   // indexing
  List& operator=(const List<T>& src);           // assignment
  List& operator+=(const List<T>& src);          // short hand for concatenation
};

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list);


class IndexError
{
	public:
		std::string message = "Bad index!";
};

#include "Dlist.cpp"

#endif
