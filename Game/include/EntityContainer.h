#pragma once

////////////////////////////////////////////////////////////
// This file is used to store entities in a container.
// It is used to replace STL containers for EntityManager.
////////////////////////////////////////////////////////////

#include"Entity.h"

class EntityContainer 
{
private:
    void grow();
    void shrink();

    BaseEntity** arr;
    int capacity;
    int currentSize;

public:
    EntityContainer();
    ~EntityContainer();

    void Append(BaseEntity* element);
    BaseEntity* GetAt(int index);
    void SetAt(int index, BaseEntity* value);
    void InsertAt(int index, BaseEntity* value);
    void RemoveAt(int index);
    int Search(BaseEntity* key);
    int Size() const;
};