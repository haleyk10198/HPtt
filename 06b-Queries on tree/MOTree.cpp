struct query{
	int hl, hr, id, l;
	query(int l, int r, int i):hl(l), hr(r), id(i), l(0){
	}
	query(int l, int r, int i, int lca):hl(l), hr(r), id(i), l(lca){
	}
	query(){
	}
}qs[60010];

void consider(int node){
	if(st[node]) rem(node);
	else inc(node);
	
	st[node] ^= 1;
	return;
}

void moveTo(int hl, int hr){
	while(hl < gl)
		consider(inv[--gl]);
	while(hr > gr)
		consider(inv[++gr]);
	while(hr < gr)
		consider(inv[gr--]);
	while(hl > gl)
		consider(inv[gl++]);
	return;
}

int lca(int u, int v){
	if(d[u] < d[v]) return lca(v, u);
	for(int i = 16; i >= 0; i--)
		if(d[par[i][u]] >= d[v])
			u = par[i][u];
	
	if(u == v)
		return u;
	
	for(int i = 16; i >= 0; i--)
		if(par[i][u] != par[i][v])
			u = par[i][u], v = par[i][v];
	
	return par[0][u];
}

/* Given query range nodes {x, y}, l = lca(u, v)
	if(u == l || l == v)
		qs[i] = query(en[u], en[v], i);
	else
		qs[i] = query(ed[u], en[v], i, l);
	
	sort(qs, qs+m, [](query x, query y){
		if(x.hl/SQN != y.hl/SQN)
			return x.hl/SQN < y.hl/SQN;
		if(x.hr != y.hr)
			return x.hr < y.hr;
		return x.id < y.id;
	});
	
	for(int i = 0; i < m; i++){
		query q = qs[i];
		moveTo(q.hl, q.hr);
		if(q.l)	consider(q.l);
		res[q.id] = mp(q1, q2);
		if(q.l) consider(q.l);
	}*/

