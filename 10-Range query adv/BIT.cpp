int T[MAXN], n;

int ask(int pos)
// returns sum[0, pos]
{
	int sum = 0;
	for( ++pos; pos; pos-=pos&-pos)
	// remove ++pos to sum[0, pos)
	{
		sum += T[pos];
	}
	return sum;
}

void update(int pos, int dv)
// a[pos] += dv;
{
	for(++pos; pos <= n; pos+=pos&-pos)
		T[pos] += dv;
	return;
}
