class MyHash
{
	int insert(Elem e)
	{
		if(size < M)	
		{
			int key = getKey(e);
			Elem home = h(key); //h = hash()

			for(pos = home, i = 1; !EEComp::eq(HT[pos],EMPTY) && !EEComp::(HT[pos, TOMB]); i++)
			{
				if(EEComp::eq(HT[pos], e))
				return -2;
				pos = (home + p(key, i)) % M;
			}

			HT[pos] = e;	
			size++;

			return pos;
		}

		return -1;
	}
}
