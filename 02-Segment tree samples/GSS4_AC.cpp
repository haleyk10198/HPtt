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

ll T[400010];
int n, q;

void build(int id = 1, int l = 0, int r = n){
	if(l+1 == r){
		cin >> T[id];
		return;
	}
	build(id<<1, l, l+r>>1);
	build(id<<1|1, l+r>>1, r);
	T[id] = T[id<<1]+T[id<<1|1];
	return;
}

void upd(int x, int y, int id = 1, int l = 0, int r = n){
	if(x >= r || l >= y) return;
	if(l+1 == r){
		T[id] = sqrtl(T[id]);
		return;
	}
	if(T[id] == r-l && x <= l && r <= y) return;
	upd(x, y, id<<1, l, l+r>>1);
	upd(x, y, id<<1|1, l+r>>1, r);
	T[id] = T[id<<1]+T[id<<1|1];
	return;
}

ll ask(int x, int y, int id = 1, int l = 0, int r = n){
	if(l >= y || x >= r) return 0;
	if(x <= l && r <= y) return T[id];
	return ask(x, y, id<<1, l, l+r>>1)+ask(x, y, id<<1|1, l+r>>1, r);
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	
	for(int no = 1; cin >> n; no++){
		build();
		cin >> q;
		cout << "Case #" << no << ":" << endl;
		for(int i = 0, op, l, r; i < q; i++){
			cin >> op >> l >> r;
			if(l > r) swap(l, r);
			if(op == 0)
				upd(--l, r);
			else
				cout << ask(--l, r) << endl;
		}
		cout << endl;
	}
	
	return 0;
}

