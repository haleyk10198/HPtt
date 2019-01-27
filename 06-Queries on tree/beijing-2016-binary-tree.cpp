/* Author haleyk10198 */
/* §@ªÌ:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

#define pb push_back

constexpr auto MOD = 1000000007LL;
constexpr auto LINF = (1LL << 60);
constexpr auto INF = 2147483647LL;
constexpr auto PI = 3.1415926535897932384626433;
constexpr auto EPS = 1E-9;

template<typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> p) {
    out << p.first << ' ' << p.second;
    return out;
}

template<typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p) {
    in >> p.first >> p.second;
    return in;
}

template<typename T>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v)
        in >> x;
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, vector<T> v) {
    for (int i = 0; i < v.size(); i++)
        out << v[i] << (i + 1 == v.size() ? '\n' : ' ');
    out.flush();
    return out;
}

#if __cplusplus < 201703L
#define mp make_pair
#endif

#define MAXN 40010

class ETNode{
    public:
        ETNode *l, *r, *par;
        ll w, dw, f;
        int sz, real;
        bool rev;
        void apply_flip(){
            swap(l, r);
            rev ^= 1;
        }
        ETNode(){
            l = r = par = NULL;
            rev = false;
            w = dw = f = 0;
        }
        void reset(){
            l = r = par = NULL;
            rev = false;
            w = dw = f = 0;
        }
        void maintain(){
            f = w*real;
            sz = real;
            if(l) f += l->f, sz += l->sz;
            if(r) f += r->f, sz += r->sz;
        }
        void push(){
            if(l){
                if(rev) l->apply_flip();
                l->apply(dw);
            }
            if(r){
                if(rev) r->apply_flip();
                r->apply(dw);
            }
            dw = 0;
            rev = 0;
        }
        void apply(int d){
            w += d;
            dw += d;
            f += d*sz;
        }

};

int w[MAXN], l[MAXN], r[MAXN], par[MAXN];
ETNode ET[2][2][MAXN]; // ET[+VE/-VE][IN/OUT][ID]

inline void maintain(ETNode *x){
    if(x){
        x->maintain();
    }
    return;
}

inline bool isroot(ETNode *x){
    if(not x->par) return true;
    return x->par->l != x && x->par->r != x;
}

inline void push(ETNode* x){
    if(x){
        x->push();
    }
    return;
}

inline void getpushed(ETNode* x){
    if(not isroot(x)) getpushed(x->par);
    push(x);
}

inline void rotate(ETNode* x){
    ETNode *y = x->par;
    ETNode *z = y->par;

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

    maintain(y), maintain(x), maintain(z);
    //ORDER IS IMPORTANT, ALWAYS UPDATE LOWER NODES FIRST
    return;
}

inline void reverse(ETNode *x){
    if(x){
        x->apply_flip();
    }
}

inline void splay(ETNode* x){
    getpushed(x);
    while(not isroot(x)){
        ETNode *y = x->par;
        if(not isroot(y)){
            ETNode *z = y->par;
            if((z->l == y)^(y->l == x)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    return;
}

inline ETNode* access(ETNode* x){
    ETNode *ret = NULL;
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

inline void makeroot(ETNode* x){
    access(x);
    splay(x);
    reverse(x);
    return;
}

inline void link(ETNode* x, ETNode* y){
    makeroot(x);
    x->par = y;
    return;
}

inline void cut(ETNode* x, ETNode* y){
    makeroot(x);
    access(y);
    splay(y);
    y->l = NULL;
    x->par = NULL;
    maintain(y);
    return;
}

void makerootET(int id){
    makeroot(ET[0][0]+id);
    makeroot(ET[1][0]+id);
}

void accessET(int id){
    access(ET[0][0]+id);
    access(ET[1][0]+id);
}

void splayET(int id){
    splay(ET[0][0]+id);
    splay(ET[1][0]+id);
}

bool check_child(int fa, int ch){
    /*
     * if fa is an ancestor of ch,
     * then it lies on the path between root -> ch
     *
     * Hence, it should lie on the topmost splay after access(ch)
     * */
    makerootET(1);
    accessET(ch);
    splayET(fa);

    if(ET[0][0][fa].par) return false;
    splay(ET[0][1]+fa);
    return ET[0][1][fa].par;
}

void cut_par(int u){
    for(int real = 0; real < 2; real++){
        ETNode *st, *ed;
        st = ET[real][0]+par[u];
        ed = ET[real][1]+par[u];
        if(l[par[u]] == u){
            if(r[par[u]]){
                ed = ET[real^1][0]+r[par[u]];
            }
        }
        if(r[par[u]] == u){
            if(l[par[u]]){
                st = ET[real][1]+l[par[u]];
            }
        }
        cut(st, ET[real^(r[par[u]]==u)][0]+u);
        cut(ed, ET[real^(r[par[u]]==u)][1]+u);
        link(st, ed);
    }

    if(l[par[u]] == u) l[par[u]] = 0;
    else r[par[u]] = 0;
    par[u] = 0;
}

void make_child(int fa, int ch, int sgn)
// sgn: 0/1, l/r
{
    ETNode *st, *ed;

    for(int i = 0; i < 2; i++) {
        st = ET[i][0] + fa;
        ed = ET[i][1] + fa;
        if(sgn == 0){
            if (r[fa]) ed = ET[i ^ 1][0] + r[fa];
        }
        if(sgn == 1){
            if(l[fa]) st = ET[i][1] + l[fa];
        }

        cut(st, ed);
        link(st, ET[i^sgn][0]+ch);
        link(ET[i^sgn][1]+ch, ed);
    }

    if(sgn) r[fa] = ch;
    else l[fa] = ch;
    par[ch] = fa;
}

void set_value(int id, int w){
    accessET(id);
    splayET(id);
    ET[0][0][id].w = w;
    ET[1][0][id].w = w;

    maintain(ET[0][0]+id);
    maintain(ET[1][0]+id);
}

void add_subtree_value(int id, int w){
    makerootET(id);
    access(ET[0][1]+id);
    access(ET[1][1]+id);
    splay(ET[0][1]+id);
    splay(ET[1][1]+id);
    ET[0][1][id].apply(w);
    ET[1][1][id].apply(w);
}

ll get_value(int id){
    makerootET(id);
    access(ET[0][1]+id);
    splay(ET[0][1]+id);
    return ET[0][1][id].f;
}

int main() {
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
//    freopen("../output.txt","w",stdout);
//    freopen("../debug.txt", "w", stderr);
#endif
//    ios_base::sync_with_stdio(false);

    int n, m;
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; i++){
            scanf("%d", w+i);
        }

        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(par, 0, sizeof(par));

        for(int i = 1; i <= n; i++){
            ET[0][0][i].reset();
            ET[0][0][i].real = 1;
            ET[0][1][i].reset();
            ET[0][1][i].real = 0;
            ET[1][0][i].reset();
            ET[1][0][i].real = -1;
            ET[1][1][i].reset();
            ET[1][1][i].real = 0;
            ET[0][0][i].w = ET[0][0][i].f = w[i];
            ET[1][0][i].w = ET[1][0][i].f = w[i];
            ET[0][0][i].maintain();
            ET[0][1][i].maintain();
            ET[1][0][i].maintain();
            ET[1][1][i].maintain();
            link(ET[0][0]+i, ET[0][1]+i);
            link(ET[1][0]+i, ET[1][1]+i);
        }

        for(int i = 1, x, y; i <= n; i++){
            scanf("%d%d", &x, &y);
            if(x) make_child(i, x, 0);
            if(y) make_child(i, y, 1);
        }

        scanf("%d", &m);

        for(int i = 1, op, u, v; i <= m; i++) {
            scanf("%d", &op);
            if (op == 1) {
                scanf("%d%d", &u, &v);
                if (l[v] || check_child(u, v)) {
                    printf("F\n");
                    continue;
                }
                printf("S\n");
                cut_par(u);
                make_child(v, u, 0);
            } else if (op == 2) {
                scanf("%d%d", &u, &v);
                if (r[v] || check_child(u, v)) {
                    printf("F\n");
                    continue;
                }
                printf("S\n");
                cut_par(u);
                make_child(v, u, 1);
            } else if (op == 3) {
                scanf("%d", &v);
                if (not l[v] || not r[v]) {
                    printf("F\n");
                    continue;
                }
                printf("S\n");

                int lch = l[v], rch = r[v];
                cut_par(lch);
                cut_par(rch);
                make_child(v, rch, 0);
                make_child(v, lch, 1);

            } else if (op == 4) {
                scanf("%d%d", &u, &v);
                set_value(u, v);
                printf("S\n");
            } else if (op == 5) {
                scanf("%d%d", &u, &v);
                add_subtree_value(u, v);
                printf("S\n");
            } else if (op == 6) {
                scanf("%d", &u);
                printf("%lld\n", get_value(u));
            }

//#ifdef LOCAL
//            for(int i = 1; i <= n; i++){
//                printf("%d%c", get_value(i), i == n? '\n': ' ');
//             }
//#endif
        }
    }

    return 0;
}

