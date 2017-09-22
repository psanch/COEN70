// FILE: node.cpp
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t

using namespace std;

namespace scu_coen70_6B
{
    template<class Item>
    size_t list_length(const node<Item>* head_ptr)
    // Library facilities used: cstdlib
    {
	const node<Item>* cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }
    
    template<class Item>
    void list_head_insert(node<Item>*& head_ptr, const Item& entry)
    {
    	head_ptr = new node<Item>(entry, head_ptr);
    }

    
    template<class Item>
    void list_insert(node<Item>* previous_ptr, const Item& entry)
    {
    	node<Item>* insert_ptr;

    	insert_ptr = new node<Item>(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    template<class Item>
    node<Item>* list_search(node<Item>* head_ptr, const Item& target)
    // Library facilities used: cstdlib
    {
    	node<Item>* cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    template<class Item>
    const node<Item>* list_search(const node<Item>* head_ptr, const Item& target)
    // Library facilities used: cstdlib
    {
    	const node<Item>* cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    template<class Item>
    node<Item>* list_locate(node<Item>* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node<Item>* cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    template<class Item>
    const node<Item>* list_locate(const node<Item>* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node<Item>* cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    template<class Item>
    void list_head_remove(node<Item>*& head_ptr)
    {
    	node<Item>* remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    template<class Item>
    void list_remove(node<Item>* previous_ptr)
    {
    	node<Item>* remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    template<class Item>
    void list_clear(node<Item>*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    template<class Item>
    void list_copy(const node<Item>* source_ptr, node<Item>*& head_ptr, node<Item>*& tail_ptr)
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

    template<class Item>
    void list_piece(node<Item>* start_ptr, node<Item>* end_ptr, node<Item>*& head_ptr, node<Item>*& tail_ptr)
    // Library facilities used: stdlib.h
    {
        head_ptr = NULL;
        tail_ptr = NULL;

        // Handle the case of the empty list or list with single item.
        if (start_ptr == NULL || start_ptr == end_ptr)
            return;

        // Make the head node for the newly created list, and put data in it
        // We know there is at least one item to copy because of the above
        // (start_ptr != end_ptr) check.
        list_head_insert(head_ptr, start_ptr->data());
        tail_ptr = head_ptr;

        // Copy the rest of the nodes one at a time, adding at the tail of new list
        for (start_ptr = start_ptr->link();
             start_ptr != NULL && start_ptr != end_ptr;
             start_ptr = start_ptr->link())
        {
            list_insert(tail_ptr, start_ptr->data());
            tail_ptr = tail_ptr->link();
        }
    }

    template<class Item>
    size_t list_occurrences(node<Item>* head_ptr, const Item& target)
    {
        size_t answer = 0;

        for (head_ptr = list_search(head_ptr, target);
             head_ptr != NULL;
    	     head_ptr = list_search(head_ptr->link(), target))
    	answer++;

        return answer;
    }

    template<class Item>
    void list_insert_at(node<Item>*& head_ptr, const Item& entry, size_t position)
    {
        assert(position > 0);
        node<Item>* precursor;

        if (position == 1)
    	   list_head_insert(head_ptr, entry);
        else
        {
        	precursor = list_locate(head_ptr, position-1);
        	assert(precursor != NULL);
        	list_insert(precursor, entry);
        }
    }

    template<class Item>
    Item list_remove_at(node<Item>*& head_ptr, size_t position)
    {
        assert(position > 0);
        node<Item>* precursor;
        Item answer;

        if (position == 1)
        {
    	assert(head_ptr != NULL);
    	answer = head_ptr->data();
    	list_head_remove(head_ptr);
        }
        else
        {
    	precursor = list_locate(head_ptr, position-1);
    	assert(precursor != NULL);
    	assert(precursor->link() != NULL);
    	answer = precursor->link()->data();
    	list_remove(precursor);
        }
        return answer;
    }

    template<class Item>
    node<Item>* list_copy_segment(node<Item>* head_ptr, size_t start, size_t finish)
    {
        node<Item>* start_ptr;
        node<Item>* finish_ptr;
        node<Item>* new_head;
        node<Item>* new_tail;

        assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
        ++finish;
        

        start_ptr = list_locate(head_ptr, start);
        assert(start_ptr != NULL);
        finish_ptr = list_locate(start_ptr, finish-start+1);
        list_piece(start_ptr, finish_ptr, new_head, new_tail);
        return new_head;
    }
    
    //NON CONSTANT ITERATOR
    template<class Item>
    node_iterator<Item>::node_iterator(node<Item>* initial){
        
        current = initial;
        
    }
    
    template<class Item>
    Item& node_iterator<Item>::operator *( ) const       // Dereference, gets value of current
    {
        
        return current->data();
        
    }
    
    template<class Item>
    node_iterator<Item>& node_iterator<Item>::operator ++( )   // Prefix ++
    {
        
        current = current->link();
        return *this;
        
    }
    
    template<class Item>
    node_iterator<Item> node_iterator<Item>::operator ++(int)      // Postfix ++
    {
        node_iterator orig(current);
        current = current->link();
        return orig;
        
    }
    
    template<class Item>
    bool node_iterator<Item>::operator ==(const node_iterator other) const
    {
        
        return ( current == other.current);
        
        
    }
    
    template<class Item>
    bool node_iterator<Item>::operator !=(const node_iterator other) const
    {
        
        return (current != other.current);
        
    }
    
    //CONST ITERATOR
    
    
    template<class Item>
    const_node_iterator<Item>::const_node_iterator(const node<Item>* initial)
    {
        
        current = initial;
        
    }
    
    template<class Item>
    const Item& const_node_iterator<Item>::operator *( ) const       // Dereference, gets value of current
    {
        
        return current->data();
        
    }
    
    template<class Item>
    const_node_iterator<Item>& const_node_iterator<Item>::operator ++( )   // Prefix ++
    {
        
        current = current->link();
        return current;
        
    }
    
    template<class Item>
    const_node_iterator<Item> const_node_iterator<Item>::operator ++(int)      // Postfix ++
    {
        
        const_node_iterator orig(current);
        current = current->link();
        return orig;
        
    }
    
    template<class Item>
    bool const_node_iterator<Item>::operator ==(const const_node_iterator other) const
    {
        
        return (current == other.current);
        
        
    }
    
    template<class Item>
    bool const_node_iterator<Item>::operator !=(const const_node_iterator other) const
    {
        
        return (current != other.current);
        
        
    }
    
}
