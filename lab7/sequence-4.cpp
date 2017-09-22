//
//  sequence.cpp
//  
//
//  Created by Pedro Sanchez on 3/1/17.
//
//
/*private:
 node *head_ptr;
 node *tail_ptr;
 node *cursor;
 node *precursor;
 size_type many_nodes;*/

#include <stdio.h>
#include <cassert>
#include "sequence.h"
#include "node.h"
#include <iostream>

namespace coen70_lab7{
    

    sequence::sequence( ){
        
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
        
    }
    
    sequence::sequence(const sequence& source){
        
        node* head_ptr = NULL;
        node* tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        
        list_copy(source.head_ptr,head_ptr,tail_ptr);
        
        many_nodes = size();
        
    }
    
    sequence::~sequence( ){
        
        list_clear(head_ptr);
        
    }
    
    void sequence::start( ){
        
        cursor = head_ptr;
        precursor = NULL;
        
    }
    
    void sequence::end(){
        checktail();
        cursor = tail_ptr;
        
        for(precursor = head_ptr; precursor->link() != cursor; precursor = precursor->link());
        checktail();
    }
    
    void sequence::checktail(){
        
        if(tail_ptr != NULL && tail_ptr->link() == NULL) return;
        
        if(tail_ptr == NULL){
            tail_ptr = head_ptr;
        }
        while(tail_ptr->link() != NULL){
            tail_ptr = tail_ptr->link();
            
        }
        
    }
    
    void sequence::advance( ){
        
        assert(is_item() == true);
        
        precursor = cursor;
        cursor = cursor->link();
        
    }
    
    void sequence::insert(const value_type& entry){
        
        if(cursor == head_ptr){
            
            list_head_insert(head_ptr,entry);
            cursor = head_ptr;
            many_nodes++;
            checktail();
            return;
        }
        
        if(precursor == tail_ptr){
            
            cursor = new node(entry,NULL);
            precursor->set_link(cursor);
            checktail();
            many_nodes++;
            return;
            
        }
        
        if(is_item()){
            
            cursor = new node(entry, precursor->link());
            precursor->set_link(cursor);
            many_nodes++;
            checktail();
            return;
            
        }
        
        else{
            list_head_insert(head_ptr,entry);
            cursor = head_ptr;
            checktail();
            many_nodes++;
            return;
        }
    }
    void sequence::attach(const value_type& entry){
        
        if(!is_item() || many_nodes == 0){
            
            list_head_insert(head_ptr,entry);
            cursor = head_ptr;
            tail_ptr = head_ptr;
            many_nodes++;
            checktail();
            return;
            
        }
        
        if(cursor == tail_ptr){
            
            precursor = cursor;
            cursor = new node(entry,NULL);
            precursor->set_link(cursor);
            checktail();
            many_nodes++;
            return;
            
        }
        
        if( is_item() ){
            
            precursor = cursor;
            cursor = new node(entry, precursor->link());
            precursor->set_link(cursor);
            checktail();
            many_nodes++;
            return;
            
        }
        
        else{
            list_head_insert(head_ptr,entry);
            cursor = head_ptr;
            checktail();
            many_nodes++;
            return;
        }
        
        return;
    
    }
    void sequence::operator =(const sequence& source){
     
        list_copy(source.head_ptr,head_ptr,tail_ptr);
        cursor = head_ptr;
        precursor = NULL;
        many_nodes = size();
        return;
        
    }
    void sequence::remove_current( ){
        
        assert(is_item());
        
        if(cursor == head_ptr){
            
            if(tail_ptr == head_ptr){
                
                tail_ptr = NULL;
                
            }
            
            head_ptr = head_ptr->link();
            delete [] cursor;
            cursor = head_ptr;
            many_nodes--;
            checktail();
            return;
        }
        
        if(cursor == tail_ptr){
            
            tail_ptr = precursor;
            delete [] cursor;
            cursor = NULL;
            tail_ptr->set_link(NULL);
            many_nodes--;
            checktail();
            return;
            
        }
        
        if(is_item()){
            
            precursor->set_link(cursor->link());
            delete [] cursor;
            cursor = precursor->link();
            many_nodes--;
            checktail();
            return;
            
        }
        
        
        return;
        
    }
    
    //constant 
    sequence::size_type sequence::size( ) const {
        
        return many_nodes;
    
    }
    
    bool sequence::is_item( ) const {
        
        if (cursor != NULL) return true;
        return false;
    }
    
    sequence::value_type sequence::current( ) const{
        
        assert(is_item());
        return cursor->data();
        
    }


    
}
