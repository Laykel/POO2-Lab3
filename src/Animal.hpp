/* ---------------------------------------------------------------------------------
 * Lab       : Laboratoire 3 - Liste
 * File      : Animal.hpp
 * Author(s) : Alison Savary et Luc Wachter
 * Date      : 01.05.2019
 *
 * Goal      : Very very small class to represent an animal
 *
 * Compiler  : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */
#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal
{
   public:
   virtual void makeSound()
   {
      std::cout << "I am an animal and make a sound." << std::endl;
   }
};

#endif /* ANIMAL_HPP */

