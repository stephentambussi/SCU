template <class Item>
queue<Item>::queue(const queue <Item>& source)
{
    //copy only valid entries of one array to new array
    //don't use copy function
    //class uses dynamic array
    data = new value_type[source.capacity];
    capacity = source.capacity;
    count = source.count;
    first = source.first;
    last = source.last;
    if(source.count != 0)
    {
        size_type tmpCount = count;
        size_type tmpCursor = first;
        while(tmpCount > 0)
        {
            data[tmpCursor] = source.data[tmpCursor];
            tmpCursor = (tmpCursor+1) % capacity;
            --tmpCount;
        }
    }


}