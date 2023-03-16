#include "Set.h"
#include <iostream>

using namespace std;

Set::Set() {
	// initialize empty set
	set_size = 0;
	head = nullptr;
	tail = nullptr;
}

Set::~Set() {
	// no memory to clear if empty set
	if (head == nullptr)
		return;

	// else we need to clear dynamically allocated memory
	Node* curr = head;
	Node* nextNode;

	while (curr != nullptr) {
		nextNode = curr->next;
		delete curr;
		curr = nextNode;
	}
}

Set::Set(const Set& other) 
{
	// sets fields equal to other's 
	set_size = other.set_size;

	if (other.set_size == 0) { // if other is empty, new set is set to empty too
		head = nullptr;
		tail = nullptr;
		return;
	}

	// other case, create new linked list
	head = new Node;
	head->prev = nullptr;

	Node* curr = head;

	// copies all but the last node, dynamically allocate new nodes as traverse through list
	for (Node* cNode = other.head; cNode->next != nullptr; cNode = cNode->next)
	{
		Node* newNode = new Node;

		curr->m_item = cNode->m_item;
		curr->next = newNode;
		newNode->prev = curr;

		curr = newNode;
	}

	//copies data to last node and sets next to nullptr
	curr->m_item = other.tail->m_item;
	curr->next = nullptr;

	//set the tail pointer
	tail = curr;
}


Set& Set::operator=(const Set& rhs) 
{
	// checks if two lists are equivalent, if they are the two sets are already equal and we just return
	if (this != &rhs) 
	{
		Set temp(rhs); // creates temporary copy of rhs
		swap(temp); // switches contents of lhs and temp
	} // temp will be destroyed at the end of this loop and the dynamically allocated memory will be cleared if ~Set() is done correctly

	return *this;
}

bool Set::empty() const
{
	if (set_size == 0) //empty Set defined to have nothing inside, so set_size = 0 if empty set
	{
		return true;
	}
	return false;
}

int Set::size() const
{
	return set_size; //return size of Set aka set_size
}

bool Set::insert(const ItemType& value)
{
	if (contains(value)) // checks if value exists within the set, can't have duplicates
		return false;

	if (set_size == 0)
	{
		Node* newNode = new Node;
		newNode->m_item = value; // set new node's "item" to value
		newNode->prev = nullptr;
		newNode->next = nullptr;

		head = newNode; // only value so between head and tail
		tail = newNode;

		// increments number of items
		set_size++;
		return true;
	}

	// creates new node and sets its fields (non zero case)
	Node* newNode = new Node;
	newNode->m_item = value;
	newNode->prev = tail;
	newNode->next = nullptr;

	// sets the set's fields
	tail->next = newNode;
	tail = newNode;

	//increments number of items
	set_size++;
	return true;
}

bool Set::erase(const ItemType& value) 
{
	if (!contains(value)) // erase returns false if value not contained, nothing to erase
		return false;

	Node* currNode = head;
	for (Node* curr = head; curr != nullptr; curr = curr->next) // iterates through the list to find the node corresponding to value, sets currNode to curr
	{ 
		if (curr->m_item == value)
		{
			currNode = curr;
			break;
		}
			
	}

	if (currNode->prev != nullptr) // aka value is not the item of the first node
	{
		currNode->prev->next = currNode->next; // node above value linked to the one below
	}
	else 
	{
		head = currNode->next; // if head node is erased, head points to new first node
	}

	if (currNode->next != nullptr) 
	{
		currNode->next->prev = currNode->prev; // node below value linked to the one above
	}
	else {
		tail = currNode->prev; // if removing tail node, point tail to new tail node
	}

	set_size--; // decrements set size
	delete currNode; // remove removed node
	return true;
}

bool Set::contains(const ItemType& value) const 
{
	for (Node* curr = head; curr != nullptr; curr = curr->next)
	{ // iterate through linked list
		if (curr->m_item == value)
			return true; // searches for value, if value is found then the Set contains the value
	}

	return false;
}

bool Set::get(int pos, ItemType& value) const 
{

	if (pos >= 0 || pos < set_size)
	{
		for (Node* curr_j = head; curr_j != nullptr; curr_j = curr_j->next) //double iteration
		{
			int counter = 0;
			for (Node* curr_k = head; curr_k != nullptr; curr_k = curr_k->next) //compare each term to eachother
			{
				if (curr_j->m_item > curr_k->m_item)
				{
					counter++; // counts how many terms the current item is greater than
				}
			}
			if (counter == pos)
			{
				value = curr_j->m_item;
				return true; // function succeeds
			}
		}
		return false;
	}
	else
		return false;
}

void Set::swap(Set& other)
{
	int temp_size = set_size; // swap the set sizes
	set_size = other.set_size;
	other.set_size = temp_size;

	Node* temp_head = head; // swap heads of the sets
	head = other.head;
	other.head = temp_head;

	Node* temp_tail = tail; //swap tails of the sets
	tail = other.tail;
	other.tail = temp_tail;
}

void unite(const Set& s1, const Set& s2, Set& result) {
	result = s1; // copies s1 into result

	for (int i = 0; i < s2.size(); i++) 
	{ // insert items of s2 into s1
		ItemType m_insert; // stores what to insert (temporary)
		s2.get(i, m_insert);
		result.insert(m_insert); // insert function means no repeats
	}
}

void butNot(const Set& s1, const Set& s2, Set& result) {

	if (&s1 == &s2) { // if the sets are the same, subtracting them results in an empty set
		Set empty;
		result = empty;
		return;
	}

	result = s1;

	for (int i = 0; i < s2.size(); i++) { // removes elements of s2 from s1
		ItemType m_erase; // stores what to remove (temporary)
		s2.get(i, m_erase);
		result.erase(m_erase); // erase only removes if exists
	}
}