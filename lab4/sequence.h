//
//  structure.hpp
//  
//
//  Created by Pedro Sanchez on 2/1/17.
//
//
// FILE: sequence1.h
// CLASS PROVIDED: sequence (part of the namespace scu_coen70_3)
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
// typedef ____ value_type
// sequence::value_type is the data type of the items in the
// sequence. It may be any of the C++ built-in types (int, char,
// etc.), or a class with a default constructor, an assignment
// operator, and a copy constructor.
//
// typedef ____ size_type
// sequence::size_type is the data type of any variable that keeps
// track of how many items are in a sequence.
//
// static const size_type CAPACITY = _____
// sequence::CAPACITY is the maximum number of items that a sequence
// can hold.
//
// CONSTRUCTOR for the sequence class:
// sequence( )
// Postcondition: The sequence has been initialized as an empty sequence.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
// void start( )
// Postcondition: The first item on the sequence becomes the current
// item(but if the sequence is empty, then there is no current item).
//
// void advance( )
// Precondition: is_item returns true.
// Postcondition: If the current item was already the last item in the
// sequence, then there is no longer any current item. Otherwise, the
// new current item is the item immediately after the original current
// item.
//
// void insert(const value_type& entry)
// Precondition: size( ) < CAPACITY.
// Postcondition: A new copy of entry has been inserted in the
// sequence before the current item. If there was no current item,
// then the new entry has been inserted at the front of the sequence.
// In either case, the newly inserted item is now the current item of
// the sequence.
//O(N)
//
// void attach(const value_type& entry)
// Precondition: size( ) < CAPACITY.
// Postcondition: A new copy of entry has been inserted in the
// sequence after the current item. If there was no current item, then
// the new entry has been attached to the end of the sequence. In
// either case, the newly inserted item is now the current item of the
// sequence.
//O(N)
//
// void remove_current( )
// Precondition: is_item returns true.
// Postcondition: The current item has been removed from the sequence,
// and the item after this (if there is one) is now the new current item.
//O(n)
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
// size_type size( ) const
// Postcondition: The return value is the number of items in the
// sequence.
//
// bool is_item( ) const
// Postcondition: A true return value indicates that there is a valid
// "current" item that may be retrieved by activating the current
// member function (listed below). A false return value indicates that
// there is no valid current item.
//
// value_type current( ) const
// Precondition: is_item( ) returns true.
// Postcondition: The item returned is the current item in the
// sequence.
//
// VALUE SEMANTICS for the sequence class:
// Assignments and the copy constructor may be used with sequence
// objects.


//insert_front
//postcondition: The item is now inserted as the first item in the sequence and is also the current item
//O(N)

//attach_back
//postcondition: The item is now attached to the end of the list, used++, and is now the current item
//O(1)



//end()
//precondition: at least one item in the sequence
//postcondition: The current item is now the last item in the sequence

//operator +
//pre condition: memory space for new array, size() + addend.size() < CAPACITY
//post condition: a new sequence is created with new.used = used + size.used; all items in the sequences added exist in the new sequence in order.

//operator +=
//precondition: size() + addend.size() < CAPACITY
//postcondition: the object that called the operator has used+= addend.used; all items in the addend are added onto the sequence

//operator []
//postcondition: allows for indexing using size_type; returns value_type of desired index;


#ifndef sequence_hpp
#define sequence_hpp

namespace coen70{
    

    class sequence{
    public:
        typedef double value_type;
        typedef int size_type;
        static const size_type CAPACITY = 50;
        value_type data[CAPACITY];
    private:
        size_type used;
        size_type now;
        
        
    public:
        
        sequence();
        void start(){now = 0;};
        void advance(){assert(is_item()); now++;};
        void end(){assert(used != 0); now = used-1;};
        
        void insert(const value_type& entry);
        void attach(const value_type& entry);
        void insert_front(const value_type& entry);
        void attach_back(const value_type& entry);
        void remove_current();
        void remove_front();
        
        sequence operator+(const sequence& s)const;
        sequence operator+=(const sequence& addend);
        value_type operator[](size_type now) const;
        
        bool is_item()const;
        value_type current() const {assert (is_item()); return data[now];};
        size_type size() const{return used;};
        
        
    
    };

};
#include <stdio.h>

#endif /* structure_hpp */

