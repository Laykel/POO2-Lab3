//
//  LinkedList.cpp
//
//  Copyright (c) 2016 Olivier Cuisenaire. All rights reserved.
//

#include <iostream>
#include <stdexcept>
using namespace std;

/// Forward declaration classe
template < typename T > class LinkedList;

/// Forward declaration fonction d'affichage
template <typename T>
ostream& operator << (ostream& os, const LinkedList<T>& liste);

/// Classe de liste chainee
template < typename T > class LinkedList {

   friend ostream& operator << <T>(ostream& os, const LinkedList<T>& liste);

public:
   using value_type = T;
   using reference = T&;
   using const_reference = const T&;
   using pointer = T*;
   using const_pointer = const T*;

private:
   /**
    *  @brief Maillon de la chaine.
    * 
    * contient une valeur et le lien vers le maillon suivant.
    */
   struct Node {
      value_type data;
      Node* next;
      Node(const_reference data, Node* next = nullptr)
      : data(data), next(next) {
         cout << "(C" << data << ") ";
      }
      Node(Node&) = delete;
      Node(Node&&) = delete;
      ~Node()
      {
         cout << "(D" << data << ") ";
      }
   };

private:
   /**
    *  @brief  Tete de la LinkedList
    */
   Node* head;

private:
   /**
    *  @brief Nombre d'éléments
    */
   size_t nbElements;

public:
   /**
   *  @brief Constructeur par défaut. Construit une LinkedList vide
   *
   *  @remark Complexité constante
   */
   LinkedList() : head(nullptr), nbElements(0) {}

public:
   /**
    *  @brief Constructeur de copie
    *
    *  @param other la LinkedList à copier
    *
    *  @remark Complexité linéaire (comme l'opérateur d'affectation)
    */
   LinkedList(const LinkedList& other) {
      head = nullptr;
      nbElements = 0;

      *this = other;
   }

public:
   /**
    *  @brief Opérateur d'affectation par copie
    *
    *  @param other la LinkedList à copier
    *
    *  @return la LinkedList courante *this (par référence)
    *
    *  @remark l'opérateur doit être une no-op si other 
    *  est la LinkedList courante.
    *
    *  @remark le contenu précédent de la LinkedList courante est 
    *  effacé.
    *
    *  @remark Complexité linéaire
    */
   LinkedList& operator= (const LinkedList& other) {     
      size_t end = nbElements;
      size_t oldNbElements = nbElements;

      try {
         if (other.size() != 0) {
            Node* cur = other.head;
            while (cur != nullptr) {
               insert(cur->data, end);
               end++;
               cur = cur->next;
            }
         }

         while (oldNbElements > 0) {
            pop_front();
            oldNbElements--;
         }
      } catch (...) {
         while (oldNbElements < nbElements) {
            erase(oldNbElements);
         }

         throw; // On relance l'exception
      }

      return *this;
   }

public:
   /**
   *  @brief destructeur
   *
   *  @remark Complexité linéaire
   */
   ~LinkedList() {
      while (head != nullptr) {
         Node* tmp = head->next;
         delete head;
         head = tmp;
      }

      nbElements = 0;
   }

public:
   /**
    *  @brief nombre d'éléments stockés dans la liste
    *
    *  @return nombre d'éléments. 
    *
    *  @remark Complexité constante
    */
   size_t size() const noexcept {
      return nbElements;
   }

public:
   /**
    *  @brief insertion d'une valeur dans un maillon en tête de liste
    *
    *  @param value la valeur à insérer
    *
    *  @exception std::bad_alloc si pas assez de mémoire, où toute autre exception
    *  lancée par le constructeur de copie de value_type
    *
    *  @remark Complexité constante
    */
   void push_front(const_reference value) {
      head = new Node{value, head};
      nbElements++;
   }

public:
   /**
    *  @brief accès (lecture/écriture) à la valeur en tête de LinkedList
    *
    *  @return référence à cette valeur
    *
    *  @exception std::runtime_error si la liste est vide
    *
    *  @remark Complexité constante
    */
   reference front() {
      if (head == nullptr)
         throw runtime_error("runtime_error LinkedList::front");

      return head->data;
   }

   const_reference front() const {
      return front();
   }

public:
   /**
    *  @brief Suppression de l'élément en tête de LinkedList
    *
    *  @exception std::runtime_error si la liste est vide
    *
    *  @remark Complexité constante
    */
   void pop_front() {
      if(head == nullptr)
         throw runtime_error("runtime_error LinkedList::pop_front");

      Node* tmp = head;
      head = head->next;
      delete tmp;

      nbElements--;
   }

public:
   /**
    *  @brief Insertion en position quelconque
    *
    *  @param value la valeur à insérer
    *  @param pos   la position où insérer, 0 est la position en tete
    *
    *  @exception std::out_of_range("LinkedList::insert") si pos non valide
    *
    *  @exception std::bad_alloc si pas assez de mémoire, où toute autre exception
    *  lancée par la constructeur de copie de value_type
    *
    *  @remark Complexité linéaire
    */
   void insert(const_reference value, size_t pos) {
      if (pos > nbElements)
         throw out_of_range("LinkedList::insert");

      if (pos == 0) {
         push_front(value);
      } else {
         Node* prevNode = nullptr;
         getPointerFromPosition(pos-1, prevNode);
         Node* newNode = new Node{value, prevNode->next};

         prevNode->next = newNode;

         nbElements++;
      }
   }

public:
   /**
    *  @brief Acces à l'element en position quelconque
    *
    *  @param pos la position, 0 est la position en tete
    * 
    *  @exception std::out_of_range("LinkedList::at") si pos non valide
    *
    *  @return une reference a l'element correspondant dans la liste
    *
    *  @remark Complexité linéaire
    */
   reference at(size_t pos) {
      if (pos >= nbElements)
         throw out_of_range("LinkedList::at");

      Node* cur = nullptr;
      getPointerFromPosition(pos, cur);
      return cur->data;
   }

   /**
    *  @brief Acces à l'element en position quelconque
    *
    *  @param pos la position, 0 est la position en tete
    *
    *  @exception std::out_of_range("LinkedList::at") si pos non valide
    *
    *  @return une const_reference a l'element correspondant dans la liste
    *
    *  @remark Complexité linéaire
    */
   const_reference at(size_t pos) const {
      if (pos >= nbElements)
         throw out_of_range("LinkedList::at");
      
      Node* cur = nullptr;
      getPointerFromPosition(pos, cur);
      return cur->data;
   }

public:
   /**
    *  @brief Suppression en position quelconque
    *
    *  @param pos la position, 0 est la position en tete
    *
    *  @exception std::out_of_range("LinkedList::erase") si pos non valide
    *
    *  @remark Complexité linéaire
    */
   void erase(size_t pos) {
      if (pos >= nbElements)
         throw out_of_range("LinkedList::erase");

      if (pos == 0) {
         pop_front();
      }
      else {
         Node* prevNode = nullptr;
         getPointerFromPosition(pos-1, prevNode);
         Node* tmp = prevNode->next;

         prevNode->next = tmp->next;

         delete tmp;
         nbElements--;
      }
   }

public:
   /**
    *  @brief Recherche du premier élément correspondant à une valeur
    *  donnée dans la liste
    *
    *  @param value la valeur à chercher
    *
    *  @return la position dans la liste. -1 si la valeur n'est pas trouvée
    *
    *  @remark Complexité linéaire
    */
   size_t find(const_reference value) const noexcept {
      const size_t NOT_FOUND = (size_t)-1;

      Node* cur = head;
      for (size_t i = 0; i < nbElements; ++i) {
         if (cur->data == value)
            return i;
         cur = cur->next;
      }

      return NOT_FOUND;
   }

   /**
    *  @brief Tri des elements de la liste par tri fusion
    *
    *  @remark Complexité linéarithmique - O(n log(n))
    */
   void sort() noexcept {
      mergeSort(head, nbElements);
   }

private:
   Node*& merge(Node*& start, Node* mid, Node* end) {
      Node* iteratorL = start;
      Node* iteratorR = mid;
      Node** cur = &start;

      while (iteratorL != mid and iteratorR != end) {
         if (iteratorL->data < iteratorR->data) {
            *cur = iteratorL;
            cur = &(iteratorL->next);
            iteratorL = iteratorL->next;
         } else {
            *cur = iteratorR;
            cur = &(iteratorR->next);
            iteratorR = iteratorR->next;
         }
      }

      Node* startRest = iteratorL == mid ? iteratorR : iteratorL;
      Node* endLoop = iteratorL == mid ? end : mid;
      
      while(startRest != endLoop){
         *cur = startRest;
         cur = &(startRest->next);
         startRest = startRest->next;
      }
      *cur = end;
      return *cur;
   }

   Node*& mergeSort(Node*& start, size_t n) {
      if (n <= 1)
         return start->next;
      
      Node*& middle = mergeSort(start, n/2);
      Node*& last = mergeSort(middle, n - n/2);
      
      return merge(start, middle, last);
   }

   /**
    *  @brief Modifie le pointeur "elem" pour pointer sur l'élément
    *  en position "pos".
    *
    *  @param [in] pos la position dans la liste de l'élément voulu
    *  @param [in,out] elem un pointeur qui sera modifié
    */
   void getPointerFromPosition(size_t pos, Node*& elem) const {
      // On initialise le pointeur en local pour s'assurer qu'il est valide
      elem = head;
      for (size_t i = 0; i < pos; ++i) {
         elem = elem->next;
      }
   }
};

template <typename T>
ostream& operator << (ostream& os, const LinkedList<T>& liste) {
   os << liste.size() << ": ";
   auto n = liste.head;
   while (n) {
      os << n->data << " ";
      n = n->next;
   }
   return os;
}
