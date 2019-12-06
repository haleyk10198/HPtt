#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15
#define MAXN 500010
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

// dp[len][eq][sumi][x-fx]
int dp[2][2][65][65], n, m;

ll solve(string str) {
    ll ret = 0;
    memset(dp, 0, sizeof(dp));

    dp[0][1][0][0] = 1;

    for(int len = 1, i = 1; len <= str.length(); len++, i^=1) {
        memset(dp[i], 0, sizeof(dp[i]));
        // lt
        for(int sum = 0; sum < m; sum++) {
            for(int diff = 0; diff < m; diff++) {
                for(int dig = 0, toSum = sum, toDiff = diff, dDiff = (m+1-sum)%m; dig < 10; dig++, (++toSum) %= m, (toDiff += dDiff) %= m) {
                    (dp[i][0][toSum][toDiff] += dp[i^1][0][sum][diff]) %= MOD;
                }
            }
        }

        // eq
        for(int sum = 0; sum < m; sum++) {
            for(int diff = 0; diff < m; diff++) {
                for(int dig = '0', toSum = sum, toDiff = diff, dDiff = (m+1-sum)%m; dig <= str[len-1]; dig++, (++toSum) %= m, (toDiff += dDiff) %= m) {
                    (dp[i][dig == str[len-1]][toSum][toDiff] += dp[i^1][1][sum][diff]) %= MOD;
                }
            }
        }
    }

    for(int x = 0; x < m; x++) {
        (ret += dp[str.length()%2][1][x][0]) %= MOD;
        (ret += dp[str.length()%2][0][x][0]) %= MOD;
    }

    return ret;
}

string L, R;

void minus(string &str) {
    str.back()--;
    for(int i = str.length()-1; str[i] < '0'; i--) {
        str[i] += 10;
        str[i-1] --;
    }
}

int main() {
#ifdef LOCAL
    freopen("J.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    int Tc; cin >> Tc;
    while(Tc--) {
        ll res = 0;
        cin >> L >> R >> m;
        ::minus(L);
        res = solve(R)-solve(L);
        if(res < 0) res += MOD;
        res %= MOD;

        cout << res << endl;
    }
}