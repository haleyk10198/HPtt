/* Author haleyk10198 */
/* ?@??:  haleyk10198 */
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

struct node{
    node *l, *r, *par;
    bool rev; int val, lsum, rsum, sz, sum, best, lazy;
    node(){
        l = r = par = NULL;
        rev = false;
        val = lsum = rsum = sum = best = 0;
        sz = 1;
        lazy = INF;
    }
};
 
node T[100010];

inline void reverse(node *x){
	//..... too naive
	if(x){
		x->rev ^= 1;
		swap(x->lsum, x->rsum);
		swap(x->l, x->r);
	}
	return;
}

inline void apply(node *x, int v){
	if(x){
		x->val = v;
		x->lazy = v;
		x->lsum = x->rsum = x->best = max(0, x->val*x->sz);
		x->sum = x->val*x->sz;
	}
	return;
}

inline void push(node* x){
    if(x){
    	if(x->rev)
    		reverse(x->l), reverse(x->r);
    	if(x->lazy != INF)
    		apply(x->l, x->lazy), apply(x->r, x->lazy);
    	x->rev = false;
    	x->lazy = INF;
	}
    return;
}
 
void maintain(node* x){
    if(x){
    	x->sum = x->val;
    	x->best = x->lsum = x->rsum = max(x->val, 0);
    	x->sz = 1;
    	if(x->l){
			x->best = max(max(x->l->best, x->best), x->l->rsum+x->lsum);
			x->lsum = max(x->l->lsum, x->l->sum+x->lsum);
			x->rsum = max(x->rsum, x->sum+x->l->rsum);
    		x->sz += x->l->sz;
    		x->sum += x->l->sum;
		}
    	if(x->r){
			x->best = max(max(x->best, x->r->best), x->rsum+x->r->lsum);
			x->lsum = max(x->lsum, x->sum+x->r->lsum);
			x->rsum = max(x->r->rsum, x->r->sum+x->rsum);
    		x->sz += x->r->sz;
    		x->sum += x->r->sum;
		}
    }
    return;
}
 
inline bool isroot(node *x){
    if(not x->par) return true;
    return x->par->l != x && x->par->r != x;
}

inline void getpushed(node* x){
    if(not isroot(x)) getpushed(x->par);
    push(x);
} 

void rotate(node* x){
    node *y = x->par;
    node *z = y->par;
     
    if(not isroot(y)){
        if(z->l == y) z->l = x;
        if(z->r == y) z->r = x;
    }
    x->par = z;
     
    if(y->r == x){
        if(y->r = x->l) y->r->par = y;
        y->par = x;
        x->l = y;
    }
    else{
        if(y->l = x->r) y->l->par = y;
        y->par = x;
        x->r = y;
    }
     
    maintain(y), maintain(x);
    //ORDER IS IMPORTANT, ALWAYS UPDATE LOWER NODES FIRST
    return;
}
 
inline void splay(node* x){
    getpushed(x);
    while(not isroot(x)){
        node *y = x->par;
        if(not isroot(y)){
            node *z = y->par;
            if((z->l == y)^(y->l == x)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    return;
}
 
inline node* access(node* x){
    node *ret = NULL;
    while(x){
        splay(x);
        x->r = ret;
        maintain(x);
        ret = x;
        x = x->par;
    }
    //while(ret && ret->l) ret = ret->l; //depends if intended to return root
    return ret;
}
 
inline void makeroot(node* x){
    access(x);
    splay(x);
    reverse(x);
    return;
}
 
inline void link(node* x, node* y){
    makeroot(x);
    x->par = y;
    return;
}
 
inline void cut(node* x, node* y){
    makeroot(x);
    access(y);
    splay(y);
    y->l = NULL;
    x->par = NULL;
    return;
}

inline bool connected(node *x, node *y){
	makeroot(x);
	makeroot(y);
	return not isroot(x);
}

int n, m;

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	//ios_base::sync_with_stdio(false);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &T[i].val);
	
	for(int i = 1, u, v; i < n; i++){
		scanf("%d%d", &u, &v);
		link(T+u, T+v);
	}
	
	scanf("%d", &m);
	for(int i = 1, op, a, b, k; i <= m; i++){
		scanf("%d%d%d", &op, &a, &b);
		if(op == 1){
			makeroot(T+a);
			access(T+b);
			splay(T+b);
			printf("%d\n", T[b].best);
		}
		else if(op == 2){
			scanf("%d", &k);
			makeroot(T+a);
			access(T+b);
			splay(T+b);
			apply(T+b, k);
		}
	}
	return 0;
}
