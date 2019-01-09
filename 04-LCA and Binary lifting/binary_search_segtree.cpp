// assume T[] is a segtree storing range max

// search for first apperance of something >= v, if all < v, return n
int ask(int v, int id = 1, int l = 0, int r = n)
{
	if(T[id] < v)
	// everything is < v
	{
		return n;
	}
	
	if(l+1 == r){
		if(T[id] >= v) return l;
		else return n; // just to be safe
	}
	
	if(T[id<<1] >= v)
	// if lhs stores something gte v, look into it and discard rhs
	{
		return ask(v, id<<1, l, l+r>>1);
	}
	else
	// vice versa
	{
		return ask(v, id<<1|1, l+r>>1, r);
	}
}

int general_ask(int x, int v, int id = 1, int l = 0, int r = n){
	if(x >= r)
	// if invalid segment
	{
		return n;
	}
	
	if(l+1 == r){
		if(T[id] >= v) return l;
		else return n; // writing return r won't work
	}
	
	if(l >= x)
	// if the entire segment lies within bound
	{
		return ask(v, id, l, r);
	}
	
	int ret = general_ask(x, v, id<<1, l, l+r>>1);
	if(ret == n)
	// if not found in lhs
	{
		// seek rhs
		return general_ask(x, v, id<<1|1, l+r>>1, r);
	}
	else
		return ret;
}

// assume there is an getID(pos) function to map pos \in [0, n) to ID in trees

// generalized case: What if starting point is not fixed at 0?
// You should store T[id].bounds = [l, r) in this case as we are not traversing the tree top-down
int general_ask2(int start, int v){
	int id = getID(start);
	while(T[id].v < v){	
		if(T[id].r == n){
			// everything after start is peeked, but nothing shows up, then terminate
			return n;
		}
		if(id%2 == 0)
		// if id is a left child, walk to parent for a larger valid segment
		{
			id /= 2;
		}
		else if(id%2 == 1)
		// else, walk to the sibling
		{
			id++;
		}
	}
	
	// now we are in a segment which starts later than "start", and it contains something gte v
	return ask(v, id, T[id].l, T[id].r);
	// reuse the previous function!
}
