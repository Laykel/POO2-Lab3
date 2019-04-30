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

using namespace std;

// Test program for List class (almost unit tests)
int main() {
   cout << "Test simple constructor (l1)" << endl;
   List<int> l1;
   cout << l1 << endl;
   cout << string(30, '-') << endl;

   cout << "Test initializer list constructor (l2)" << endl;
   List<int> l2{12, 13, 56, 90, 0};
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test copy constructor (l3(l2))" << endl;
   const List<int> l3(l2);
   cout << l3 << endl;
   cout << string(30, '-') << endl;

   cout << "Test list of strings" << endl;
   List<string>* l4 = new List<string>{"Rohan", "Gondor"};
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test assignment operator (l1 = l3)" << endl;
   l1 = l3;
   cout << l1 << endl;
   cout << string(30, '-') << endl;

   cout << "Test append method l2.append(42)" << endl;
   l2.append(42);
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test insert method l2.insert(23)" << endl;
   l2.insert(23);
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test insert on empty list l1.insert(\"Hello\")" << endl;
   l4->insert("Hello");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test append on empty list l4.append(\"Ca boom ?\")" << endl;
   l4->append("Ca boom ?");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test removeAt on list with one element l4.removeAt(1)" << endl;
   l4->removeAt(1);
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test removeAt l2.removeAt(3)" << endl;
   l2.removeAt(3);
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test find l2.find(90)" << endl;
   cout << "Index of 90 is " << l2.find(90) << endl;
   cout << string(30, '-') << endl;

   cout << "Test remove(object) l4.remove(\"Hello\")" << endl;
   l4->remove("Hello");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test remove(object) l4.remove(\"NotHere\")" << endl;
   l4->remove("NotHere");
   cout << *l4 << endl;
   cout << string(30, '-') << endl;

   cout << "Test write with brackets operator" << endl;
   l2[2] = 9;
   cout << l2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test iterators on list of strings" << endl;
   List<string> l5{"what", "a", "beautiful", "world"};
   // Test iterators
   for (auto it = l5.begin(); it != l5.end(); ++it) {
      cout << &*it << " - " << *it << endl;
   }
   cout << string(30, '-') << endl;

   cout << "Test for each with iterators" << endl;
   for (string s : l5) {
      cout << s << " ";
   }
   cout << endl << string(30, '-') << endl;

   cout << "Test for each with const iterators" << endl;
   for (int i : l3) {
      cout << i << " ";
   }
   cout << endl << string(30, '-') << endl;

   // Deallocate l4
   delete l4;

   // Given tests in the assignment
   {
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
   }

   return EXIT_SUCCESS;
}