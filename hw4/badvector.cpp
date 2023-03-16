void removeBad(vector<Movie*>& v)
{
	if (v.size() <= 0)
	{
		return;
	}

	for (vector<Movie*>::iterator itr = v.begin(); itr != v.end(); )
	{
		if ((*itr)->rating() < 50)
		{
			delete* itr;
			itr = v.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}
