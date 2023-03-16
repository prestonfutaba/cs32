#include "newSet.h"
#include <iostream>

Set::Set(int x)
{
	if (x < 0)
	{
		exit(1);
	}

	set = new ItemType[x];
	capacity = x;
	set_size = 0;
}

Set::Set(const Set& other) //CC
{
	capacity = other.capacity;
	set_size = other.set_size;
	set = new ItemType[other.set_size];

	for (int i = 0; i < set_size; i++) 
	{
		*(set + i) = *(other.set + i);
	}
}

Set& Set::operator=(const Set& other) //AO
{
	Set temp(other);
	swap(temp); //don't care what temp is afterwards so it is fine to have the original set 
	return *this;
}

Set::~Set() //Destructor --> no memory leaks!
{
	delete[] set;
}

bool Set::empty() const
{
	if (set_size == 0)
		return true;
	return false;
}

int Set::size() const
{
	return set_size;
}

bool Set::insert(const ItemType& value)
{
	if (set_size >= capacity || set_size < 0)
	{
		return false;
	}

	else if (set_size == 0)
	{
		set[0] = value;
		set_size++;
		return true;
	}

	else {
		for (int i = 0; i < set_size; i++)
		{
			if (set[i] == value)
			{
				return false;
			}
		}
		set[set_size] = value;
		set_size++;
		return true;
	}
	return false;
}

bool Set::erase(const ItemType& value)
{
	for (int i = 0; i < set_size; i++)
	{
		if (set[i] == value)
		{
			for (int j = i; j < set_size - 1; j++)
			{
				set[j] = set[j + 1];
			}
			set_size--;
			return true;
		}

	}
	return false;
}

bool Set::contains(const ItemType& value) const
{
	for (int i = 0; i < set_size; i++)
	{
		if (set[i] == value)
		{
			return true;
		}
	}
	return false;
}

bool Set::get(int i, ItemType& value) const
{
	if (i >= 0 && i < set_size)
	{
		for (int j = set_size - 1; j >= 0; j--)
		{
			int counter = 0;
			for (int k = set_size - 1; k >= 0; k--)
			{
				if (set[j] > set[k])
				{
					counter++;
				}
			}
			if (counter == i)
			{
				value = set[j];
				return true;
			}
		}
		return false;
	}
	else
		return false;

}

void Set::swap(Set& other)
{
	ItemType* ptr = set;
	set = other.set;
	other.set = ptr;

	int m_set_size = set_size;
	set_size = other.set_size;
	other.set_size = m_set_size;

	int m_capacity = capacity;
	capacity = other.capacity;
	other.capacity = m_capacity;

}