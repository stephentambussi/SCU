//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.

//Stephen Tambussi
#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence::sequence()
    {
        init();
    }

    //Copy Constructor
    sequence::sequence(const sequence& source)
    {
        init();
        *this = source;
    }
    sequence::~sequence()
    {
        list_clear(head_ptr);
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }
    void sequence::start()
    {
        precursor = NULL;
        cursor = head_ptr;
    }
    void sequence::end()
    {
        if(many_nodes == 0) return;
        cursor = tail_ptr;
        if(head_ptr == tail_ptr)//one node in list, precursor is null
            precursor = NULL;
        else
            precursor = list_locate(head_ptr, many_nodes-1);//precursor = tail-1
    }
    void sequence::advance()
    {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }
    void sequence::insert(const value_type& entry)
    {
        if(!is_item() || precursor == NULL)
        {
            list_head_insert(head_ptr, entry);
            if(tail_ptr == NULL)//no tail --> tail points to front
                tail_ptr = head_ptr;
            cursor = head_ptr;
            precursor = NULL;
            many_nodes++;
        }
        else
        {
            list_insert(precursor, entry);
            cursor = precursor->link();
            many_nodes++;
        }
    }
    void sequence::attach(const value_type& entry)
    {
        //3 cases
        if(head_ptr == NULL)//empty list
        {
            list_head_insert(head_ptr, entry);
            tail_ptr = head_ptr;
            cursor = head_ptr;
            precursor = NULL;
        }
        else if(cursor == NULL)//precursor at tail
        {
            list_insert(tail_ptr, entry);
            cursor = tail_ptr->link();
            precursor = tail_ptr;
            tail_ptr = tail_ptr->link();
        }
        else //insert after cursor
        {
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            if(cursor->link() == NULL)
                tail_ptr = cursor;
        }
        many_nodes++;
    }
    void sequence::operator=(const sequence& source)
    {
        if(this == &source) return;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        start();
        node* tmp = source.head_ptr;
        while(tmp != source.cursor)
        {
            advance();
            tmp = tmp->link();
        }
    }
    void sequence::remove_current()
    {
        assert(is_item());
        //3 cases
        if(cursor == head_ptr)//at head of sequence
        {
            //2 cases
            if(head_ptr == tail_ptr)//one node in list
            {
                list_head_remove(head_ptr);
                head_ptr = NULL;
                tail_ptr = NULL;
                cursor = NULL;
                precursor = NULL;
            }
            else//greater than one
            {
                list_head_remove(head_ptr);
                cursor = head_ptr;
                precursor = NULL;
            }
        }
        else if(cursor == tail_ptr)//at end of sequence
        {
            list_remove(precursor);
            tail_ptr = precursor;
            cursor = NULL;
        }
        else//in the middle somewhere in sequence
        {
            list_remove(precursor);
            cursor = cursor->link();
        }
        many_nodes--;
    }
    sequence::size_type sequence::size() const
    {
        return many_nodes;
    }
    bool sequence::is_item() const
    {
        if(cursor == NULL) return false;
        else return true;
    }
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return cursor->data();
    }
}
