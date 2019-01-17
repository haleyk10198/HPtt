// This is poorly optimized and will TLE

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

#define MAXK 1e18

//map<ll, int> conv;
int T;
ll k;
string a, b;

int primes[4] = {2, 3, 5, 7};
ll dp[101][80000];

int dpid;
int used[4], conv[60][38][26][22];

inline int getid(){
    return conv[used[0]][used[1]][used[2]][used[3]];
}

inline bool put_digit(int d, int sgn){
    for(int i = 0; i < 4; i++){
        while(d%primes[i] == 0){
            d /= primes[i];
            used[i] += sgn;
        }
    }

    return *min_element(used, used+4) >= 0;
}

ll dpfs(int n){
    if(n == 0) return *max_element(used, used+4) == 0;

    ll &ret = dp[n][getid()];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 1; i < 10; i++){
        if(put_digit(i, -1)){
            ret += dpfs(n-1);
            ret %= MOD;
        }
        put_digit(i, 1);
    }

    return ret;
}

void build(ll num, int pos){
    if(num > MAXK || pos == 4) return;
    conv[used[0]][used[1]][used[2]][used[3]] = dpid++;
    used[pos]++;
    build(num*primes[pos], pos);
    used[pos]--;
    build(num, pos+1);

    return;
}

void init(){
    memset(conv, -1, sizeof(conv));
    memset(dp, -1, sizeof(dp));

    build(1, 0);

    return;
}

bool set_used(ll num){
    memset(used, 0, sizeof(used));
    for(int i = 0; i < 4; i++){
        while(num%primes[i] == 0){
            num /= primes[i];
            used[i]++;
        }
    }

    return num == 1;
}

void string_minus(string &str){
    for(int i = str.length()-1; i >= 0; i--){
        if(str[i]-- == '0'){
            str[i] = '9';
        }
        else break;
    }
}

ll work(const string &str){
    ll ret = 0;
    for(int len = 1; len < str.length(); len++){
        ret += dpfs(len);
        ret %= MOD;
    }

    for(int pos = 0; pos < str.length(); pos++){
        for(int digit = 1; digit+'0' < str[pos]; digit++){
            if(put_digit(digit, -1)){
                ret += dpfs(str.length()-pos-1);
                ret %= MOD;
            }
            put_digit(digit, 1);
        }

        if(str[pos] == '0') break;

        if(not put_digit(str[pos]-'0', -1))
            break;

        if(pos+1 == str.length()){
            ret += dpfs(0);
            ret %= MOD;
        }
    }

    return ret;
}

int main() {
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);

    init();

    cin >> T;

    for(int no = 1; no <= T; no++){
        cin >> a >> b >> k;
        string_minus(a);

        cout << "Case " << no << ": ";

        if(set_used(k)){
            ll res = -work(a);
            set_used(k);
            res += work(b);
            if(res < 0) res += MOD;
            cout << res << endl;
        }
        else
            cout << 0 << endl;
    }

    return 0;
}

