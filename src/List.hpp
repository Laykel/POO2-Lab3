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
    * <p>Creates null head and tail</p>
    */
   explicit List();

   /**
    * Initializer list constructor
    *
    * @param args The initializer list
    */
   List(const std::initializer_list<T>& args);

   /**
    * Copy constructor
    *
    * @param other The list to copy from
    */
   List(const List& other);

   /**
    * Destructor
    */
   virtual ~List();

   /**
    * Assignment operator
    *
    * @param other The list from which to copy
    * @return A reference to a new list with identical elements to other
    */
   List& operator=(const List& other);

   /**
    * Get the number of elements in the list
    *
    * @return The size of the list
    */
   size_t size() const;

   /**
    * Read-only array subscript operator
    *
    * @param index The index of the element to access
    * @return A reference to the (constant) value of the element at index
    */
   const T& operator[](const size_t index) const;

   /**
    * Read/write array subscript operator
    *
    * @param index The index of the element to access
    * @return A reference to the value of the element at index
    */
   T& operator[](const size_t index);

   /**
    * Insert an object at the beginning of the list
    *
    * @param o A constant reference to the object to insert
    */
   void insert(const T& o);

   /**
    * Insert an object at the end of the list
    *
    * @param o A constant reference to the object to append
    */
   void append(const T& o);

   /**
    * Remove the element at specified index
    *
    * @param index Index of the element to remove
    */
   void removeAt(size_t index);

   /**
    * Remove the object o if it is in the list
    *
    * @param o The object to remove
    */
   void remove(const T& o);

   /**
    * Find an object if it is in the list
    *
    * @param o The object to find
    * @return The index of the object or -1 if it is not in the list
    */
   int find(const T& o) const;

//    Iterator begin();

//    Iterator end();

private:
   /**
    * Helper for the destruction of list or sub-lists
    */
   void destroy(Node* root);

   /**
    * Helper index access member function
    *
    * @param index The index of the node to access
    */
    Node* accessAt(size_t index);

private:
   // Head node of the list
   Node* head;
   // Tail node of the list
   Node* tail;

   // Size of the list
   size_t _size;
};

// Genericity nonsense
#include "ListImpl.hpp"

#endif // LIST_HPP
