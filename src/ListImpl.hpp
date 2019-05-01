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

// Friend functions ---------------------------------------------------------------

// Output stream operator
template <typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& list) {
   auto node = list.head;

   while (node != nullptr) {
      os << node->data << " ";
      node = node->next;
   }

   return os;
}

// Iterators inner classes functions ----------------------------------------------

// Generic iterator constructor
template <typename T>
List<T>::GenericIterator::GenericIterator(Node* pointer)
: pointer(pointer) {}

// Prefix incrementation operator
template <typename T>
typename List<T>::GenericIterator::GenericIterator& List<T>::GenericIterator::operator++() {
   pointer = pointer->next;
   return *this;
}

// Postfix incrementation operator
template <typename T>
const typename List<T>::GenericIterator::GenericIterator List<T>::GenericIterator::operator++(int) {
   GenericIterator tmp = *this;
   ++*this;
   return tmp;
}

// Prefix decrementation operator
template <typename T>
typename List<T>::GenericIterator::GenericIterator& List<T>::GenericIterator::operator--() {
   pointer = pointer->previous;
   return *this;
}

// Postfix decrementation operator
template <typename T>
const typename List<T>::GenericIterator::GenericIterator List<T>::GenericIterator::operator--(int) {
   GenericIterator tmp = *this;
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

// Member access operator (read/write)
template <typename T>
T& List<T>::Iterator::operator*() const {
   return this->pointer->data;
}

// Member access operator (read-only)
template <typename T>
const T& List<T>::ConstIterator::operator*() const {
   return this->pointer->data;
}

// Member functions ---------------------------------------------------------------

// No parameter constructor
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), _size(0) {}

// Initializer list constructor
template <typename T>
List<T>::List(const std::initializer_list<T>& args) : _size(args.size()) {
   // Insert first value
   head = new Node(*args.begin());
   tail = head;

   // Read initializer list's values
   for (const T* elem = args.begin()+1; elem != args.end(); ++elem) {
      // Create new element and update previous node's next
      tail->next = new Node(*elem, tail);
      // Update tail
      tail = tail->next;
   }
}

// Copy constructor
template <typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), _size(0) {
   // Call assignment operator
   *this = other;
}

// Destructor
template <typename T>
List<T>::~List() {
   destroy(head);
}

// Assignment operator
template <typename T>
List<T>& List<T>::operator= (const List& other) {
   // No-op if the other list is the current one
   if (&other == this) {
      return *this;
   }

   // Deallocate memory of current list
   destroy(head);

   // Reinitialize
   head = tail = nullptr;
   _size = other.size();

   // Set head and tail
   Node* node = other.head;
   head = new Node(node->data);
   tail = head;
   node = node->next;

   // Set the rest
   while (node != nullptr) {
      tail->next = new Node(node->data, tail);
      tail = tail->next;
      node = node->next;
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
const T& List<T>::operator[](const size_t index) const {
   return accessAt(index)->data;
}

// Read/write array subscript operator
template <typename T>
T& List<T>::operator[](const size_t index) {
   return accessAt(index)->data;
}

// Insert new element to the start of the list
template <typename T>
void List<T>::insert(const T& o) {
   // If the list is empty
   if (head == nullptr) {
      head = new Node(o);
      tail = head;
   }
   else {
      head->previous = new Node(o, nullptr, head);
      head = head->previous;
   }
   _size++;
}

// Insert new element to the end of the list
template <typename T>
void List<T>::append(const T& o) {
   // If the list is empty
   if (head == nullptr) {
      head = new Node(o);
      tail = head;
   }
   else {
      tail->next = new Node(o, tail);
      tail = tail->next;
   }
   _size++;
}

// Remove the element at the specified index
template <typename T>
void List<T>::removeAt(size_t index) {
   Node* toRemove = accessAt(index);

   // Check previous node
   if (toRemove->previous != nullptr) {
      toRemove->previous->next = toRemove->next;
   }
   else {
      head = toRemove->next;
   }
   // Check next node
   if (toRemove->next != nullptr) {
      toRemove->next->previous = toRemove->previous;
   }
   else {
      tail = toRemove->previous;
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
   return Iterator(head);
}

// Return a generic iterator pointing to the end of the list
template <typename T>
typename List<T>::Iterator List<T>::end() {
   return Iterator(tail);
}

// Return a generic iterator pointing to the beginning of the list
template <typename T>
typename List<T>::ConstIterator List<T>::begin() const {
   return ConstIterator(head);
}

// Return a generic iterator pointing to the end of the list
template <typename T>
typename List<T>::ConstIterator List<T>::end() const {
   return ConstIterator(tail);
}

// Private member functions ---------------------------------------------------------------

// Destruction helper
template <typename T>
void List<T>::destroy(Node* root) {
   // Deallocate every element after the root
   while (root != nullptr) {
      Node* tmp = root->next;
      delete root;
      root = tmp;
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
