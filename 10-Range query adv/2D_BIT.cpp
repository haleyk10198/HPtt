// full code: https://csacademy.com/submission/1526005/

vector<int> points[30010], trees[30010];
int n, m;	

void addPoint(int x, int y){
	// m is the first dimension, add x until M
	for( ; x <= m; x+=x&-x)
		points[x].pb(y);
}

void update(int x, int y, int v){
	for(x; x <= m; x+=x&-x){
		// Go through the first dimension
		auto it = lower_bound(points[x].begin(), points[x].end(), y);
		// For the second dimension, find the corresponding record for starting point
		// Since we are doing sparse tree, we take the closest next point
		for(int j = it-points[x].begin()+1; j < points[x].size(); j+=j&-j)
			trees[x][j] += v;
	}
}

int ask(int x, int y){
	int ret = 0;
	for(; x > 0; x-=x&-x)
	{
		auto it = upper_bound(points[x].begin(), points[x].end(), y);
		int j = it-points[x].begin();
		for( j; j >= 0; j-=j&-j){
			ret += trees[x][j];
			if(j == 0)
				break;
		}
	}
	return ret;
}
