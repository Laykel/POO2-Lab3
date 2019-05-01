/* ---------------------------------------------------------------------------------
 * Lab       : Laboratoire 3 - Liste
 * File      : Dog.hpp
 * Author(s) : Alison Savary et Luc Wachter
 * Date      : 01.05.2019
 *
 * Goal      : Very very small class to represent a dog
 *
 * Compiler  : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */
#ifndef DOG_HPP
#define DOG_HPP

class Dog : public Animal
{
   public:
   void makeSound()
   {
      std::cout << "I am a dog woof, woof !" << std::endl;
   }
};

#endif /* DOG_HPP */

