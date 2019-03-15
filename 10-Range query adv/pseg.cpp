struct pseg{
	static int t;
	int l, r, x;
	pseg(){
		l = r = x = 0;
	}
}T[4000010];

int pseg::t = 0, n, q, root[200010];

void upd(int &pos, int ref, int val, int l = 0+1, int r = n+1){
	pos = ++pseg::t;
	T[pos] = T[ref];
	T[pos].x++;
	if(l+1 == r)
		return;
	int mid = (l+r)/2;
	if(val < mid)
		upd(T[pos].l, T[ref].l, val, l, mid);
	else
		upd(T[pos].r, T[ref].r, val, mid, r);
}

int ask(int root, int x, int y, int l = 0+1, int r = n+1){
	if(x >= r || l >= y) return 0;
	if(x <= l && r <= y) return T[root].x;
	
	return ask(T[root].l, x, y, l, l+r>>1)+ask(T[root].r, x, y, l+r>>1, r);	
}
