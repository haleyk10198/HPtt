#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15
#define MAXN 810
#define MAXM 55010
#define MOD 1000000007

using ll = long long;
using pii = pair<ll, ll>;
using vi = vector<int>;
typedef tree<pii, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> OT;

class Line {
public:
    ll x, y, c;

    Line(ll x, ll y, ll c) {
        ll g = gcd(gcd(x, y), c);
        this->x = x/g;
        this->y = y/g;
        this->c = c/g;
    }

    friend ostream &operator<<(ostream &os, const Line &line) {
        os << line.x << " " << line.y << " " << line.c;
        return os;
    }

    bool operator<(const Line &rhs) const {
        return std::tie(x, y, c) < std::tie(rhs.x, rhs.y, rhs.c);
    }

    bool operator>(const Line &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Line &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Line &rhs) const {
        return !(*this < rhs);
    }
};

template<typename T>
ostream& operator<<(ostream &os, const vector<T> vt) {
    for(int i = 0; i < vt.size(); i++) os << vt[i] << (i+1 == vt.size()? "": " ");

    return os;
}

static unsigned long x = 123456789, y = 362436069, z = 521288629;
unsigned long gen(void) {
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t^x^y;

    return z;
}

struct Node {
    int id;
    ll val, dv, mi, endured;
    unsigned long pr;
    Node *l, *r, *par;

    void setAlarm(int val) {
        this->val = val;
        endured = 0;
        dv = 0;
        mi = val;
    }

    Node(): l(nullptr), r(nullptr), par(nullptr){

    }

    Node(const int idx, const int val): id(idx), val(val), dv(0), mi(val), pr(gen()), l(nullptr), r(nullptr), par(nullptr) {

    }
};

inline void apply(Node* &T, ll d) {
    if(!T) return;
    T->dv += d;
    T->val += d;
    T->mi += d;
    T->endured += d;

    return;
}

void push(Node *T) {
    if(!T) return;
    apply(T->l, T->dv);
    apply(T->r, T->dv);
    T->dv = 0;
}

inline void maintain(Node* &T) {
    if(!T) return;
    if(T->l) T->mi = T->l->mi;
    else T->mi = T->val;
}

void merge(Node* &T, Node *L, Node *R) {
    if(!L) {
        T = R;
    } else if(!R) {
        T = L;
    } else if(L->pr > R->pr) {
        push(L);
        L->par = nullptr;
        merge(L->r, L->r, R);
        if(L->r) L->r->par = L;
        T = L;
    } else {
        push(R);
        R->par = nullptr;
        merge(R->l, L, R->l);
        if(R->l) R->l->par = R;
        T = R;
    }

    maintain(T);
    return;
}

void split(Node *T, const int &val, Node* &L, Node* &R) {
    if(!T) {
        L = R = nullptr;
        return;
    }
    push(T);
    if(T->val >= val) {
        R = T;
        R->par = nullptr;
        split(T->l, val, L, T->l);
        if(R->l) R->l->par = R;
    } else {
        L = T;
        L->par = nullptr;
        split(T->r, val, T->r, R);
        if(L->r) L->r->par = L;
    }

    maintain(L);
    maintain(R);
    return;
}

void insert(Node* &T, Node *n) {
    Node *L, *R;
    split(T, n->val, L, R);
    merge(T, L, n);
    merge(T, T, R);
}

using flow_t = int;
using cost_t = ll;

const int DIRECTED = 0, UNDIRECTED = 1;
const flow_t FLOW_INFTY = 0x3fffffff;
const cost_t COST_INFTY = 1e15;
int N, S, T, now, K;
bool inQ[MAXN];

struct Edge {
    flow_t remain;
    cost_t cost;
    int endVertexId, nextEdgeId;
} e[MAXM << 1];

struct Vertex {
    int firstEdgeId, firstUnsaturedEdgeId;
    cost_t level;
} v[MAXN];

void _addEdge(int begin, int end, flow_t c, cost_t w) {
    e[now].remain = c;
    e[now].cost = w;
    e[now].endVertexId = end;
    e[now].nextEdgeId = v[begin].firstEdgeId;
    v[begin].firstEdgeId = now++;
}

void addEdge(int begin, int end, flow_t c, int edgeType, cost_t w = 1) {
    _addEdge(begin, end, c, w);
    _addEdge(end, begin, edgeType*c, -w);
}

void init() {
    now = 0;
    for(int i = 0; i < N; i++) v[i].firstEdgeId = -1, inQ[i] = false;
}

bool markLevel() {
    for(int i = 0; i < N; i++) v[i].level = COST_INFTY, v[i].firstUnsaturedEdgeId = v[i].firstEdgeId, inQ[i] = false;
    v[S].level = 0;
    queue<int> Q;
    Q.push(S);
    inQ[S] = true;
    while(!Q.empty()) {
        int x = Q.front();
        Q.pop();
        inQ[x] = false;
        for(int i = v[x].firstEdgeId; i >= 0; i = e[i].nextEdgeId) {
            if(e[i].remain && v[e[i].endVertexId].level > v[x].level+e[i].cost) {
                v[e[i].endVertexId].level = v[x].level + e[i].cost;
                if(!inQ[e[i].endVertexId]) Q.push(e[i].endVertexId), inQ[e[i].endVertexId] = true;
            }
        }
    }

    return v[T].level < COST_INFTY;
}

flow_t extendFlow(int x, flow_t flow) {
    if(x == T) return flow;
    inQ[x] = true;
    flow_t t, total = 0;
    for(int &i = v[x].firstUnsaturedEdgeId; i >= 0; i=e[i].nextEdgeId) {
        if(v[e[i].endVertexId].level == v[x].level+e[i].cost && e[i].remain && !inQ[e[i].endVertexId]) {
            if(t = extendFlow(e[i].endVertexId, min(flow, e[i].remain)))
                e[i].remain -= t, e[i^1].remain += t, flow -= t, total += t;
            if(0 == flow) break;
        }
    }

    inQ[x] = false;
    return total;
}

flow_t Dinic() {
    flow_t flow, total = 0;
    cost_t cost = 0;
    while(markLevel())
        while(flow = extendFlow(S, FLOW_INFTY))
            total += flow, cost += flow*v[T].level;
    return cost;
}

void buildGraph() {
    int n, m; cin >> n >> m;
    N = n+3; S = 0; T = N-1;

    init();

    for(int i = 1, di; i < n; i++) {
        cin >> di;
        addEdge(i, i+1, INF, DIRECTED, di);
        addEdge(i+1, i, INF, DIRECTED, di);
    }

    for(int i = 0, pos, baseCost; i < m; i++) {
        cin >> pos >> baseCost;
        addEdge(S, pos, 1, DIRECTED, baseCost);
    }

    for(int i = 0, pos, baseCost; i < m; i++) {
        cin >> pos >> baseCost;
        addEdge(pos, T-1, 1, DIRECTED, baseCost);
    }

    int edgeIdx = now;
    addEdge(T-1, T, 1, DIRECTED, 0);

    ll res = 0;
    for(int i = 1; i <= m; i++) {
        res += Dinic();
        cout << res << endl;
        e[edgeIdx].remain++;
//        addEdge(T-1, T, 1, DIRECTED, 0);
    }

    return;
}

int main() {
#ifdef LOCAL
    freopen("K.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    buildGraph();

}