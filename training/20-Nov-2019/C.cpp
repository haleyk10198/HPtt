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

#define MAXN 1000010

int n, m, q;
string str[1010];

vi eList[MAXN], reList[MAXN], vList;
bool visited[MAXN];
int sccId[MAXN], sz[MAXN];

inline int flattenIdx(int x, int y) {
    return x*m+y;
}

void addEdge(int x, int y) {
    eList[x].push_back(y);
    reList[y].push_back(x);
}

void DFS(int x) {
    visited[x] = true;
    for(auto v: eList[x]) {
        if(not visited[v]) {
            DFS(v);
        }
    }

    vList.push_back(x);
}

void RDFS(int x, int id) {
    visited[x] = true;
    sccId[x] = id;
    sz[id]++;
    for(auto v: reList[x]) {
        if(not visited[v]) {
            RDFS(v, id);
        }
    }
}

int findSCC() {
    memset(visited, 0, sizeof(visited));
    vList.clear();
    for(int i = 0; i < n*m; i++) {
        if(!visited[i]) {
            DFS(i);
        }
    }

    memset(visited, 0, sizeof(visited));
    int nSCC = 0;
    for(int i = n*m-1; i >= 0; i--) {
        if(!visited[vList[i]]) {
            RDFS(vList[i], nSCC++);
        }
    }

    return nSCC;
}

int resolved[MAXN];

int main() {
#ifdef LOCAL
    freopen("../input.txt", "r", stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> q;
    for(int i = 0; i < n; i++) cin >> str[i];

    map<char, pii> dirs;
    dirs['U'] = pair(-1, 0);
    dirs['D'] = pair(1, 0);
    dirs['L'] = pair(-1, 0);
    dirs['R'] = pair(0, 1);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(auto [ch, pp]: dirs) {
                if(ch == str[i][j]) continue;
                int x = i+pp.first;
                int y = j+pp.second;

                if(x < 0 || y < 0 || x >= n || y >= m) continue;
                addEdge(flattenIdx(i, j), flattenIdx(x, y));
            }
        }
    }

    findSCC();
    for(int i = n*m-1; i >= 0; i--) {
        int from = vList[i];
        from = sccId[from];
        set<int> reach;
        if(resolved[from]) continue;
        for(auto to: eList[from]) {
            if(sccId[to] != from) {
                reach.insert(sccId[to]);
                sz[from] += sz[sccId]
            }
        }

    }
    for(int from = 0; from < n * m; from++) {

    }

    return 0;
}
