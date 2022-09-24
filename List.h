#ifndef LIST_H
#define LIST_H
/* List.h
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
*/

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  // EFFECTS: creates an empty list by intializing first and last nodes to nullptr.
  List() : first(nullptr), last(nullptr), num_elements(0) {}
  
  // EFFECTS: creates a new list from a copy of other.
  List(const List<T> &other) : List() {
    copy_all(other);
  }

  // MODIFIES: *this
  // EFFECTS: removes all elements from the existing list.  Copies all elements from rhs to the 
  // existing list.  If the existing list is the same as rhs then nothing is modified.
  List<T> & operator=(const List<T> &rhs) {
    if (this != &rhs) {
      clear();
      copy_all(rhs);
    }
    return *this;
  }

  // EFFECTS: removes all elements from the list.
  ~List() {
    clear();
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return !first && !last;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return num_elements;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    if (empty()) {
      Node *new_node = new Node{nullptr, nullptr, datum};
      last = first = new_node;
    } else {
      Node *new_node = new Node{first, nullptr, datum};
      first = first->prev = new_node;    
    }
    num_elements += 1;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    if (empty()) {
      Node *new_node = new Node{nullptr, nullptr, datum};
      first = last = new_node;
    } else {
      Node *new_node = new Node{nullptr, last, datum};
      last = last->next = new_node;
    } 
    num_elements += 1;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *new_first = first->next;   
    delete first;
    first = new_first;
    
    if (!first) {
      last = nullptr;
    } else {
      first->prev = nullptr;    
    }
    num_elements -= 1;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *new_last = last->prev; 
    delete last;
    last = new_last;
    
    if (!last) {
      first = nullptr;
    } else {
      last->next = nullptr;
    }
    num_elements -= 1;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    assert(empty());
    for (Node *node_ptr = other.first; node_ptr; node_ptr = node_ptr->next) {
      push_back(node_ptr->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int num_elements;

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator() : node_ptr(nullptr) {}
    
    // REQUIRES: The current element is dereferenceable.
    T& operator*() const {
      assert(node_ptr);  
      return node_ptr->datum;
    }

    // REQUIRES: The current element is dereferenceable.
    // EFFECTS: Moves current iterator position to next element in the list.
    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    // EFFECTS: Returns true if rhs Iterator points to the same element as lhs Iterator.  
    // Otherwise returns false.
    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    // EFFECTS: Returns true if rhs Iterator does not point to the same element as lhs Iterator.  
    // Otherwise returns false.
    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    
    // add any friend declarations here
    friend class List;
    // construct an Iterator at a specific position
    Iterator(Node *p) {
      node_ptr = p;
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    assert(i.node_ptr);
    if (!i.node_ptr->prev) { // erasing *first
      pop_front(); 
    } else if (!i.node_ptr->next) { // erasing *last
      pop_back();
    } else {
      i.node_ptr->next->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = i.node_ptr->next;
      delete i.node_ptr;
      num_elements -= 1;   
    }     
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if (!i.node_ptr) { // inserting *last
      push_back(datum);
    } else if (!i.node_ptr->prev) { // inserting *first
      push_front(datum); 
    } else {
      Node *new_node = new Node{i.node_ptr, i.node_ptr->prev, datum};
      i.node_ptr->prev->next = new_node;
      i.node_ptr->prev = new_node;
      num_elements += 1;   
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
