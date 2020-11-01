#pragma once
#include <string>
#include <sstream>
#include "LinkedListInterface.h"
using namespace std;

using namespace std;

template<class T>
class LinkedList: public LinkedListInterface<T>
{
private:

  struct Node {
    T data; // The data we are storing
    Node* next; // A pointer to the next node
    Node(const T& the_data, Node* next_val = NULL) :
      data(the_data) {next = next_val;}
  };

  Node *mylist, *head, *tail;
  int num_items;

public:

	LinkedList(void) {
    mylist = NULL;
    num_items = 0;
  };
	virtual ~LinkedList(void) {};

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertHead(T value) {
    if (!checkDuplicates(value)) {
    Node *ptr = mylist;
    mylist = new Node(value);
    mylist->next = ptr;
    num_items++;
    return;
    }
  };

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	virtual void insertTail(T value){
    if (!checkDuplicates(value)) {
    Node *ptr = mylist;
    mylist = new Node(value);
    mylist->next = ptr;
    num_items++;
    return;
    }
  };

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	virtual void insertAfter(T value, T insertionNode) {
    if (num_items == 0) {
      return;
    }
    Node *currentNode;
    currentNode = head;
    if (!checkDuplicates(value)) {
      while (currentNode->next != NULL) {
          if (currentNode->value == insertionNode) {
            Node *ptr = mylist;
            mylist = new Node(value);
            mylist->next = currentNode->next;
            currentNode->next = mylist;
            num_items++;
            return;
          }
          currentNode = currentNode->next;
        }
      if (currentNode == tail && currentNode->value == insertionNode) {
        Node *ptr = mylist;
        mylist = new Node(value);
        tail->next = mylist;
        mylist->next = NULL;
        tail = mylist;
        num_items++;
        return;
      }
    }
  };

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	virtual void remove(T value) {
    Node *currentNode;
    currentNode = head;
    Node *previousNode;
    previousNode = NULL;
    if (num_items < 1) {
      return;
    }
    if (checkDuplicates(value)) {
      while (currentNode->next != NULL) {
        if (currentNode->value == value) {
          if (head == currentNode) {
            head = head->next;
            delete currentNode;
            num_items--;
            return;
          } else {
            previousNode->next = currentNode->next;
            currentNode->next = NULL;
            delete currentNode;
            num_items--;
            return;
          }
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
      }
      if (num_items == 1) {
        previousNode = currentNode;
      }
      tail = previousNode;
      tail->next = NULL;
      delete currentNode;
      num_items--;
      if (num_items == 0) {
        head = NULL;
        tail = NULL;
      }
      return;
    }
  };

	/*
	clear

	Remove all nodes from the list.
	*/
	virtual void clear() {
    Node *currentNode;
    Node *previousNode;
    currentNode = head;
    while (currentNode->next != NULL) {
      previousNode = currentNode;
      currentNode = currentNode->next;
      delete previousNode;
    }
    delete currentNode;
    head = NULL;
    tail = NULL;
    num_items = 0;
  };

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	virtual T at(int index) {
    Node currentNode;
    if(index >= num_items) {
			throw std::out_of_range("At Error");
		} else {
			for (int i = 0; i < index; i++) {
        currentNode = currentNode->next;
      }
      return currentNode->value;
		}
  };

	/*
	size

	Returns the number of nodes in the list.
	*/
	virtual int size() {
    return num_items;
  };

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	virtual string toString() {
    stringstream ss;
    for(Node *ptr = mylist; ptr != NULL; ptr = ptr->next){
      ss << "ptr " << ptr << " val " << ptr->data << " next " << ptr-> next << endl;
    }
    return (ss.str());
  };

  bool checkDuplicates(T value) {
    Node *currentNode = head;
    while (currentNode->value != value) {
      if (currentNode->next == NULL) {
        return false;
      }
      currentNode = currentNode->next;
    }
    return true;
  }

};
