void removeOdd(vector<int>& v)
{
	if (v.size() <= 0)
	{
		return;
	}

	for (vector<int>::iterator itr = v.begin(); itr != v.end(); )
	{
		if (*itr % 2 != 0)
		{
			itr = v.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}