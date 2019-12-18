#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;
using vi = vector<int>;

#define MAXN 2000010

template<typename T>
ostream& operator<<(ostream &os, const vector<T> vt) {
    for(int i = 0; i < vt.size(); i++)
        os << vt[i] << (i+1 == vt.size()? "": " ");
    return os;
}

int n, ord[MAXN];
ll res, x[MAXN], y[MAXN], t[MAXN];

int main() {
#ifdef LOCAL
    freopen("A.txt", "r", stdin);
#endif

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> t[i];
    }

    iota(ord, ord+n, 0);
    sort(ord, ord+n, [](const int l, const int r) {
        if(x[l]+t[l] != x[r]+t[r]) return x[l]+t[l] < x[r]+t[r];
        return l < r;
    });

    priority_queue<pii, vector<pii>, greater<>> pq;
    x[n] = 2e18+1;
    ord[n] = n;

    for(ll now = 0, i = 0; !pq.empty() || i < n; ) {
        for( ; i < n && (pq.empty() || x[ord[i]]+t[ord[i]] <= now+pq.top().first); i++) {
            if(now < x[ord[i]]) {
                now = x[ord[i]];
            }
            pq.push(pair(t[ord[i]], y[ord[i]]));
        }

        for( ; !pq.empty() && now+pq.top().first <= x[ord[i]]+t[ord[i]]; ) {
            auto [dt, yy] = pq.top();
            if(yy < now+dt) {
                pq.pop();
            }
            else {
                ll frame = min(yy, x[ord[i]]+t[ord[i]])-now;
                ll make = frame/dt;

                res += make;
                now += make*dt;
            }
        }
    }

    cout << res << endl;
}