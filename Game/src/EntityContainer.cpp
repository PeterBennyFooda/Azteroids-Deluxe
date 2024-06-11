#include "EntityContainer.h"

EntityContainer::EntityContainer()
{
    capacity = 2;
    arr = new BaseEntity*[capacity];
    currentSize = 0;
}

EntityContainer::~EntityContainer() 
{
    delete[] arr;
}

int EntityContainer::Size() const
{
    return currentSize;
}

void EntityContainer::Append(BaseEntity* element) 
{
    // Check if resizing is needed
    if (currentSize == capacity) {
        grow();
    }

    // Add the element to the end
    arr[currentSize++] = element;
}

BaseEntity* EntityContainer::GetAt(int index)
{
    // Check if the index is valid
    if (index >= 0 && index < currentSize) 
    {
        return arr[index];
    }
    else 
    {
        // Handle error
        return arr[0];
    }
}

void EntityContainer::SetAt(int index, BaseEntity* value) 
{
    // Check if the index is valid
    if (index >= 0 && index < currentSize) 
    {
        arr[index] = value;
    }
    else 
    {
        // Handle error
    }
}

void EntityContainer::grow() 
{
    // Double the capacity
    capacity *= 2;
    BaseEntity** newArr = new BaseEntity* [capacity];

    // Copy elements from the old array to the new array
    for (int i = 0; i < currentSize; ++i) 
    {
        newArr[i] = arr[i];
    }

    // Delete the old array
    delete[] arr;
    arr = newArr;
}

void EntityContainer::shrink()
{
    if (currentSize <= 0)
        return;

    // Creating new array of half size
    capacity = currentSize;
    BaseEntity** newArr = new BaseEntity* [capacity];

    // copy element of old array in newly created array
    for (int i = 0; i < currentSize; i++) 
    {
        newArr[i] = arr[i];
    }

    // Delete old array
    delete[] arr;
    arr = newArr;
}

void EntityContainer::InsertAt(int index, BaseEntity* value)
{
    if (currentSize == capacity) 
    {
        grow();
    }

    for (int i = currentSize - 1; i >= index; i--) {
        arr[i + 1] = arr[i];
    }

    arr[index] = value;
    currentSize++;
}

void EntityContainer::RemoveAt(int index)
{
    for (int i = index; i < currentSize; i++) 
    {
        arr[i] = arr[i + 1];
    }

    // Replace the last index by 0
    arr[currentSize - 1] = 0;
    currentSize--;

    // Reduce if the container half element of its capacity
    if (currentSize>0 && currentSize == (capacity / 2))
    {
        shrink();
    }
}

int EntityContainer::Search(BaseEntity* key)
{
    for (int i = 0; i < currentSize; i++) 
    {
        if (arr[i] == key) 
        {
            // If element found return its index
            return i;
        }
    }

    return -1;
}

