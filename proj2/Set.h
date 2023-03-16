#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set(); //need our own destructor
    Set(const Set& other); //need our own CC
    Set& operator=(const Set& rhs); //need our own AO

    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);

private:
    struct Node {
        ItemType m_item;
        Node* next;
        Node* prev;
    };

    int set_size;
    Node* head;
    Node* tail;
};

void unite(const Set& s1, const Set& s2, Set& result);
void butNot(const Set& s1, const Set& s2, Set& result);

#endif