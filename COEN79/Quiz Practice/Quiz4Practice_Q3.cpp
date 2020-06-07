//function to increase the size the size of the dynamic array
//do not use copy function
template<class Item>
void queue<Item>::reserve(size_type new_capacity)
{
    value_type* larger_array;
    if(new_capacity == capacity) return;
    if(new_capacity < count)
        new_capacity = count;
    larger_array = new value_type[new_capacity];
    if(count == 0)
    {
        first = 0;
        last = new_capacity-1;
    }
    else
    {
        size_type tmpCount = count;
        size_type new_last = new_capacity - 1;
        while(tmpCount > 0)
        {
            new_last = (new_last+1) % new_capacity;
            larger_array[new_last] = data[first];
            first = (first + 1) % capacity;
            --tmpCount;
        }
        first = 0;
        last = new_last;
    }
    capacity = new_capacity;
    delete[] data;
    data = larger_array;
}