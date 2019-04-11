/* ---------------------------------------------------------------------------------
 * Lab         : Laboratoire 3 - Liste
 * File        : List.cpp
 * Author(s)   : Alison Savary et Luc Wachter
 * Date        : 11.04.2019
 *
 * Goal        : Implement a generic doubly linked list
 *
 * Compilateur : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */

#ifndef LIST_HPP
#define LIST_HPP

#include <ostream>

// Predeclaration of generic class
template <typename T> class List;

// Predeclaration of friend functions
template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& a);

/**
 * Generic List class with iterators
 *
 * @author Alison Savary, Luc Wachter
 */
template <typename T>
class List {
    // Operator <<
    friend std::ostream& operator<< <>(std::ostream& os, const List& a);

    /**
     * Node composing the list
     */
    struct Node {
        T data;

        Node* previous;
        Node* next;
    };

public:
    /**
     * Empty constructor
     * <p>
     * Creates a null root
     */
    explicit List();

     /**
      * Initializer list constructor
      *
      * @param args The initializer list
      */
    List(std::initializer_list<T> args);

    /**
     * Copy constructor
     *
     * @param list The list to copy from
     */
    List(const List& list);

    /**
     * Destructor
     */
    virtual ~List();

    List& operator=(const List& a);

    T& operator[](const size_t index) const;

    size_t size() const;

//    Iterator begin();

//    Iterator end();

private:
    // Root node of the list
    Node* root;

    // Size of the list
    size_t _size;
};

// Genericity nonsense
#include "ListImpl.hpp"

#endif // LIST_HPP
