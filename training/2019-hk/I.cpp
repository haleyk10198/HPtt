#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15
#define MAXN 200010
#define MAXQ 1000010
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

int n, m, members[MAXN][3];
ll vals[MAXN], sz[MAXN];

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
} T[MAXN][3];
Node *L, *M, *R, *roots[MAXN];

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
    n->par = nullptr;
    split(T, n->val, L, R);
    merge(T, L, n);
    merge(T, T, R);
}

void createListener(int idx) {
    const int &sz = ::sz[idx];
    const ll &val = ::vals[idx];
    for(int j = 0; j < sz; j++) {
        T[idx][j].id = idx;
        T[idx][j].setAlarm((val+sz-1)/sz);
        insert(roots[members[idx][j]], T[idx] + j);
    }
}

void extractCandidates(const Node *T, vi &candidates) {
    if(!T) return;
    candidates.emplace_back(T->id);
    extractCandidates(T->l, candidates);
    extractCandidates(T->r, candidates);
}

void extractSelf(Node *T, const int grp) {
	if(!T) return;
    else if(T->par == nullptr) {
        merge(roots[grp], T->l, T->r);
    } else {
        merge(T->par->l == T? T->par->l: T->par->r, T->l, T->r);
    }
}

int main() {
#ifdef LOCAL
    freopen("I.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for(int i = 0, last = 0, op, cnt1 = 0; i < m; i++) {
        cin >> op;
        if(op == 1) {
            ++cnt1;
            cin >> vals[cnt1] >> sz[cnt1]; vals[cnt1] ^= last;

            for(int j = 0; j < sz[cnt1]; j++) {
                cin >> members[cnt1][j];
            }

            createListener(cnt1);
        } else {
            int x, y; cin >> x >> y;
            x ^= last; y ^= last;

            vi candidates, tp;
            
			if(roots[x]) {
	            ::apply(roots[x], -y);
	            split(roots[x], 1, L, R);
	            roots[x] = R;
	
	            extractCandidates(L, candidates);
	
	            for(const int &idx: candidates) {
	                ll dv = 0;
	                for(int j = 0; j < sz[idx]; j++) {
	                    extractSelf(T[idx] + j, members[idx][j]);
	                    dv += T[idx][j].endured;
	                }
	
	                if((vals[idx] += dv) <= 0) {
	                    tp.emplace_back(idx);
	                } else {
	                    for(int j = 0; j < sz[idx]; j++) {
	                        T[idx][j].setAlarm((vals[idx]+sz[idx]-1)/sz[idx]);
	                        insert(roots[members[idx][j]], T[idx] + j);
	                    }
	                }
            	}
				
			}

			// dude it's size_vector, the checker should accept "0 [empty vector]"
			if(tp.empty()) cout << 0 << endl;
            else cout << tp.size() << ' ' << tp << endl;
        }
    }

}
