// File: list.cpp
// Author: Juntao Wang & Nam Pham
// Data: April 19, 2018

template <class T>
Node<T>::Node()
{
	data = 0;
	next = NULL;
  prev = NULL;
}

template <class T>
Node<T>::Node(T d)
{
	data = d;
	next = NULL;
  prev = NULL;
}

template <class T>
Node<T>::Node(T d, Node<T>* n)
{
	data = d;
	next = n;
  prev = NULL;
}

// default constructor
template <class T>
List<T>::List()
{
  head = NULL;
  tail = NULL;
	count = 0;
}

// copy constructor
template <class T>
List<T>::List(const List<T>& src)
{
	deepCopy(src);
}

// copy, private
template <class T>
void List<T>::deepCopy(const List<T>& src)
{
	head = NULL;
	tail = NULL;
	count = 0;
	if (src.head != NULL)
	{
		Node<T>* current = src.head;
		this->add(current->data);
		for (int i = 1; i < src.count; i++)
		{
			current = current->next;
			this->add(current->data);
		}
	}
}

//===================================================================================================
// append
template <class T>
void List<T>::add(T item)
{
  Node<T>* node = new Node<T>(item);
	if (head == NULL)  // list is empty
  {
    head = node;
    tail = node;
  }
	else
	{
    tail->next = node;
    node->prev = tail;
    tail = node;
	}
	count++;
}

//===================================================================================================
// size
template <class T>
int List<T>::size() const
{
	return count;
}

//===================================================================================================
// toString
template <class T>
std::string List<T>::toString() const
{
	std::stringstream s;
	s << "[";
	if (head == NULL)
	{
		s << "]";
		return s.str();
	}
	Node <T> *temp = head;
	while (temp->next!= NULL) //print everything up till second to last item
	{
		s << temp->data;
		s << ",";
		temp = temp->next;
	}
	s << temp->data;
	s << "]";
	return s.str();
}

//===================================================================================================
// find
template <class T>
int List<T>::index(T item) const
{
	Node <T> *temp = head;
	for (int i = 0; i < count; i++)
  {
    if (item == temp->data)
      {
				return i;
			}
		temp = temp->next;
  }
  return -1;
}

//===============================================================================================================
// insert
template <class T>
void List<T>::insert(int index, T item)
{
	if ((index >= count) || (index < 0))
	{
		throw IndexError();
	}
	else if (index == 0) // insert at head
	{
		Node<T>* node = new Node<T>(item, head); //create new node, with pointer poiting to current head
		head = node;
		count++;
	}
	else // insert in middle
	{
    Node<T>* node = new Node<T>(item);
    if (index <= count/2-1)
    {
      Node<T>* current = head;
    	for(int i = 0; i < index - 1; i++) //move the pointer from head to index -1;
  		{
  			current = current->next;
  		}
  		node->next = current->next;
      node->prev = current;
      current->next->prev = node;
  		current->next = node;
    }
    else
    {
      Node<T>* current = tail;
      for(int i = count-1; i > index; i--) //move the pointer from tail to index;
      {
        current = current->prev;
      }
      node->next = current;
      node->prev = current->prev;
      current->prev->next = node;
      current->prev = node;
    }
    count++;
	}
}

// remove
template <class T>
void List<T>::remove(int index)
{
	if ((index >= count) || (index < 0))
	{
		throw IndexError();
	}
	else if (index == 0)
	{
		Node <T>* temp = head->next;
		delete head;
		head = temp;
		head->prev = NULL;
		count--;
	}
	else if (index == count - 1)
	{
		Node <T>* temp = tail->prev;
		delete tail;
		tail = temp;
		tail->next = NULL;
		count--;
	}
	else
	{
		if (index <= count/2-1)
		{
			Node<T>* current = head;
			for(int i = 0; i < index-1; i++) //move the pointer from head to index -1;
			{
				current = current->next;
			}
			Node<T>* connect = current->next->next; //THis is the node we're connecting to (index +1)
			delete current->next;
			current->next = connect;
			connect->prev = current;
		}
		else
		{

			Node<T>* current = tail;
			for(int i = count-1; i > index+1; i--)
			{
				current = current->prev;
			}

			Node<T>* connect = current->prev->prev;
			delete current->prev;
			current->prev = connect;
			connect->next = current;
		}
		count--;
	}
}

// insertion
template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
	return os << list.toString();
}

// indexing
template <class T>
T& List<T>::operator[](int index) const
{
	if ((index >= count) || (index < 0))
	{
		throw IndexError();
	}
	else if (index == 0)
		return head->data;
  else if (index == count-1)
    return tail->data;
	else
	{
    if (index <= count/2-1)
    {
      Node<T>* current = head;
      for(int i = 0; i < index; i++) //move the pointer from head to index -1;
      {
        current = current->next;
      }
      return current->data;
    }
    else
    {
      Node<T>* current = tail;
      for(int i = count-1; i > index; i--) //move the pointer from tail to index +1;
      {
        current = current->prev;
      }
      return current->data;
    }
	}
}

// destructor
template <class T>
List<T>::~List()
{
	while (head != NULL)
	{
		Node<T>* temp = head->next; //make temp node (stores 2nd item to head)
		delete head; //delete head
		head = temp; //make temp the new head
	}
	tail = NULL;
	count = 0;
}

// assignment
template <class T>
List<T>& List<T>::operator=(const List<T>& src)
{
	if (this != &src)
	{
		this->~List();
		deepCopy(src);
	}
	return *this;
}

// concatenation
template <class T>
List<T>& List<T>::operator+=(const List<T>& src)
{
	if (this == &src)
	{
		List<T> tempList(src);
		Node<T> *current = tempList.head;
		this->add(current->data);
		for (int i = 1; i < tempList.count; i++)
		{
			current = current->next;
			this->add(current->data);
		}
		tempList.~List();
	}
	else
	{
		Node<T> *current = src.head;
		this->add(current->data);
		for (int i = 1; i < src.count; i++)
		{
			current = current->next;
			this->add(current->data);
		}
	}
	return *this;
}
