/* Author haleyk10198 */
/* §@ªÌ:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

using namespace std;
#define ll long long

#define pb push_back

template<typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2> p){
    out << p.first << ' ' << p.second;
    return out;
}

template <typename T>
ostream& operator<<(ostream &out, vector<T> v){
    for(int i = 0; i < v.size(); i++)
        out << v[i] << (i+1 == v.size()? '\n': ' ');
    out.flush();
    return out;
}

#if __cplusplus < 201703L
#define mp make_pair
#endif

struct Node{
    Node *l, *r, *par;
    bool rev; int sz;
    Node(){
        l = r = par = NULL;
        rev = false; sz = 1;
    }
};

Node T[200010];

inline void maintain(Node* x){
    if(x){
        x->sz = 1;
        if(x->l)
            x->sz += x->l->sz;
        if(x->r)
            x->sz += x->r->sz;
    }
    return;
}

inline bool isroot(Node *x){
    if(not x->par) return true;
    return x->par->l != x && x->par->r != x;
}

inline void reverse(Node *x){
    if(x){
        x->rev ^= 1;
        swap(x->l, x->r);
    }
}

inline void push(Node* x){
    if(x){
        if(x->rev) reverse(x->l), reverse(x->r);
        x->rev = false;
    }
    return;
}

inline void getpushed(Node* x){
    if(not isroot(x)) getpushed(x->par);
    push(x);
}

inline void rotate(Node* x){
    Node *y = x->par;
    Node *z = y->par;

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

inline void splay(Node* x){
    getpushed(x);
    while(not isroot(x)){
        Node *y = x->par;
        if(not isroot(y)){
            Node *z = y->par;
            if((z->l == y)^(y->l == x)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    return;
}

inline Node* access(Node* x){
    Node *ret = NULL;
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

inline void makeroot(Node* x){
    access(x);
    splay(x);
    reverse(x);
    return;
}

inline void link(Node* x, Node* y){
    if(not x || not y) return;
    makeroot(x);
    x->par = y;
    return;
}

inline void cut(Node* x, Node* y){
    if(not x || not y) return;
    makeroot(x);
    access(y);
    splay(y);
    y->l = NULL;
    x->par = NULL;
    return;
}

inline bool connected(Node *x, Node *y){
    makeroot(x);
    makeroot(y);
    return not isroot(x);
}

int n, m, a[200010];

int main(){
#ifdef LOCAL
		freopen("../input.txt","r",stdin);
//		freopen("output.txt","w",stdout);
    freopen("debug.txt", "w", stderr);
#endif
//	ios_base::sync_with_stdio(false);

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", a+i);
        link(T+i, T+min(n, a[i]+i));
    }

    scanf("%d", &m);
    for(int i = 0, op, x; i < m; i++){
        scanf("%d%d", &op, &x);
        if(op == 1){
            makeroot(T+x);
            access(T+n);
            splay(T+n);
            printf("%d\n", T[n].sz-1);
        }
        else if(op == 2){
            cut(T+x, T+min(n, a[x]+x));
            scanf("%d", a+x);
            link(T+x, T+min(n, a[x]+x));
        }
        else
            assert(false);
    }

    return 0;
}

