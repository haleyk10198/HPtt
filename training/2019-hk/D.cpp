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

int n, k;

int main() {
#ifdef LOCAL
    freopen("D.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    int T; cin >> T;

    while(T--) {
//        reset();

        cin >> k >> n;

        if(n == 0) {
            cout << 10-k << endl;
        } else {
            string res = "";
            for(int ways = k, len = 1; n; len++, ways *= k) {
                if(ways < n) {
                    n -= ways;
                } else {
                    --n;
                    for(int i = 1; i <= len; i++) {
                        res += string(1, '0'+n%k+10-k);
                        n /= k;
                    }
                    reverse(res.begin(), res.end());
                    cout << res << endl;
                }
            }
        }
    }
}