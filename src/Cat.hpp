/* ---------------------------------------------------------------------------------
 * Lab       : Laboratoire 3 - Liste
 * File      : Cat.hpp
 * Author(s) : Alison Savary et Luc Wachter
 * Date      : 01.05.2019
 *
 * Goal      : Very very small class to represent a cat
 *
 * Compiler  : g++ version 8.2.0
 * ---------------------------------------------------------------------------------
 */
#ifndef CAT_HPP
#define CAT_HPP

class Cat : public Animal
{
   public:
   void makeSound()
   {
      std::cout << "I am a cat Miaou !" << std::endl;
   }
};

#endif /* CAT_HPP */

