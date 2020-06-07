//The constructor allocates an array of block pointers 
//and initializes all of its entries with NULL. 
//The initial size of the array is init_bp_array_size.
template < class Item >
deque<Item>::deque(int init_bp_array_size, int init_block_size)
{
    bp_array_size = init_bp_array_size;
    block_size = init_block_size;
    block_pointers = new value_type*[bp_array_size];
    for(size_type index = 0; index < bp_array_size; ++index)
    {
        block_pointers[index] = NULL;
    }
    block_pointers_end = block_pointers + (bp_array_size-1);
    first_bp = last_bp = NULL;
    front_ptr = back_ptr = NULL;
}