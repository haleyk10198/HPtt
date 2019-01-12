int parent[LGN][MAXN]; //parent[0][MAXN] through DFS

void build(){
	for(int i = 1; i < LGN; i++){
		for(int node = 1; node <= n; node++){
			parent[i][node] = parent[i-1][parent[i-1][node]];
		}
	}
}

int walk(int node, int step){
	for(int i = LGN-1; i >= 0; i--){
		if(step&(1<<i)){
			node = parent[i][node];
		}
	}
}

int depth[MAXN]; // also initialized through DFS
int LCA(int u, int v){
	if(depth[u] < depth[v]) swap(u, v);
	walk(u, depth[u]-depth[v]); // adjust
	
	if(u == v) return u;
	
	for(int i = LGN-1; i >= 0; i--){
		if(parent[i][u] == parent[i][v])
		// the answer is < 2^i
		;
		else{
			u = parent[i][u];
			v = parent[i][v];
			// answer -= 2^i, then it is still bounded for binary search
		}
	}
}
