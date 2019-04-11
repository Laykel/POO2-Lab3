#include <cstdlib>
#include <iostream>
#include "Array.hpp"

using namespace std;

/**
 * Test program for Array class
 * @author Luc Wachter
 */
int main() {
   cout << "Test simple constructor" << endl;
   Array<int> a1(12);
   cout << a1 << endl;
   cout << string(30, '-') << endl;

   cout << "Test initializer list constructor" << endl;
   Array<int> a2{12, 13, 56, 90, 0};
   cout << a2 << endl;
   cout << string(30, '-') << endl;

   cout << "Test copy constructor" << endl;
   Array<int> a3(a2);
   cout << a3 << endl;
   cout << string(30, '-') << endl;

   cout << "Test write with brackets operator" << endl;
   a3[2] = 9;
   cout << a3 << endl;
   cout << string(30, '-') << endl;

   cout << "Test assigment operator" << endl;
   a1 = a3;
   cout << a1 << endl;
   cout << string(30, '-') << endl;

   cout << "Test iterators on array of strings" << endl;
   Array<string> a5{"what", "a", "beautiful", "world"};
   // Test iterators
   for (auto it = a5.begin(); it != a5.end(); ++it) {
      cout << &*it << " - " << *it << endl;
   }
   cout << string(30, '-') << endl;

   cout << "Test for each with iterators" << endl;
   for (string s : a5) {
      cout << s << ", ";
   }

   cout << endl;

   return EXIT_SUCCESS;
}
