int na[MAXN], sz[MAXN], cfa[MAXN], croot;
//assume vi e[MAXN] exists

vi ce[MAXN];
vi cst;

void runCen(int);

int mib, center;

void dfssz(int now, int prv){
	// trivial set sz
	sz[now] = 1;
	for(auto x: e[now])
		if(x-prv && not na[x]){
			// na[x] means whether a node has been picked as center
			// thus "not available"
			dfssz(x, now), sz[now] += sz[x];
		}
	return;
}

void choose(int now){
	// construct the auxiliary tree
	if(cst.size())
		cfa[now] = cst.back(), ce[cst.back()].pb(now);
	else
		croot = now;
	cst.pb(now);
	na[now] = 1; // block this node
	for(auto x: e[now])
		if(not na[x])
			runCen(x); // run CD on all other connected components
	cst.pop_back();
}

void pickCen(int now, int prv, int tot = -1){
	int mx = 0, id = -1;
	if(tot == -1) tot = sz[now];
	// tot is the size of the current tree concerned
	for(auto x: e[now])
		if(not na[x] && x-prv){
			pickCen(x, now, tot);
			if(sz[x] > mx){
				mx = sz[x];
			}
		}
	
	mx = max(mx, tot-sz[now]);
	// the maximum component is either the children or the tree excluding self
	if(mx < mib){
		// if it breaks the tree best
		mib = mx;
		center = now;
	}
	return;
}

void runCen(int root = 1){
	mib = INF; 
	// reset the criteria for being the best candidate
	dfssz(root, root); 
	// configurate size, especially after a center was chose and some nodes may have different size
	pickCen(root, root); 
	// pick the center based on the newly configurated size
	choose(center);
	// choose the center and update structures accordingly
	return;
}

