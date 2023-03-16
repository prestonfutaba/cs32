void removeOdd(list<int>& li)
{
	if (li.size() <= 0)
	{
		return;
	}
	
	for (list<int>::iterator itr = li.begin(); itr != li.end(); )
	{
		if (*itr % 2 != 0)
		{
			itr = li.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}


