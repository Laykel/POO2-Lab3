#ifndef ARRAYIMPL_HPP
#define ARRAYIMPL_HPP

// Dummy include for IDE
#include "Array.hpp"

/**
 * Operator <<
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const Array<T>& a) {
   for (size_t i = 0; i < a._size; i++) {
      os << a[i] << " ";
   }

   return os;
}

template <typename T>
Array<T>::Array(const size_t size)
   : _data(new T[size]), _size(size) {}

template <typename T>
Array<T>::Array(std::initializer_list<T> args)
   : _data(new T[args.size()]), _size(args.size()) {
   int i = 0;
   // Read initializer list's values
   for (const T* val = args.begin(); val != args.end(); ++val) {
      _data[i++] = *val;
   }
}

template <typename T>
Array<T>::Array(const Array& a)
   : _data(new T[a.size()]), _size(a._size) {
   memcpy(_data, a._data, a._size * sizeof(T));
}

template <typename T>
Array<T>::~Array() {
   delete[] _data;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& a) {
   if (&a == this) {
      return *this;
   }

   delete[] _data;

   _data = new T[a._size];
   _size = a._size;

   memcpy(_data, a._data, a._size * sizeof(T));

   return *this;
}

template <typename T>
T& Array<T>::operator[](const size_t index) const {
   return _data[index];
}

template <typename T>
size_t Array<T>::size() const {
   return _size;
}

// Iterators
template <typename T>
typename Array<T>::Iterator Array<T>::begin() {
   return Iterator(_data);
}

template <typename T>
typename Array<T>::Iterator Array<T>::end() {
   return Iterator(_data + _size);
}

#endif
