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

int n, m, s, cnt[MAXN], nn;

pii egcd(ll a, ll b) {
    if(a > b) {
        auto [x, y] = egcd(b, a);
        return pair(y, x);
    }

    if(a == 0) return pair(0, 1);
    auto [x, y] = egcd(b%a, a);
    return pair(y-(b/a)*x, x);
}

int main() {
#ifdef LOCAL
    freopen("J.txt", "r", stdin);
#endif

    int T; cin >> T;
    while(T--) {
        fill(cnt, cnt+n, 0);
        nn = 0;

        cin >> n;
        for(int i = 0, x; i < n; i++) {
            cin >> x; --x;
            if(cnt[x]++);
            else nn++;
        }

        sort(cnt, cnt+n, greater<>());
        n = nn;

        for(int mi = cnt[n-1]; ; mi--) {

            if(all_of(cnt, cnt+n, [&mi](const int x) {
                // a*(mi+1) + b*mi = cnt[i]%mi
                ll c1 = x%mi;
                return c1*(mi+1) <= x;
            })) {
                cout << accumulate(cnt, cnt+n, 0LL, [&mi](const ll acc, const int x) {

                    ll c1 = x%mi;
                    ll rem = (x-c1*(mi+1))%(1LL*mi*(mi+1));
                    ll c2 = rem/mi;
                    ll c3 = (x-rem)/(mi+1);

                    return acc+c2+c3;
                }) << endl;
                break;
            }
        }

    }
}