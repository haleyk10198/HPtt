#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

#define MOD 1000000007
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

int en[MAXN], ed[MAXN], dfsTime;
int sccEn[MAXN], sccEd[MAXN];

void DFS(int x) {
    visited[x] = true;
    en[x] = dfsTime++;
    for(auto v: eList[x]) {
        if(not visited[v]) {
            DFS(v);
        }
    }
    ed[x] = dfsTime;

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

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> q;
    for(int i = 0; i < n; i++) cin >> str[i];

    map<char, pii> dirs;
    dirs['U'] = pair(-1, 0);
    dirs['D'] = pair(1, 0);
    dirs['L'] = pair(0, -1);
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
    fill(sccEn, sccEn+MAXN, MOD);

    for(int i = 0; i < n*m; i++) {
        sccEn[sccId[i]] = min(sccEn[sccId[i]], en[i]);
        sccEd[sccId[i]] = max(sccEd[sccId[i]], ed[i]);
    }

    for(int i = 0, x1, x2, y1, y2, from, to; i < q; i++) {
        cin >> x1 >> y1 >> x2 >> y2; --x1, --x2, --y1, --y2;
        from = flattenIdx(x1, y1);
        to = flattenIdx(x2, y2);
        from = sccId[from];
        to = sccId[to];

        if(en[from] <= en[to] && ed[from] >= ed[to]) {
            cout << sccEd[sccId[from]]-sccEn[sccId[to]] << endl;
        } else cout << 0 << endl;
    }

    return 0;
}
