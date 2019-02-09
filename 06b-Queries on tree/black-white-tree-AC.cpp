/* Author haleyk10198 */
/* §@ªÌ:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

#define MOD 1000000007
#define LINF (1LL<<60)
#define INF 2147483647
#define PI 3.1415926535897932384626433
#define ll long long
#define pii pair<int,int>
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back((x))
#define vi vector<int>
#define vvi vector<vi>
#define EPS 1e-9
#define MAXN 50010

using namespace std;

int n, m, a[MAXN];

vi e[MAXN], euler;
int na[MAXN], sz[MAXN], croot, ch[2][MAXN], res[2][MAXN];
int tab[20][2*MAXN], en[MAXN], d[MAXN], cfa[MAXN], cop[2][MAXN];
//assume vi e[MAXN] exists

vi ce[MAXN];
vi cst;

void dfs(int now, int prv){
	en[now] = euler.size();
	euler.pb(now);
	d[now] = d[prv]+1;
	for(auto x: e[now])
		if(x-prv)
			dfs(x, now), euler.pb(now);
}

void buildpar(void){
	dfs(1, 1);
	
	for(int j = 0; j < euler.size(); j++)
		tab[0][j] = euler[j];
	
	for(int i = 1; i < 20; i++)
		for(int j = 0; j < euler.size(); j++){
			int u = tab[i-1][j], v = tab[i-1][j+(1<<(i-1))];
			tab[i][j] = (d[u] < d[v]? u: v);
		}
	
	return;
}

int lca(int u, int v){
	u = en[u], v = en[v];
	if(u > v) swap(u, v);
	int h = sizeof(int)*8 - __builtin_clz(v-u) - 1;
	int x = u, y = v-(1<<h)+1;
	x = tab[h][x], y = tab[h][y];
	return (d[x] < d[y]? x: y);
}

int dist(int u, int v){
	return d[u]+d[v]-2*d[lca(u, v)];
}

void dfssz(int now, int prv){
	sz[now] = 1;
	for(auto x: e[now])
		if(x-prv && not na[x]){
			dfssz(x, now), sz[now] += sz[x];
		}
	return;
}

void runCen(int);

int mib, center;

void choose(int now){
	if(cst.size())
		cfa[now] = cst.back(), ce[cst.back()].pb(now);
	else
		croot = now;
	cst.pb(now);
	na[now] = 1;
	for(auto x: e[now])
		if(not na[x])
			runCen(x);
	cst.pop_back();
}

void pickCen(int now, int prv, int tot = -1){
	int mx = 0, id = -1;
	if(tot == -1) tot = sz[now];
	for(auto x: e[now])
		if(not na[x] && x-prv){
			pickCen(x, now, tot);
			if(sz[x] > mx){
				mx = sz[x];
				id = x;
			}
		}
	
	mx = max(mx, tot-mx);
	if(mx < mib){
		mib = mx;
		center = now;
	}
	return;
}

void runCen(int root = 1){
	mib = INF;
	dfssz(root, root);
	pickCen(root, root);
	choose(center);
	return;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	
	for(int i = 1, u, v; i < n; i++)
		cin >> u >> v, e[u].pb(v), e[v].pb(u);
	runCen(); buildpar();
	
	for(int i = 1; i <= n; i++)
		for(int pos = i; pos; pos = cfa[pos]){
			ch[a[i]][pos]++;
			res[a[i]][pos] += dist(pos, i);
			if(pos != croot)
				cop[a[i]][pos] += dist(cfa[pos], i);
		}
	
	assert(ch[0][croot]+ch[1][croot] == n);
		
	for(int i = 0; i < m; i++){
		int op, x; cin >> op >> x;
		if(op == 1){
			for(int pos = x; pos; pos = cfa[pos]){
				ch[a[x]][pos]--, ch[a[x]^1][pos]++;
				res[a[x]][pos] -= dist(pos, x), res[a[x]^1][pos] += dist(pos, x);
				if(pos != croot)
					cop[a[x]][pos] -= dist(cfa[pos], x), cop[a[x]^1][pos] += dist(cfa[pos], x);
			}
			a[x] ^= 1;
		}
		else{
			int ret = 0;
			for(int pos = x, chi = -1; pos; pos = cfa[pos]){
				ret += res[a[x]][pos]+dist(pos, x)*ch[a[x]][pos];
				if(chi != -1){
					ret -= cop[a[x]][chi];
					ret -= dist(pos, x)*ch[a[x]][chi];
				}
				chi = pos;
			}
			cout << ret << endl;
		}
	}
	return 0;
}

