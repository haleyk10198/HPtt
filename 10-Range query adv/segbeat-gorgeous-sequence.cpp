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

int a[1000010], n, q;

struct Node{
	ll sum;
	int mx, count, tag;
	Node(){
	}
}T[4000010];

void maintain(int id){
	T[id].sum = T[id<<1].sum + T[id<<1|1].sum;
	T[id].mx = max(T[id<<1].mx, T[id<<1|1].mx);
	T[id].count = T[id<<1].count + T[id<<1|1].count;
	return;
}

void apply(int id, int l, int r, int t){
	if(T[id].tag != 0 && T[id].tag <= t) return;
	
	T[id].tag = t;
	
	if(T[id].count != r-l){
		T[id].mx = t;
		T[id].sum += 1LL*t*(r-l-T[id].count);
		T[id].count = r-l;
	}
	
	return;
}

void push(int id, int l, int r){
	if(T[id].tag != 0){
		apply(id<<1, l, l+r>>1, T[id].tag);
		apply(id<<1|1, l+r>>1, r, T[id].tag);
		T[id].tag = 0;
	}
	return;
}

void rmv(int id, int t, int l, int r){
	if(T[id].mx < t) return;	
	
	T[id].tag = 0;
	
	if(l+1 == r){
		T[id].sum = T[id].mx = 0;
		T[id].count = 0;
		return;
	}
	else{
		rmv(id<<1, t, l, l+r>>1);
		rmv(id<<1|1, t, l+r>>1, r);
		maintain(id);
	}
	return;
}

void build(int id = 1, int l = 0, int r = n){
	if(l+1 == r){
		scanf("%d", &T[id].mx);
		T[id].count = 1;
		T[id].sum = T[id].tag = T[id].mx;
		return;
	}
	T[id].tag = 0;
	build(id<<1, l, l+r>>1);
	build(id<<1|1, l+r>>1, r);
	maintain(id);
	return;
}

void upd(int x, int y, int t, int id = 1, int l = 0, int r = n){
	if(l >= y || x >= r) return;
	if(T[id].mx <= t) return;
	if(x <= l && r <= y){
		rmv(id, t, l, r);
		apply(id, l, r, t);
		return;
	}
	push(id, l, r);
	upd(x, y, t, id<<1, l, l+r>>1);
	upd(x, y, t, id<<1|1, l+r>>1, r);
	maintain(id);
	return;
}

int askmx(int x, int y, int id = 1, int l = 0, int r = n){
	if(l >= y || x >= r) return 0;
	if(x <= l && r <= y)
		return T[id].mx;
	else{
		push(id, l, r);
		int r1 = askmx(x, y, id<<1, l, l+r>>1), r2 = askmx(x, y, id<<1|1, l+r>>1, r);
		return max(r1, r2);
	}
}

ll asksum(int x, int y, int id = 1, int l = 0, int r = n){
	if(l >= y || x >= r) return 0;
	if(x <= l && r <= y)
		return T[id].sum;
	else{
		push(id, l, r);
		return asksum(x, y, id<<1, l, l+r>>1)+asksum(x, y, id<<1|1, l+r>>1, r);
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &q);
		build();
		int op, x, y, t;
		while(q--){
			scanf("%d", &op);
			if(op == 0){
				scanf("%d%d%d", &x, &y, &t);
				upd(--x, y, t);
			}
			else if(op == 1){
				scanf("%d%d", &x, &y);
				printf("%d\n", askmx(--x, y));
			}
			else if(op == 2){
				scanf("%d%d", &x, &y);
				printf("%lld\n", asksum(--x, y));
			}
		}
	}
	
	return 0;
}

