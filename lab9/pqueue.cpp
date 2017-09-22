//
//  pqueue.cpp
//  
//
//  Created by Pedro Sanchez on 3/13/17.
//
//node *head_ptr;
//size_t many_nodes;
//

#include <cassert>
#include <cstdlib>
#include "pqueue.h"
namespace coen70_lab9 {
	
PriorityQueue::PriorityQueue( ){
    
	head_ptr = NULL;
	many_nodes = 0;
	
    
}

PriorityQueue::PriorityQueue(const PriorityQueue& other){
    
	head_ptr = NULL;
	many_nodes = 0;
	
	*this = other;
	
}


PriorityQueue::~PriorityQueue(){
    
    node* p;
    
    while (head_ptr != NULL){
        p = head_ptr;
        head_ptr = head_ptr->link() ;
        delete [] p;
        --many_nodes;
    }
    
}

void PriorityQueue::insert(const Item& entry, unsigned int priority){
    
    node* p;
    
    p = head_ptr;
    
    if( head_ptr == NULL)
    {
        
        head_ptr = new node(entry, priority);
		++many_nodes;
		return;
    }
    
    if( priority > head_ptr->priority() )
    {
        
        head_ptr = new node(entry, priority, head_ptr);
		++many_nodes;
		return;
    }
    
    while ( p->link() != NULL && p->link()->priority() >= priority )
    {
        
        p = p->link();
        
    }
    
    p->set_link(new node(entry, priority, p->link() ) );
                
    ++many_nodes;
}

PriorityQueue::Item PriorityQueue::get_front( ){
    
	assert( size() > 0 );
    
    PriorityQueue::Item mydata;
	
	mydata = head_ptr->data();
	
	node* p;
	p = head_ptr;
	
    head_ptr = head_ptr->link();
    
	delete [] p;
	
	--many_nodes;
	
	return mydata;
	
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& other){
	
	if ( &other == this)
		return *this;
	
	this->~PriorityQueue();
	
	if (other.head_ptr == NULL)
		return *this;
	
	node* mycur;
	node* trav;
	
	trav = other.head_ptr;
	
	head_ptr = new node(trav->data(), trav->priority(), NULL);
	
	mycur = head_ptr;
	++many_nodes;
	
	trav = trav->link();
	
	while (trav != NULL){
		
		mycur->set_link(new node(trav->data(), trav->priority()) );
		++many_nodes;
		
		mycur = mycur->link();
		trav = trav->link();
		
	}
	
	return *this;
	
}

}
    
