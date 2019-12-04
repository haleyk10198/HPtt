#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15
#define MAXN 200010

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

class NodeTag {
public:
    int from, child, mx;
    ll sum;

    NodeTag(int from, int child, int mx, ll sum) : from(from), child(child), mx(mx), sum(sum) {}

    bool operator<(const NodeTag &rhs) const {
        return std::tie(mx, from) < std::tie(rhs.mx, rhs.from);
    }

    bool operator>(const NodeTag &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const NodeTag &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const NodeTag &rhs) const {
        return !(*this < rhs);
    }
};

int n;
ll a[MAXN];
vi e[MAXN];

int na[MAXN], sz[MAXN], cfa[MAXN], croot;
vi ce[MAXN];
vi cst;

vector<NodeTag> subTree[MAXN];

void runCen(int);

int mib, center;

int fFather[MAXN][20], fMax[MAXN][20];
ll fSum[MAXN][20];
int d[MAXN];

void reset() {
    for(int i = 1; i <= n; i++) {
        ce[i].clear();
        e[i].clear();
        subTree[i].clear();
        fill(fFather[i], fFather[i]+20, 0);
        fill(fSum[i], fSum[i]+20, 0);
    }
    cst.clear();
    fill(cfa+1, cfa+n+1, 0);
    fill(na+1, na+n+1, 0);
}

void dfssz(int now, int prv) {
    sz[now] = 1;
    for(auto x: e[now]) {
        if(x-prv && not na[x]) {
            dfssz(x, now);
            sz[now] += sz[x];
        }
    }
}

void choose(int now) {
    if(cst.size()) {
        cfa[now] = cst.back();
        ce[cst.back()].push_back(now);
    } else croot = now;

    cst.push_back(now);
    na[now] = 1;

    for(auto x: e[now]) {
        if(not na[x]) {
            runCen(x);
        }
    }

    cst.pop_back();
}

void pickCen(int now, int prv, int tot = -1) {
    int mx = 0, id = -1;
    if(tot == -1) tot = sz[now];

    for(auto x: e[now]) {
        if(not na[x] && x-prv) {
            pickCen(x, now, tot);
            if(sz[x] > mx) {
                mx = sz[x];
            }
        }
    }

    mx = max(mx, tot-sz[now]);
    if(mx < mib) {
        mib = mx;
        center = now;
    }

    return;
}

void runCen(int root = 1) {
    mib = INF;
    dfssz(root, root);
    pickCen(root, root);
    choose(center);
    return;
}

void dfsTab(int now, int prv) {
    fFather[now][0] = prv;
    fSum[now][0] = a[now];
    fMax[now][0] = a[now];

    for(auto x: e[now]) {
        if(x - prv) {
            d[x] = d[now]+1;
            dfsTab(x, now);
        }
    }
}

void buildTab() {
    for(int i = 1; i < 20; i++) {
        for(int j = 1; j <= n; j++) {
            fFather[i][j] = fFather[fFather[i][j-1]][j-1];
            fSum[i][j] = fSum[i][j-1]+fSum[fFather[i][j-1]][j-1];
            fMax[i][j] = max({fMax[i][j-1], fMax[fFather[i][j-1]][j-1]});
        }
    }

    return;
}

int LCA(int u, int v) {
    if(d[u] < d[v]) swap(u, v);

    for(int i = 19; i >= 0; i--) {
        if(d[fFather[u][i]] >= d[v]) {
            u = fFather[u][i];
        }
    }

    if(u == v) return u;

    for(int i = 19; i >= 0; i--) {
        if(fFather[u][i] != fFather[v][i]) {
            u = fFather[u][i];
            v = fFather[v][i];
        }
    }

    return fFather[u][0];
}

pair<ll, int> fWalk(int u, const int &steps) {
    ll sum = 0;
    int mx = 0;
    for(int i = 0; i < 20; i++) {
        if((1<<i)&steps) {
            sum += fSum[u][i];
            mx = max(mx, fMax[u][i]);
            u = fFather[u][i];
        }
    }

    return pair(sum, mx);
}

// sum, mx
pair<ll, int> fPoints(const int &u, const int &v) {
    int l = LCA(u, v);

    auto [sum1, mx1] = fWalk(u, d[u]-d[l]);
    auto [sum2, mx2] = fWalk(v, d[v]-d[l]+1);

    return pair(sum1+sum2, max({mx1, mx2}));
}

OT exc[MAXN];
OT sums;

void workSubtree(vector<NodeTag> &subtree, const int &node, ll &res) {
    sort(subtree.begin(), subtree.end());

    sums.clear();

    for(auto &tag: subtree) {
        auto& [from, child, mx, sum] = tag;

        // sum1 + (sum2 - a[node]) - mx > mx
        // sum2-a[node] > 2mx - sum1
        res += sums.size() - sums.order_of_key(pair(2*mx - sum, INF));
        res -= exc[child].size() - exc[child].order_of_key(pair(2*mx - sum, INF));

        sums.insert(pair(sum-a[node], from));
        exc[child].insert(pair(sum-a[node], from));
    }

    for(auto& [_, child, foo, bar]: subtree) {
        exc[child].clear();
    }

    return;
}

ll solve() {
    ll res = 0;
    for(int i = 1; i <= n; i++) {
        for(int pos = i; pos != croot; pos = cfa[pos]) {
            auto [sum, mx] = fPoints(i, cfa[pos]);
            subTree[cfa[pos]].emplace_back(i, pos, mx, sum);
        }
    }

    for(int i = 1; i <= n; i++) {
        workSubtree(subTree[i], i, res);
    }

    return res;
}

int main() {
#ifdef LOCAL
    freopen("C.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    d[0] = -1;

    while(T--) {
        reset();

        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        for(int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
        }

        runCen();
        dfsTab(1, 0);
        buildTab();
        cout << solve() << endl;
    }
}