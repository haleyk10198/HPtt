int tab[LGN][MAXN<<1];
vi e[MAXN], en[now], ed[now], euler, d[MAXN];

void dfs(int now, int prv){
	en[now] = euler.size();
	d[now] = d[prv]+1;
	euler.push_back(now);
	for(auto x: e[now]){
		if(x != prv){
			dfs(x, now);
			euler.push_back(now);
		}
	}
	ed[now] = euler.size();
	
	return;
}

void build(){
	int n = euler.size(); // n = 2*n-1
	for(int i = 0; i < n; i++){
		tab[0][i] = euler[i];
	}
	
	for(int i = 1; i < LGN; i++){
		for(int j = 0; j+(1<<i) <= n; j++){
			int x = tab[i-1][j];
			int y = tab[i-1][j+(1<<(i-1))];
			if(d[x] < d[y]) tab[i][j] = x;
			else tab[i][j] = y;
		}
	}
	
	return;
}

int ask(int x, int y){
	if(en[x] > en[y]) swap(x, y);
	x = en[x]; y = ed[y];
	int h = sizeof(int)*8 - __builtin_clz(y-x) + 1; // lg2(y-x)
	int u = tab[h][x];
	int v = tab[h][y-(1<<h)];
	
	if(d[u] < d[v]) return u;
	else return v;
}
