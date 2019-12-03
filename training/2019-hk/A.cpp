#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ostream>

using namespace __gnu_pbds;

using namespace std;

#define INF 0x7fffffff
#define LINF 1e15

using ll = long long;
using pii = pair<ll, ll>;
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
};

map<int, OT> cols, rows;
int n;

ll xy[4];

vector<Line> res;

void tryAdd(OT &T, pii p) {
    auto& [l, r] = p;
    auto it = T.upper_bound(pair(l, -INF));
    if(it != T.end()) {
        auto [x, y] = *it;
        // exclude interior
        pii uni = pair(min(x, l), max(y, r));
        pii inter = pair(max(x, l), min(y, r));

        if(inter.second > inter.first) {
            T.erase(it);
            if(inter.second < uni.second) T.insert(pair(inter.second, uni.second));
            p = pair(uni.first, inter.first);
        }
    }

    it = T.upper_bound(pair(l, INF));

    if(it != T.begin()) {
        --it;
        auto [x, y] = *it;
        // exclude interior
        pii uni = pair(min(x, l), max(y, r));
        pii inter = pair(max(x, l), min(y, r));

        if(inter.second > inter.first) {
            T.erase(it);
            if(inter.second < uni.second) T.insert(pair(inter.second, uni.second));
            p = pair(uni.first, inter.first);
        }
    }

    if(l < r)
        T.insert(p);
}

bool check(OT &T, const ll &l, const ll &r) {
    auto it = T.upper_bound(pair(l, INF));
    if(it != T.begin()) {
        --it;

        if(it->first <= l) {
            if(it->second >= l) {
                ll st = it->second+1;
                if(st > r) return true;
                else return check(T, st, r);
            }
        }
    }

    return false;
}

template<typename T>
ostream& operator<<(ostream &os, const vector<T> vt) {
    for(int i = 0; i < vt.size(); i++) os << vt[i] << (i+1 == vt.size()? "": " ");

    return os;
}

int main() {
#ifdef LOCAL
    freopen("A.txt", "r", stdin);
#endif

    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while(T--) {
        rows.clear();
        cols.clear();
        res.clear();
        cin >> n;

        ll XMAX = -INF;
        ll XMIN = INF;
        ll YMAX = -INF;
        ll YMIN = INF;

        xy[0] = xy[1] = -LINF;
        xy[2] = xy[3] = LINF;

        ll x1, x2, y1, y2;

        for(int i = 0; i < n; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);

            x1 *= 2;
            x2 *= 2;
            y1 *= 2;
            y2 *= 2;

            XMAX = max(XMAX, x2);
            XMIN = min(XMIN, x1);
            YMAX = max(YMAX, y2);
            YMIN = min(YMIN, y1);

            xy[1] = max(x2+y2, xy[0]);
            xy[3] = min(x1+y1, xy[2]);

            xy[0] = max(x2-y1, xy[1]);
            xy[2] = min(x1-y2, xy[3]);

            tryAdd(rows[x1], pair(y1, y2));
            tryAdd(rows[x2], pair(y1, y2));
            tryAdd(cols[y1], pair(x1, x2));
            tryAdd(cols[y2], pair(x1, x2));
        }


        // horizontal rule
        int ok = 1;

        const ll XMID = (XMIN+XMAX)/2;
        for(auto [row, T]: rows) {
            const ll rr = XMID + (XMID-row);
            if(!rows.count(rr)) {
                ok = 0;
                break;
            }
            for(auto [l, r]: T) {
                if(!check(rows[rr], l, r)) {
                    ok = 0;
                    break;
                }
            }
        }

        if(ok) {
            res.emplace_back(Line(2, 0, XMID));
        }

        ok = 1;

        const ll YMID = (YMIN+YMAX)/2;
        for(auto [col, T]: cols) {
            const ll cc = YMID + (YMID-col);
            if(!cols.count(cc)) {
                ok = 0;
                break;
            }
            for(auto [l, r]: T) {
                if(!check(cols[cc], l, r)) {
                    ok = 0;
                    break;
                }
            }
        }

        if(ok) {
            res.emplace_back(Line(0, 2, YMID));
        }

        ok = 1;
        const ll XYMID = (xy[1]+xy[3])/2;
        for(auto [row, T]: rows) {
            const ll cc = XYMID - row;
            if(!cols.count(cc)) {
                ok = 0;
                break;
            }

            for(auto [l, r]: T) {
                ll x = row+(cc-l);
                ll y = row-(r-cc);
                if(x > y) swap(x, y);

                if(!check(cols[cc], x, y)) {
                    ok = 0;
                    break;
                }
            }
        }


        for(auto [col, T]: cols) {
            const ll rr = XYMID - col;
            if(!rows.count(rr)) {
                ok = 0;
                break;
            }
            for(auto [l, r]: T) {
                ll x = col+(rr-l);
                ll y = col-(r-rr);
                if(x > y) swap(x, y);

                if(!check(rows[rr], x, y)) {
                    ok = 0;
                    break;
                }
            }
        }

        if(ok) {
            res.emplace_back(Line(2, 2, XYMID));
        }

        ok = 1;
        const ll YXMID = (xy[0]+xy[2])/2;

        for(auto [row, T]: rows) {
            const ll cc = -YXMID + row;
            if(!cols.count(cc)) {
                ok = 0;
                break;
            }
            for(auto [l, r]: T) {
                ll x = row-(cc-l);
                ll y = row+(r-cc);
                if(x > y) swap(x, y);

                if(!check(cols[cc], x, y)) {
                    ok = 0;
                    break;
                }
            }
        }


        for(auto [col, T]: cols) {
            const ll rr = YXMID + col;
            if(!rows.count(rr)) {
                ok = 0;
                break;
            }
            for(auto [l, r]: T) {
                ll x = col-(rr-l);
                ll y = col+(r-rr);

                if(!check(rows[rr], x, y)) {
                    ok = 0;
                    break;
                }
            }
        }

        if(ok) {
            res.emplace_back(Line(2, -2, YXMID));
        }

        cout << res.size () << endl
             << res << endl;
    }
}