/* ---------------------------------------------------------------------------------
 * Lab         : Laboratoire 3 - Liste
 * File        : List.cpp
 * Author(s)   : Alison Savary et Luc Wachter
 * Date        : 11.04.2019
 *
 * Goal        :
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

};

// Genericity nonsense
#include "ListImpl.hpp"

#endif // LIST_HPP
