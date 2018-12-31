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

using namespace std;

pii qs[100010];
int a[100010], prv[100010], ord[100010], qrd[100010], res[100010], n, q;
map<int, int> m1;

struct Node{
	ll nowsum, mxsum, nowd, mxd;
	Node(){
		nowd = nowsum = nowd = mxd = 0;
	}
}T[400010];

void apply(int id, int v){
	T[id].nowsum += v;
	T[id].nowd += v;
	T[id].mxd = max(T[id].mxd, T[id].nowd);
	T[id].mxsum = max(T[id].nowsum, T[id].mxsum);
}

void push(int id){
	T[id<<1].mxsum = max(T[id<<1].mxsum, T[id<<1].nowsum+T[id].mxd);
	T[id<<1|1].mxsum = max(T[id<<1|1].mxsum, T[id<<1|1].nowsum+T[id].mxd);
	T[id<<1].mxd = max(T[id<<1].mxd, T[id<<1].nowd + T[id].mxd);
	T[id<<1|1].mxd = max(T[id<<1|1].mxd, T[id<<1|1].nowd + T[id].mxd);
	apply(id<<1, T[id].nowd);
	apply(id<<1|1, T[id].nowd);
	T[id].nowd = T[id].mxd = 0;
	return;
}

void upd(int x, int y, int v, int id = 1, int l = 0, int r = n){
	if(x >= r || l >= y) return;
	if(x <= l && r <= y){
		apply(id, v);
		return;
	}
	push(id);
	upd(x, y, v, id<<1, l, l+r>>1);
	upd(x, y, v, id<<1|1, l+r>>1, r);
	T[id].mxsum = max(T[id<<1].mxsum, T[id<<1|1].mxsum);
	T[id].nowsum = max(T[id<<1].nowsum, T[id<<1|1].nowsum);
	return;
}

ll ask(int x, int y, int id = 1, int l = 0, int r = n){
	if(x >= r || l >= y) return -LINF;
	if(x <= l && r <= y) return T[id].mxsum;
	push(id);
	ll r1 = ask(x, y, id<<1, l, l+r>>1);
	ll r2 = ask(x, y, id<<1|1, l+r>>1, r);
	return max(r1, r2);
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		if(not m1.count(a[i]))
			prv[i] = -1;
		else
			prv[i] = m1[a[i]];
		m1[a[i]] = i;
	}
	
	cin >> q;
	for(int i = 0; i < q; i++){
		cin >> qs[i].first >> qs[i].second;
		--qs[i].first, qs[i].second;
	}	
	
	iota(qrd, qrd+q, 0);
	sort(qrd, qrd+q, [](int x, int y){
		if(qs[x].second != qs[y].second)
			return qs[x].second < qs[y].second;
		return x < y;
	});
	
	for(int i = 0, j = 0; j < q; j++){
		while(i < n && i < qs[qrd[j]].second){
			upd(prv[i]+1, i+1, a[i]);
			i++;
		}
		res[qrd[j]] = ask(qs[qrd[j]].first, qs[qrd[j]].second);		
	}
	
	for(int i = 0; i < q; i++)
		cout << res[i] << endl;
	
	return 0;
}

