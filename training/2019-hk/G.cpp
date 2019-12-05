#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15
#define MAXN 100010
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

int k, n, par[MAXN], a[MAXN], dp[MAXN];

int main() {
#ifdef LOCAL
    freopen("G.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    cin >> k;
    if(k == 1) {
        cout << 2 << endl
             << 1 << endl
             << "1 2" << endl;

        return 0;
    }

    fill(a, a+MAXN, 1);
    int mainBranch = 1;
    n = 1;

    while(k > 1) {
        if(k%2) {
            par[n+1] = mainBranch;
            mainBranch = n+1;

            n += 1;

            k--;
        } else {
            par[n+1] = mainBranch;
            par[n+2] = n+1;
            par[n+3] = mainBranch;
            a[mainBranch] = 1e9;

            mainBranch = n+3;
            n += 3;

            k >>= 1;
        }
    }

    for(int pos = mainBranch, sum = 1; pos; pos = par[pos]) {
        if(a[pos] == 1e9) {
            sum++;
        } else {
            a[pos] = sum;
        }
    }

    cout << n << endl;
    for(int i = 2; i <= n; i++) cout << par[i] << (i == n? '\n': ' ');
    for(int i = 1; i <= n; i++) cout << a[i] << (i == n? '\n': ' ');

}