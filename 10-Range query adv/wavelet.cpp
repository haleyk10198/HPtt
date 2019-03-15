struct wavelet{
	vi v, ml, mr;
	int n, mi, mx;
	wavelet *lhs, *rhs;
	wavelet(){
		mi = INF, mx = -INF;
		v = ml = mr = vi();
		n = 0;
		lhs = rhs = nullptr;
	}
	void build(void){
		for(auto x: v)
			mi = min(x, mi), mx = max(x, mx);
		if(mi == mx) return;
		int mid = mi+mx>>1;
		lhs = new wavelet();
		rhs = new wavelet();
		for(int i = 0; i < n; i++){
			wavelet *ref = (v[i] <= mid? lhs: rhs);
			ref->n++, ref->v.pb(v[i]);
			ml.pb(lhs->n), mr.pb(rhs->n);
		}
		lhs->build();
		rhs->build();
		return;
	}
	int ask(int l, int r, int rank){
		if(mi == mx) return mi;
		int lt = ml[r]-(l? ml[l-1]: 0);
		if(lt >= rank)
			return ask(ml[l], ml[r], rank);
		else
			return ask(mr[l], mr[r], rank);
	}
}root;

