/* Author haleyk10198 */
/* ?@??:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<ll>;
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

map<int, vi> m1;
map<int, vi> m2;
#define MAXK 65536

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

ll a[MAXK], b[MAXK];

void convolute(int x, int y){
    if(m1.count(x+y)) return;

    vi *v1 = &m2[x];
    vi *v2 = &m2[y];
    m1[x+y] = vi(32768, 0);
    vi &v = m1[x+y];
    for(int i = 0; i < MAXK; i++)
        a[i] = (*v1)[i]*(*v2)[i]%MOD;
    ntt.work(a, MAXK, ntt.INTT);
    for(int i = 0; i < 32768; i++)
        v[i] = a[i];

    v1 = &m2[x-1];
    v2 = &m2[y-1];
    for(int i = 0; i < MAXK; i++)
        a[i] = (*v1)[i]*(*v2)[i]%MOD;
    ntt.work(a, MAXK, ntt.INTT);
    for(int i = 1; i < 32768; i++)
        (v[i] += a[i-1]) %= MOD;

    for(int i = 0; i < 32768; i++)
        a[i] = v[i], a[i+32768] = 0;

    ntt.work(a, MAXK, ntt.NTT);
    m2[x+y] = vi(MAXK, 0);
    vi &vv = m2[x+y];
    for(int i = 0; i < MAXK; i++)
        vv[i] = a[i];

    return;
}

void step(int n){
    if(m1.count(n+1)) return;

    vi &v1 = m1[n];
    vi &v2 = m1[n-1];
    m1[n+1] = vi(32768, 0);
    vi &v = m1[n+1];
    v[0] = 1;

    for(int k = 1; k < 32768; k++){
        v[k] = (v1[k]+v1[k-1]+v2[k-1])%MOD;
    }

    for(int i = 0; i < 32768; i++)
        a[i] = v[i], a[i+32768] = 0;
    ntt.work(a, MAXK, ntt.NTT);
    m2[n+1] = vi(MAXK, 0);
    vi &vv = m2[n+1];
    for(int i = 0; i < MAXK; i++)
        vv[i] = a[i];

    return;
}

void compute(int n){
    if(m1.count(n)) return;

    if(n%2){
        compute(n-1);
        step(n-1);
        return;
    }

    compute(n/2);
    convolute(n/2, n/2);
    convolute(n/2, n/2-1);
    convolute(n/2-1, n/2-1);
    return;
}

int main() {
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);

    m1[1] = {1, 1};
    m1[2] = {1, 3, 1};
    m1[3] = {1, 5, 5, 1};
    m1[1].resize(32768);
    m1[2].resize(32768);
    m1[3].resize(32768);

    for(int i = 1; i <= 3; i++){
        memset(a, 0, sizeof(a));
        for(int j = 0; j < 5; j++)
            a[j] = m1[i][j];
        ntt.work(a, MAXK, ntt.NTT);
        m2[i] = vi(MAXK, 0);
        for(int j = 0; j < MAXK; j++)
            m2[i][j] = a[j];
    }

    int n, k; cin >> n >> k;
    compute(n);

    m1[n].resize(k+1);
    m1[n].erase(m1[n].begin());

    cout << m1[n];

    return 0;
}
