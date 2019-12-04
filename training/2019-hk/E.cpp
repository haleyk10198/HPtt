#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15
#define MAXN 5010

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

int n, a[MAXN], masked[MAXN];

bool canForce(int l, int r, int x) {
    vector<pii> st;
    for(int i = l; i < r; i++) {
        if(st.empty() || st.back().second != a[l]) {
            st.emplace_back(1, a[i]);
        } else {
            st.back().first++;
            if(st.back().second != x && st.back().first == 3) {
                st.back().first = 1;
            }
        }
    }

    int sumX = accumulate(st.begin(), st.end(), 0, [&x](const int acc, const pii pp) {
        return acc+pp.second*(pp.first == x);
    });
    int sumY = accumulate(st.begin(), st.end(), 0, [&x](const int acc, const pii pp) {
        return acc+pp.second*(pp.first != x);
    });

    return sumX > sumY;
}

bool check(int idx) {
    for(int i = 1; i <= n; i++) {
        if(i == idx) continue;
        masked[i] = (a[i] > a[idx]);
    }

    if(idx > 1 && idx < n) {
        if(canForce(0, idx, 0) && canForce(idx+1, n, 1)) return true;
        if(canForce(0, idx, 1) && canForce(idx+1, n, 0)) return true;
    } else {
        bool hv0 = false;
        bool hv1 = false;
        for(int i = 1; i <= n; i++) {
            if(i == idx) continue;
            if(masked[i] == 0) hv0 = true;
            else hv1 = true;
        }

        return hv0 && hv1;
    }

    return false;
}

int main() {
#ifdef LOCAL
    freopen("E.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    int T; cin >> T;

    while(T--) {
//        reset();

        cin >> n;
        for(int i = 1; i <= n; i++) cin >> a[i];

        for(int i = 1; i <= n; i++) cout << check(i);
        cout << endl;
    }
}