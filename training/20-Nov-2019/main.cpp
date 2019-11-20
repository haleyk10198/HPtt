#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define fi first
#define se second

int n, m, s, t;
vector<pii> e[100005];
vector<int> r[100005];

int vis1[100005];
vector<int> ans;

void dfs1(int v) {
    vis1[v] = 1;
    for (int u: r[v]) {
        if (not vis1[u]) dfs1(u);
    }
}

void dfs2(int v) {
    if (ans.size() > 1000006) return;
    if (v == t) return;

    for (auto op : e[v]) {
        if (vis1[op.se]) {
            ans.push_back(op.fi);
            dfs2(op.se);
            return;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        e[u].push_back({c, v});
        r[v].push_back((u));
    }

    for (int i = 1; i<= n; i++)
        sort(e[i].begin(), e[i].end());

    dfs1(t);

    if (not vis1[s]) cout << "IMPOSSIBLE\n";
    else {
        dfs2(s);
        if (ans.size() > 1000000) cout << "TOO LONG\n";
        else {
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i] << (i + 1 == ans.size() ? '\n' : ' ');
            }
        }
    }



    return 0;
}
