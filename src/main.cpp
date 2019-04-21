/* ---------------------------------------------------------------------------------
 * Lab         : Laboratoire 3 - Liste
 * File        : main.cpp
 * Author(s)   : Alison Savary et Luc Wachter
 * Date        : 11.04.2019
 *
 * Goal        : Test the List class
 *
 * Compilateur : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */

#include <iostream>
#include "List.hpp"

using namespace std;

// Test program for List class (almost unit tests)
int main() {
    cout << "Test simple constructor" << endl;
    List<int> l1;
    cout << l1 << endl;
    cout << string(30, '-') << endl;

    cout << "Test initializer list constructor" << endl;
    List<int> l2{12, 13, 56, 90, 0};
    cout << l2 << endl;
    cout << string(30, '-') << endl;

    cout << "Test copy constructor" << endl;
    List<int> l3(l2);
    cout << l3 << endl;
    cout << string(30, '-') << endl;

//    cout << "Test write with brackets operator" << endl;
//    l3[2] = 9;
//    cout << l3 << endl;
//    cout << string(30, '-') << endl;
//
//    cout << "Test assigment operator" << endl;
//    l1 = l3;
//    cout << l1 << endl;
//    cout << string(30, '-') << endl;
//
//    cout << "Test iterators on list of strings" << endl;
//    List<string> l5{"what", "a", "beautiful", "world"};
//    // Test iterators
//    for (auto it = l5.begin(); it != l5.end(); ++it) {
//        cout << &*it << " - " << *it << endl;
//    }
//    cout << string(30, '-') << endl;
//
//    cout << "Test for each with iterators" << endl;
//    for (string s : l5) {
//        cout << s << ", ";
//    }
//    cout << endl;
//
//    // Given tests in the assignment
//    {
//        List<string> l;
//        l.append("un");
//        l.append("deux");
//        l.append("trois");
//        for (List<string>::Iterator it = l.begin(); it != l.end(); ++it)
//            cout << *it << " ";
//        cout << endl;
//        // Affichage: un deux trois
//        const List<int> c = {42, 3, 14};
//        for (List<int>::ConstIterator it = c.end(); it != c.begin(); --it)
//            cout << *it << " ";
//        cout << endl;
//        // Affichage: 14 3 42
//    }

    return EXIT_SUCCESS;
}