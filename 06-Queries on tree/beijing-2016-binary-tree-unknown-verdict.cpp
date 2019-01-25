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

struct Node{
    Node *l, *r, *par;
    bool rev;

    int subw, subw_pathsum;
    int fw, fw_range_update; // f[i]-w[i]
    int sz, sz_range_update;
    int real;

    Node(){
        l = r = par = NULL;
        rev = false;
    }
    void reset(){
        subw = subw_pathsum = fw = fw_range_update = sz = sz_range_update = real = 0;
        l = r = par = nullptr;
        rev = false;
    }
};

int w[MAXN], l[MAXN], r[MAXN], par[MAXN];
Node T[2][MAXN];

inline void maintain(Node* x){
    if(x){
        x->subw_pathsum = x->subw;
        if(x->l) x->subw_pathsum += x->l->subw_pathsum;
        if(x->r) x->subw_pathsum += x->r->subw_pathsum;
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

inline void add_sz(Node *x, int sz){
    if(x){
        x->sz += sz;
        x->sz_range_update += sz;
    }
}

inline void add_value(Node *x, int fw){
    if(x){
        x->fw += fw;
        x->fw_range_update += fw;
    }
}

inline void push(Node* x){
    if(x){
        if(x->rev){
            reverse(x->l);
            reverse(x->r);
            x->rev = false;
        }

        add_sz(x->l, x->sz_range_update);
        add_sz(x->r, x->sz_range_update);
        x->sz_range_update = 0;

        add_value(x->l, x->fw_range_update);
        add_value(x->r, x->fw_range_update);
        x->fw_range_update = 0;
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

    maintain(y), maintain(x), maintain(z);
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
    makeroot(x);
    x->par = y;
    return;
}

inline void cut(Node* x, Node* y){
    makeroot(x);
    access(y);
    splay(y);
    y->l = NULL;
    x->par = NULL;
    return;
}

bool check_child(int fa, int ch){
    /*
     * if fa is an ancestor of ch,
     * then it lies on the path between root -> ch
     *
     * Hence, it should lie on the topmost splay after access(ch)
     * */
    makeroot(T[0]+1);
    access(T[0]+ch);
    splay(T[0]+fa);
    return T[0][fa].par == nullptr;
}

inline int get_value(int u){
    /*
     * access the path from root to T[u]
     * take summation along the path(rval) for subtree updates
     * take the weight(val) applied on it for effects of other updates
     * */

    int sgn = T[1][u].real;

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
        access(T[i]+u);
        splay(T[i]+u);
    }

    return T[sgn][u].sz*T[0][u].subw_pathsum + T[sgn][u].fw;
}

inline int get_subw(int u){
    makeroot(T[0]+1);
    access(T[0]+u);
    splay(T[0]+u);

    return T[0][u].subw_pathsum;
}

inline void cut_par(int u){
    // cut each tree and prepare for update
    int subw = get_subw(u);
    int fw = get_value(u);
    int sgn = T[1][u].real;
    int sgnfa = T[1][par[u]].real;

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
        access(T[i]+u);
        splay(T[i]+u);
    }

    int sz = T[sgn][u].sz;

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
    }

    for(int i = 0; i < 2; i++){
        cut(T[i]+u, T[i^(r[par[u]]==u)]+par[u]);
    }

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
        access(T[i]+par[u]);
        splay(T[i]+par[u]);
    }

    // update ancestors
    add_sz(T[sgn^(r[par[u]]==u)]+par[u], -sz);
    add_sz(T[sgn^1^(r[par[u]]==u)]+par[u], sz);
    add_value(T[sgn^(r[par[u]]==u)]+par[u], -fw);
    add_value(T[sgn^1^(r[par[u]]==u)]+par[u], fw);

    // update subw
    T[0][u].subw = T[0][u].subw_pathsum = subw;

    // cut the child records
    if(l[par[u]] == u) l[par[u]] = 0;
    else r[par[u]] = 0;
}

inline void add_value(int id, int v){
    /*
     * access the path from root to T[id]
     * splay it to the root
     * apply the add value function
     * */

    int sgn = T[1][id].real;

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
        access(T[i]+id);
        splay(T[i]+id);
    }

    add_value(T[sgn]+id, v);
    add_value(T[sgn^1]+id, -v);
    return;
}

inline void add_subtree_value(int id, int v){
    /*
     * Similar to add_value
     * */

    int sgn = T[1][id].real;

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
        access(T[i]+id);
        splay(T[i]+id);
    }

    int dv = v*T[sgn][id].sz;
    T[0][id].subw += v;
    T[0][id].subw_pathsum += v;

    id = par[id];
    if(not id) return;

    add_value(T[sgn]+id, dv);
    add_value(T[sgn^1]+id, -dv);

    return;
}

inline void make_child(int ch, int fa, int sgn){

    int sgnch = T[1][ch].real;
    int sgnfa = T[1][fa].real;

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
        access(T[i]+fa);
        splay(T[i]+fa);
        makeroot(T[i]+ch);
    }

    int fw = T[sgnch][ch].fw + T[sgnch][ch].subw_pathsum*T[sgn][ch].sz;
    int dw = T[0][ch].subw-T[0][fa].subw_pathsum;

    add_value(T[sgnfa^sgn]+fa, fw);
    add_value(T[sgnfa^sgn^1]+fa, -fw);
    add_sz(T[sgnfa^sgn]+fa, T[sgnch][ch].sz);
    add_sz(T[sgnfa^sgn]+fa, -T[sgnch][ch].sz);

    T[0][ch].subw = dw;
    T[0][ch].subw_pathsum = dw;

    link(T[sgnch]+ch, T[sgnfa^sgn]+fa);
    link(T[sgnch^1]+ch, T[sgnfa^sgn^1]+fa);

    for(int i = 0; i < 2; i++){
        makeroot(T[i]+1);
    }

    if(sgn) r[fa] = ch;
    else l[fa] = ch;
    par[ch] = fa;

    return;
}

int main() {
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
//    ios_base::sync_with_stdio(false);

    int n, m;
    while(~scanf("%d", &n)){
        for(int i = 1; i <= n; i++){
            scanf("%d", w+i);
        }

        for(int i = 1; i <= n; i++){
            scanf("%d%d", l+i, r+i);
        }

        scanf("%d", &m);

        for(int i = 1; i <= n; i++){
            T[0][i].reset();
            T[1][i].reset();
            T[0][i].real = 1;
        }

        for(int i = 1; i <= n; i++){
            if(l[i]){
                make_child(l[i], i, 0);
            }
            if(r[i]){
                make_child(r[i], i, 1);
            }
        }

        for(int i = 1; i <= n; i++){
            add_value(i, w[i]);
        }

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
                make_child(u, v, 0);
            } else if (op == 2) {
                scanf("%d%d", &u, &v);
                if (r[v] || check_child(u, v)) {
                    printf("F\n");
                    continue;
                }
                printf("S\n");
                cut_par(u);
                make_child(u, v, 1);
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
                make_child(rch, v, 0);
                make_child(lch, v, 1);

            } else if (op == 4) {
                scanf("%d%d", &u, &v);
                int ww = get_value(u);
                add_value(u, v - ww);
                printf("S\n");
            } else if (op == 5) {
                scanf("%d%d", &u, &v);
                add_subtree_value(u, v);
                printf("S\n");
            } else if (op == 6) {
                scanf("%d", &u);
                printf("%d\n", get_value(u));
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

