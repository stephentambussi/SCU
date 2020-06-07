//Removes item from front of the deque
template <class Item>
void deque<Item>::pop_front()
{
    assert(!isEmpty());
    if(back_ptr == front_ptr)
    {
        for(size_type i = 0; i < bp_array_size; ++i)
        {
            delete[] block_pointers[index];//deletes blocks
            block_pointers[index] = NULL;
            //array of pointers to blocks points to nothing
        }
        first_bp = last_bp = NULL;
        front_ptr = back_ptr = NULL;
    }
    else if(front_ptr == (*first_bp + block_size - 1))
    //last element of first block
    {
        //removes last element of first block & deletes first block
        delete[] (*first_bp);
        *first_bp = NULL;
        //then ptr goes to next element
        //in block_pointers array
        ++first_bp;
        front_ptr = *first_bp;
    }
    else 
        ++front_ptr;

}