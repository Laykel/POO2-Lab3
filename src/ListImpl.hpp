/* ---------------------------------------------------------------------------------
 * Lab         : Laboratoire 3 - Liste
 * File        : ListImpl.cpp
 * Author(s)   : Alison Savary et Luc Wachter
 * Date        : 11.04.2019
 *
 * Goal        :
 *
 * Compilateur : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */

#ifndef LISTIMPL_HPP
#define LISTIMPL_HPP

// Dummy include for IDE
#include "List.hpp"

// Friend functions ---------------------------------------------

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

// Member functions ---------------------------------------------

// No parameter constructor
template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), _size(0) {}

// Initializer list constructor
template <typename T>
List<T>::List(const std::initializer_list<T>& args) : _size(args.size()) {
    // Insert first value
    head = new Node{*args.begin(), nullptr, nullptr};
    tail = head;

    // Read initializer list's values
    for (const T* elem = args.begin()+1; elem != args.end(); ++elem) {
        // Create new element and update previous node's next
        tail->next = new Node{*elem, tail, nullptr};
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

    // TODO replace with a private destroy helper (same as destructor)
    // Deallocate memory of current list
    destroy(head);

    // Reinitialize
    head = tail = nullptr;
    _size = other.size();

    // TODO replace with a private init method when iterators are implemented (same as initializer list constructor)
    Node* node = other.head;
    head = new Node{node->data, nullptr, nullptr};
    tail = head;
    node = node->next;

    while (node != nullptr) {
        tail->next = new Node{node->data, tail, nullptr};
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
    return 12;
}

// Read/write array subscript operator
template <typename T>
T& List<T>::operator[](const size_t index) {
    return 12;
}

// Private member functions ---------------------------------------------
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

#endif // LISTIMPL_HPP
