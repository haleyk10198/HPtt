/* Author haleyk10198 */
/* ?@??:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

#define pb push_back

constexpr auto MOD = 998244353LL;
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

const int G = 3; // Primitive root

long long fastPow(long long a, long long b) {
    long long ans = 1;
    a %= MOD;
    while (b) {
        if (b & 1) ans = (ans * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return ans;
}

struct NumberTheoreticTransform {
    void rearrange(long long arr[], int len) { // len must be a power of 2
        for (int i = 1, j = len >> 1; i < len - 1; ++i) {
            if (i < j) swap(arr[i], arr[j]);
            int k = len >> 1;
            while (j >= k) j -= k, k >>= 1;
            j += k;
        }
    }
    void work(long long y[], int len, int mode) {
        rearrange(y, len);
        for (int h = 2; h <= len; h <<= 1) {
            long long omegaN = fastPow(G, (MOD - 1) / h);
            if (mode == INTT) omegaN = fastPow(omegaN, MOD - 2);
            for (int j = 0, h2 = h >> 1; j < len; j += h) {
                long long omega = 1;
                for (int k = j; k < j + h2; ++k) {
                    long long a = y[k], b = (omega * y[k + h2]) % MOD;
                    y[k] = (a + b) % MOD;
                    y[k + h2] = ((a - b) % MOD + MOD) % MOD;
                    omega = (omega * omegaN) % MOD;
                }
            }
        }
        if (mode == INTT) {
            long long inv =  fastPow(len, MOD - 2);
            for (int i = 0; i < len; ++i)
                y[i] = (y[i] * inv) % MOD;
        }
    }
    enum Mode{NTT, INTT};
}ntt;

bool isRoot(long long x, long long y) { // Test if y is a primitive root of x. Usually x is MOD, and if true is returned, we set G to y.
    long long p = y;
    for (long long i = 1; i < x - 1; ++i) {
        p = (p * y) % x;
        if (p == y) return false;
    }
    return true;
}

#define LEN 1048576

ll a[LEN], b[LEN];

int main() {
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    for(int i = 0, x; i < k; i++){
        cin >> x;
        a[x] = 1;
    }

    b[0] = 1;
    ntt.work(a, LEN, ntt.NTT);
    ntt.work(b, LEN, ntt.NTT);

    for(int i = 0; (1<<i) <= n/2; i++){
        if((1<<i)&(n/2)){
            for(int i = 0; i < LEN; i++){
                b[i] *= a[i];
                b[i] %= MOD;
            }
        }
        for(int i = 0; i < LEN; i++){
            a[i] *= a[i];
            a[i] %= MOD;
        }
    }

    ntt.work(b, LEN, ntt.INTT);
    cout << accumulate(b, b+LEN, 0LL, [](ll acc, ll x){
        return (acc+x*x)%MOD;
    }) << endl;

    return 0;
}
