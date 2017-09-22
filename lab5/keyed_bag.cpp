//
//  keyed_bag.cpp
//  
//
//  Created by pedro emilio sanchez munoz on 2/10/17.
//
//
/*
namespace coen70_lab
 {
 class keyed_bag
 {
 public:
 
 // TYPEDEFS and MEMBER CONSTANTS
 typedef int value_type;
 typedef string key_type;
 typedef std::size_t size_type;
 static const size_type CAPACITY = 30;
 
 // CONSTRUCTOR
 keyed_bag( ) { used = 0; }
 
 // MODIFICATION MEMBER FUNCTIONS
 void erase( ) { used = 0; }
 bool erase(const key_type& key);
 void insert(const value_type& entry, const key_type& key);
 keyed_bag operator +=(const keyed_bag& addend);
 
 // CONSTANT MEMBER FUNCTIONS
 bool has_key(const key_type& key) const;
 value_type get(const key_type& key) const;
 bool hasDuplicateKey(const keyed_bag& otherBag) const;
 size_type size( ) const { return used; }
 size_type count(const value_type& target) const;
 
 private:
 key_type keys[CAPACITY];    // The array to store the keys
 value_type data[CAPACITY];  // The array to store items
 size_type used;             // How much of array is used
 
 };
 
 // NONMEMBER FUNCTIONS for the keyed_bag class
 keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2);
 }
*/

#include <stdio.h>
#include <string>
#include "keyed_bag.h"
#include <cassert>

using namespace coen70_lab;

bool keyed_bag::erase(const key_type& key){
    
    size_type i;
    
    for (i = 0; i < used; i++){
        
        if(keys[i] == key){
            data[i] = data[used]; //swap for deletion
            keys[i] = keys[used];
            used--;
            return true;
            }
            
        }
        return false;
}
    


void keyed_bag::insert(const value_type& entry, const key_type& key){
    
    assert( used < CAPACITY );
    
    data[used] = entry;
    keys[used] = key;
    used++;
}

keyed_bag keyed_bag::operator+=(const keyed_bag& addend){
    
    assert (used + addend.used < CAPACITY);
    
    size_type i;
    size_type j;
    size_type control = addend.used;
    
    for(i = used, j = 0; i < used + control; i++,j++){
        
        data[i] = addend.data[j];
        keys[i] = addend.keys[j];
    
    }
    
    used += control;
    
    return *this;
    
}

keyed_bag operator+(const keyed_bag& lhs, const keyed_bag& rhs){
    
    assert(lhs.size() + rhs.size() < keyed_bag::CAPACITY);
    assert(!lhs.hasDuplicateKey(rhs));
    
    keyed_bag newbag;
    
    newbag += lhs;
    newbag += rhs;
    
    return newbag;
    
}

bool keyed_bag::has_key(const key_type& key)const{
    
    size_type i;
    
    for (i=0; i < used; i++){
        
        if(keys[i] == key)
            return true;
    }
    
    return false;
    
}

bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{ //O N^2 !!!! no gusta
    
    size_type i,j;
    size_type dup = 0;
    
    for(i=0; i < used; i++){
       
        for(j=0; j < otherBag.used; j++){
            
            if (keys[i] == otherBag.keys[j]){
                dup++;
                if (dup > 1)
                    return true;
            }
        }
        
    }
    return false;
}

keyed_bag::value_type keyed_bag::get(const key_type& key)const{
    
    assert(has_key(key));
    size_type i;
    
    for(i=0; i < used; i++){
        
        if(keys[i] == key)
            return data[i];
        
    }
}

keyed_bag::size_type keyed_bag::count(const value_type& target)const{
    
    size_type i;
    size_type count = 0;
    
    for(i=0; i < used; i++){
        
        if(data[i] == target)
            count++;
    }
    
    return count;
    
}
