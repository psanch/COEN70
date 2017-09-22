//
//  structure.cpp
//  
//
//  Created by Pedro Sanchez on 2/1/17.
//
//

#include "sequence.h"
#include <iostream>
#include <stdbool.h>
#include <cassert>
#include <algorithm>

using coen70::sequence;
using std::endl;

sequence::sequence(){
    
    used = 0;
    now = 0;

}


void sequence::insert(const value_type& entry){
    
    assert (size() < CAPACITY);
    
    size_type i;
    
    
    if(is_item()){
        
        for (i = used; i != now; i--){
            
            data[i] = data[i-1];
            
        }
        
    
    
    data[i] = entry;
    used++;
    }
    
    else insert_front(entry);
}

void sequence::insert_front(const value_type& entry){
    
    assert (size() < CAPACITY);
    
    size_type i;
    
    for (i = used; i > 0; i--){
        
        data[i] = data[i-1];
        
    }
    
    data[0] = entry;
    now = 0;
    used++;
    
}

void sequence::attach(const value_type& entry){
    
    assert (size() < CAPACITY);
    
    size_type i;
    
    if(is_item()){
        
        for (i = used; i > now + 1; i--){
            
            data[i] = data[i-1];
        
        }
        
        data[i] = entry;
        now++;
        used++;
    }
    else {attach_back(entry);}
    
}


void sequence::attach_back(const value_type& entry){
    
    assert( used < CAPACITY);
    
    data[used] = entry;
    now = used;
    used++;
    
}
void sequence::remove_current(){
    
    assert(is_item());
    
    size_type i;
    
    for(i = now + 1; i < used; i++){
        
        data[i-1] = data[i];
        
    }

    used--;
}
void sequence::remove_front(){
    
    size_type i;
    
    for(i = 0; i < used; i++){
        
        data[i] = data[i+1];
        
    }
    
}

sequence sequence::operator+(const sequence& s)const{
    
    assert (used + s.used < CAPACITY);
    
    sequence sum;
    
    size_type i;
    
    for (i = 0; i < used; i++){
        
        sum.data[i] = data[i];
        
    }
    
    sum.used = used;
    
    for (i=used; i < used + s.used; i++){
        
        sum.data[i] = s.data[i];
        
    }
    
    sum.used += s.used;
    
    return sum;
    
    
}

bool sequence::is_item()const{

    
    if(now < used)
        return true;
    else return false;
    
}

sequence sequence::operator+=(const sequence& addend){
    
    assert (used + addend.used < CAPACITY);
    
    size_type i;
    
    size_type control;
    
    control = addend.used;
    
    for(i = used; i < used + control; i++){
        
        data[i] = addend.data[i];
        
    }
    
    used += addend.used;
    
    return *this;
    
    
}
sequence::value_type sequence::operator[](size_type now) const{
    
    assert (now < CAPACITY);
    
    return data[now];
    
}
