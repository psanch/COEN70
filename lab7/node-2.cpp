// FILE: node.cpp
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace coen70_lab7
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
    {
        head_ptr = start_ptr;
        tail_ptr = start_ptr;
        
        while( tail_ptr->link() != end_ptr)
            tail_ptr = tail_ptr->link();
        tail_ptr = tail_ptr->link();
    }

    size_t list_occurrences(node* head_ptr, const node::value_type& target)
    {
        node* cursor;
        cursor = head_ptr;
        size_t i = 0;
        
        
        while(cursor != NULL){
            
            if(cursor->data() == target) i++;
            
            cursor = cursor->link();
        }
        
        return i;

    }

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
    {
        assert(head_ptr != NULL && position > 0 && position <= list_length(head_ptr)+1);
    
        node* cursor = head_ptr;
        size_t i;
        
        if( position == 1){
            
            list_head_insert(head_ptr,entry);
            return;
            
        }
        
        for (i = 2 ; i < position; i++, cursor = cursor->link() );
        
        node* creator = new node(entry, cursor->link());
        
        cursor->set_link(creator);
        
        return;
    
    }

    node::value_type list_remove_at(node*& head_ptr, size_t position)
    {
        assert(head_ptr != NULL && position <= list_length(head_ptr));
        
        node* cursor = head_ptr;
        node::value_type tmp;
        
        if( position == 1){
            
            head_ptr = head_ptr->link();
            tmp = cursor->data();
            delete [] cursor;
            return tmp;
            
        }
        
        for (size_t i = 2 ; i < position; i++, cursor = cursor->link() );
        
        node* agent = cursor->link();
        
        cursor->set_link(agent->link());
        
        tmp = agent->data();
        
        delete [] agent;
        
        return tmp;
        
    }

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
    {
        assert( (1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)) );
        
        if (head_ptr == NULL)
            return NULL;
        
        node* cursor = head_ptr;
        node* prelister;
        node* lister;
        node* starter;
        node* finisher;
        node* top;
        size_t i;
        
        for ( i = 1; i < start ; i++, cursor = cursor->link() );
        
        starter = cursor;
        
        for ( ; i < finish ; i++, cursor = cursor->link() );
        
        finisher = cursor;
        
        top = new node(starter->data() , NULL);
        
        //if(start == finish) return top;
        
        cursor = starter->link();
        
        prelister = top;
        
        while(cursor != finisher->link() ){
            
            lister = new node (cursor->data() , NULL);
            prelister->set_link(lister);
            
            prelister = lister;
            cursor = cursor->link();
            
        }
        
        return top;
    }

}

