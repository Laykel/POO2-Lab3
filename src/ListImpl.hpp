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
    while (head != nullptr) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
}

// Assignment operator
template <typename T>
List<T>& List<T>::operator= (const List& other) {
    if (&other == this) {
        return *this;
    }

    if (other.size() == 0) {
        head = tail = nullptr;
        _size = 0;
    }
    else {
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
    }
}

// Get the number of elements in the list
template <typename T>
size_t List<T>::size() const {
    return _size;
}

// Private member functions ---------------------------------------------

#endif // LISTIMPL_HPP
