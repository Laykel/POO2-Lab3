/* ---------------------------------------------------------------------------------
 * Lab       : Laboratoire 3 - Liste
 * File      : ListImpl.cpp
 * Author(s) : Alison Savary et Luc Wachter
 * Date      : 11.04.2019
 *
 * Goal      : Implement a generic doubly linked list
 *
 * Compiler  : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */

#ifndef LISTIMPL_HPP
#define LISTIMPL_HPP

#include "List.hpp"
#include <stdexcept>

// Friend functions -----------------------------------------------------------------

// Output stream operator
template <typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& list) {
//   auto node = list.head;

//   while (node != nullptr) {
//      os << node->data << " ";
//      node = node->next;
//   }

   for (const T& elem : list) {
      os << elem << " ";
   }

   return os;
}

// GenericIterator inner class ------------------------------------------------------

// Generic iterator constructor
template <typename T>
List<T>::GenericIterator::GenericIterator(Node* pointer)
: pointer(pointer) {}

// Prefix incrementation operator
template <typename T>
typename 
List<T>::GenericIterator::GenericIterator& List<T>::GenericIterator::operator++() {
   pointer = pointer->next;
   return *this;
}

// Postfix incrementation operator
template <typename T>
const typename 
List<T>::GenericIterator::GenericIterator List<T>::GenericIterator::operator++(int) {
   GenericIterator tmp(*this);
   ++*this;
   return tmp;
}

// Prefix decrementation operator
template <typename T>
typename 
List<T>::GenericIterator::GenericIterator& List<T>::GenericIterator::operator--() {
   pointer = pointer->previous;
   return *this;
}

// Postfix decrementation operator
template <typename T>
const typename 
List<T>::GenericIterator::GenericIterator List<T>::GenericIterator::operator--(int) {
   GenericIterator tmp(*this);
   --*this;
   return tmp;
}

// Equality logic operator
template <typename T>
bool List<T>::GenericIterator::operator==(const GenericIterator& val) const {
   return (pointer == val.pointer);
}

// Inequality logic operator
template <typename T>
bool List<T>::GenericIterator::operator!=(const GenericIterator& val) const {
   return !(val == *this);
}

// Iterator inner class -------------------------------------------------------------

template <typename T>
List<T>::Iterator::Iterator(Node* pointer)
: GenericIterator(pointer) {}

// Member access operator (read/write)
template <typename T>
T& List<T>::Iterator::operator*() const {
   return this->pointer->data;
}

// Member property access operator (read/write)
template <typename T>
T& List<T>::Iterator::operator->() const {
   return this->pointer->data;
}

// ConstIterator inner class --------------------------------------------------------

template <typename T>
List<T>::ConstIterator::ConstIterator(Node* pointer)
: GenericIterator(pointer) {}

// Member access operator (read-only)
template <typename T>
const T& List<T>::ConstIterator::operator*() const {
   return this->pointer->data;
}

// Member property access operator (read-only)
template <typename T>
const T& List<T>::ConstIterator::operator->() const {
   return this->pointer->data;
}

// Member functions ---------------------------------------------------------------

// No parameter constructor
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), beforeHead(nullptr), 
                  afterTail(nullptr), _size(0) {}

// Initializer list constructor
template <typename T>
List<T>::List(const std::initializer_list<T>& args) : List() {
   _size = args.size();
   for (const T& elem : args) {
      append(elem);
   }
}

// Copy constructor
template <typename T>
List<T>::List(const List& other) : List() {
   // Call assignment operator
   *this = other;
}

// Destructor
template <typename T>
List<T>::~List() {
   destroy();
}

// Assignment operator
template <typename T>
List<T>& List<T>::operator= (const List& other) {
   // No-op if the other list is the current one
   if (&other == this) {
      return *this;
   }

   // Deallocate memory of current list
   destroy();

   // Reinitialize
   head = tail = nullptr;
   _size = other.size();

   // Append elements
   for (const T& elem : other) {
      append(elem);
   }

   return *this;
}

// Get the number of elements in the list
template <typename T>
size_t List<T>::size() const {
   return _size;
}

// Read-only array subscript operator
template <typename T>
const T& List<T>::operator[](size_t index) const {
   return accessAt(index)->data;
}

// Read/write array subscript operator
template <typename T>
T& List<T>::operator[](size_t index) {
   return accessAt(index)->data;
}

// Insert new element to the start of the list
template <typename T>
void List<T>::insert(const T& o) {
   // If the list is empty
   if (head == nullptr) {
      // Create first node
      append(o);
   }
   else {
      // Insert new node
      head->previous = new Node(o, nullptr, head);
      head = head->previous;
      head->previous = beforeHead;

      // Update sentinel nodes
      beforeHead->data = head->data;
      beforeHead->next = head->next;
      afterTail->previous = tail->previous;
   }

   _size++;
}

// Insert new element to the end of the list
template <typename T>
void List<T>::append(const T& o) {
   // If the list is empty
   if (head == nullptr) {
      // Create first node
      head = new Node(o);
      tail = head;

      // Create sentinel nodes
      beforeHead = new Node(o);
      head->previous = beforeHead;
      afterTail = new Node(o, tail);
   }
   else {
      // Append new node
      tail->next = new Node(o, tail);
      tail = tail->next;
      tail->next = afterTail;

      // Update sentinel nodes
      afterTail->data = tail->data;
      afterTail->previous = tail->previous;
      beforeHead->next = head->next;
   }

   _size++;
}

// Remove the element at the specified index
template <typename T>
void List<T>::removeAt(size_t index) {
   Node* toRemove = accessAt(index);

   // Check previous node
   if (toRemove != head) {
      toRemove->previous->next = toRemove->next;

      // Update beforeHead
      if(index == 1) {
         beforeHead->next = toRemove->next;
      }
   }
   else {
      head = toRemove->next;
      // Update beforeHead
      beforeHead->next = head->next;
      beforeHead->data = head->data;
   }

   // Check next node
   if (toRemove != tail) {
      toRemove->next->previous = toRemove->previous;

      // Update afterTail
      if(index == _size - 1) {
         afterTail->previous = toRemove->previous;
      }
   }
   else {
      tail = toRemove->previous;
      // Update afterTail
      afterTail->previous = tail->previous;
      afterTail->data = tail->data;
   }

   // Deallocate specified node
   delete toRemove;
   _size--;
}

// Remove given element (first occurrence)
template <typename T>
void List<T>::remove(const T& o) {
   int index = find(o);
   if (index != -1) {
      removeAt(index);
   }
   else {
      std::cout << "Object not in the list !" << std::endl;
   }
}

// Find given element in list, returns index (first occurrence)
template <typename T>
int List<T>::find(const T& o) const {
   Node* current = head;
   int index = 0;

   while (current != nullptr) {
      if (current->data == o) {
         return index;
      }
      current = current->next;
      index++;
   }

   return -1;
}

// Return a generic iterator pointing to the beginning of the list
template <typename T>
typename List<T>::Iterator List<T>::begin() {
   return Iterator(beforeHead);
}

// Return a generic iterator pointing to the end of the list
template <typename T>
typename List<T>::Iterator List<T>::end() {
   return Iterator(afterTail);
}

// Return a generic iterator pointing to the beginning of the list
template <typename T>
typename List<T>::ConstIterator List<T>::begin() const {
   return ConstIterator(beforeHead);
}

// Return a generic iterator pointing to the end of the list
template <typename T>
typename List<T>::ConstIterator List<T>::end() const {
   return ConstIterator(afterTail);
}

// Private member functions ---------------------------------------------------------

// Destruction helper
template <typename T>
void List<T>::destroy() {
   if (beforeHead == nullptr) {
      return;
   }

   Node *current = beforeHead;

   beforeHead->next = head;
   afterTail->next = nullptr;

   // Deallocate every element after the root
   while (current != nullptr) {
      Node* tmp = current->next;
      delete current;
      current = tmp;
   }
}

// Helper index access function
template <typename T>
typename List<T>::Node* List<T>::accessAt(size_t index) {
   if (index >= _size) {
      throw std::out_of_range("Index out of range of list size.");
   }

   Node* node = head;
   for (size_t i = 0; i < index; i++) {
      node = node->next;
   }

   return node;
}

#endif // LISTIMPL_HPP
