void removeBad(list<Movie*>& li)
{
	if (li.size() <= 0)
	{
		return;
	}

	for (list<Movie*>::iterator itr = li.begin(); itr != li.end(); )
	{
		if ((*itr)->rating() < 50)
		{
			delete* itr;
			itr = li.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}
