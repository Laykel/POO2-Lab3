/* ---------------------------------------------------------------------------------
 * Lab       : Laboratoire 3 - Liste
 * File      : main.cpp
 * Author(s) : Alison Savary et Luc Wachter
 * Date      : 11.04.2019
 *
 * Goal      : Test the List class
 *
 * Compiler  : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */

#include <iostream>
#include "List.hpp"
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

using namespace std;

// Test program for List class (almost unit tests)
int main() {
   // TODO: Test operator->

   cout << "Test simple constructor (expected: )" << endl;
   List<int> l1;
   cout << l1 << endl;
   cout << string(30, '-') << endl;

   cout << "Test initializer list constructor (expected: 12 13 56 90 0)" << endl;
   List<int> l2{12, 13, 56, 90, 0};
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test copy constructor (expected: 12 13 56 90 0)" << endl;
   const List<int> l3(l2);
   cout << l3 << endl;
   cout << string(30, '-') << endl;

   cout << "Test dynamically allocated list of strings (expected: Rohan Gondor)" << endl;
   List<string>* l4 = new List<string>{"Rohan", "Gondor"};
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test assignment operator (expected: 12 13 56 90 0)" << endl;
   l1 = l3;
   cout << l1 << endl;
   cout << string(30, '-') << endl;

   cout << "Test append method l2.append(42) (expected: 12 13 56 90 0 42)" << endl;
   l2.append(42);
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test insert method l2.insert(23) (expected: 23 12 13 56 90 0 42)" << endl;
   l2.insert(23);
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test insert l1.insert(\"Hello\") (expected: Hello Rohan Gondor)" << endl;
   l4->insert("Hello");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test append l4.append(\"Ca boom ?\") (expected: Hello Rohan Gondor Ca boom?)" << endl;
   l4->append("Ca boom ?");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test removeAt l4.removeAt(1) (expected: Hello Gondor Ca boom?)" << endl;
   l4->removeAt(1);
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test removeAt l2.removeAt(3) (expected: 23 12 13 90 0 42)" << endl;
   l2.removeAt(3);
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test find l2.find(90) (expected: Index of 90 is 3)" << endl;
   cout << "Index of 90 is " << l2.find(90) << endl;
   cout << string(30, '-') << endl;

   cout << "Test remove(object) l4.remove(\"Hello\") (expected: Gondor Ca boom?)" << endl;
   l4->remove("Hello");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test remove(object) l4.remove(\"NotHere\") (expected: Object not in the list!)" << endl;
   l4->remove("NotHere");
   cout << string(30, '-') << endl;

   cout << "Test write with brackets operator (expected: 23 12 9 90 0 42)" << endl;
   l2[2] = 9;
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   List<string> l5{"what", "a", "beautiful", "world"};

   cout << "Test for each with iterators (expected: what a beautiful world)" << endl;
   for (string s : l5) {
      cout << s << " ";
   }
   cout << endl << string(30, '-') << endl;

   cout << "Test for each with const iterators (expected: 12 13 56 90 0)" << endl;
   for (int i : l3) {
      cout << i << " ";
   }
   cout << endl << string(30, '-') << endl;

   // Deallocate l4
   delete l4;

   // Given tests in the assignment
   cout << "Tests given in the assignment" << endl;
   List<string> l;
   l.append("un");
   l.append("deux");
   l.append("trois");

   for (List<string>::Iterator it = l.begin(); it != l.end(); ++it)
      cout << *it << " ";
   cout << endl;
   // Affichage: un deux trois

   const List<int> c = {42, 3, 14};
   for (List<int>::ConstIterator it = c.end(); it != c.begin(); --it)
      cout << *it << " ";
   cout << endl;
   // Affichage: 14 3 42
   
   // Test liaison dynamique
   Dog d1;
   Cat c1;
   Cat c2;
   Animal a1;
   List<Animal> la {d1, c1, c2, a1};
   
   for (List<Animal>::Iterator it = la.begin(); it != la.end(); ++it)
      (*it).makeSound();
   cout << endl;

   return EXIT_SUCCESS;
}