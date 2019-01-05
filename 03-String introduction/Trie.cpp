int nxt[SIGMA][MAXN];
// SIGMA = 26, MAXN = total length

int nodecnt = 1; // root initialized
int NULL_NODE = 0;

void dfs(int id){
	for(int i = 0; i < SIGMA; i++)
		if(nxt[i][id] != NULL_NODE)
			dfs(i);
}

void insert(string str, int root = 1){
	for(auto x: str){
		if(nxt[x-'a'][root] == NULL_NODE)
			nxt[x-'a'][root] = ++nodecnt;
		root = nxt[x-'a'][root];
	}
	
	//do something on root
}
