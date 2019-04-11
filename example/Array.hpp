#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstring>
#include <ostream>

// Predeclaration of generic class
template <typename T> class Array;

// Predeclaration of friend function
template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& a);

/**
 * Generic Array class with iterators
 * @author Luc Wachter
 */
template <typename T>
class Array {
   /**
    * Operator <<
    */
   friend std::ostream& operator<< <>(std::ostream& os, const Array& a);

   /**
    * Iterator class on Array
    */
   class Iterator {
   public:
      Iterator(T* pointer)
         : pointer(pointer) {}

      // Prefix ++
      Iterator& operator++() {
         pointer++;
         return *this;
      }

      bool operator==(const Iterator& val) const {
         return (pointer == val.pointer);
      }

      bool operator!=(const Iterator& val) const {
         return !(val == *this);
      }

      T& operator*() {
         return *pointer;
      }

      // Other ++, -> ...
   private:
      T* pointer;
   };

public:
   explicit Array(const size_t size);

   Array(std::initializer_list<T> args);

   Array(const Array& a);

   ~Array();

   Array& operator=(const Array& a);

   T& operator[](const size_t index) const;

   size_t size() const;

   Iterator begin();

   Iterator end();

private:
   // Content of the array
   T* _data;
   // Size of the array
   size_t _size;
};

// Genericity nonsense
#include "ArrayImpl.hpp"

#endif
