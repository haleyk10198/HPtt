/* Author haleyk10198 */
/* §@ªÌ:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

#define pb push_back

constexpr auto MOD = 1000000007LL;
constexpr auto LINF = (1LL << 60);
constexpr auto INF = 2147483647LL;
constexpr auto PI = 3.1415926535897932384626433;
constexpr auto EPS = 1E-9;

template<typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> p) {
    out << p.first << ' ' << p.second;
    return out;
}

template<typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p) {
    in >> p.first >> p.second;
    return in;
}

template<typename T>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v)
        in >> x;
    return in;
}

template<typename T>
ostream &operator<<(ostream &out, vector<T> v) {
    for (int i = 0; i < v.size(); i++)
        out << v[i] << (i + 1 == v.size() ? '\n' : ' ');
    out.flush();
    return out;
}

#if __cplusplus < 201703L
#define mp make_pair
#endif

string str[3];
constexpr ll prime = 29;

#define MAXN 2010

ll inv_prime[MAXN];
ll hh[3][MAXN];

ll pwr(ll b, ll e){
    b %= MOD;
    if(e == 0) return 1;
    if(e == 1) return b;
    return (pwr(b*b, e/2)*pwr(b, e%2))%MOD;
}

void hash_function(string str, ll *hh){
    ll p = 1;
    for(int i = 0; i < str.length(); i++, (p*=prime)%=MOD){
        hh[i] += 1LL*(str[i]-'a'+1)*p;
        hh[i] %= MOD;

        hh[i+1] = hh[i];
    }

    return;
}

set<ll> res[MAXN];
/* equality check helps reducing clash rate, see WA: https://codeforces.com/contest/113/submission/47970849 */

ll hash_value(ll *hh, int left, int right){
    ll ret = hh[right-1];
    if(left > 0)
        ret -= hh[left-1];
    ret *= inv_prime[left];
    ret %= MOD;
    if(ret < 0)
        ret += MOD;
    return ret;
}

int main() {
#ifdef LOCAL
    freopen("../input.txt","r",stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);

    inv_prime[0] = 1;
    ll p = 1; // beware of overflow! define ll
    for(int i = 0; i < MAXN; i++, (p*=prime)%=MOD){
        inv_prime[i] = pwr(p, MOD-2);
    }

    for(int i = 0; i < 3; i++){
        cin >> str[i];
        hash_function(str[i], hh[i]);
    }


    for(int left = 0; left < str[0].length(); left++){
        for(int right = left+max(str[1].length(), str[2].length()); right <= str[0].length(); right++){
            if(hash_value(hh[0], left, left+str[1].length()) == hash_value(hh[1], 0, str[1].length()) &&
               hash_value(hh[0], right-str[2].length(), right) == hash_value(hh[2], 0, str[2].length())){
                res[right-left].insert(hash_value(hh[0], left, right));
            }
        }
    }

    cout << accumulate(res, res+MAXN, 0, [](int acc, set<ll> s){
        return acc+s.size();
    }) << endl;

    return 0;
}
