#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds;

using namespace std;

using ll = long long;
#define pii pair<ll, ll>
#define fi first
#define se second

typedef tree<
        pair<ll, pii>,
        null_type,
        greater<>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        OT;


#define MAXN 1000010

int n;
set<pii> edges;
map<pii, int> weights;

void solve(int u, int v, OT &out) {
    vector<OT> children;
    const int u0 = u;
    const int v0 = v;
    edges.erase(pair(v, -u));

    while(true) {
        auto it = edges.upper_bound(pair(v, -u));
        if(it == edges.begin()) {
            break;
        }
        --it;
        int y = it->first;
        int x = -it->second;

        if(y <= u) break;
        children.push_back(OT());
        solve(x, y, children.back());
        v = x;
    }

    if(children.empty()) {
        if(weights.count(pair(u0, v0))) {
            out.insert(pair(weights[pair(u0, v0)], pair(u0, v0)));
        }
        return;
    }

    int idx = 0;
    for(int i = 0; i < children.size(); i++) {
        if(children[idx].size() < children[i].size()) {
            idx = i;
        }
    }

    swap(out, children[idx]);

    for(int i = 0; i < children.size(); i++) {
        if(i != idx) {
            auto it = out.begin();
            for(int j = 0; j+1 < children[i].size(); j++) it++;
            for(auto pit = it, oit = --children[i].end(); ; --oit, it = pit) {
                if(it != out.begin()) --pit;
                ll vv = it->first+oit->first;
                out.erase(it);
                out.insert(pair(vv, oit->second));
                if(oit == children[i].begin()) break;
            }
        }
    }

    if(weights.count(pair(u0, v0))) {
        out.insert(pair(weights[pair(u0, v0)], pair(u0, v0)));
    }
    return;
}

ll writeBuffer[MAXN];

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i = 0, s, t, v; i < n; i++) {
        cin >> s >> t;
        cin >> weights[pair(s, t)];
        edges.insert(pair(t, -s));
    }

    OT res;
    solve(1, 1e6, res);

    {
        int idx = 0;
        for(auto node: res) {
            writeBuffer[idx] += node.first;
            writeBuffer[idx+1] += writeBuffer[idx];
            idx++;
        }
        for( idx; idx < n; idx++) writeBuffer[idx] = writeBuffer[idx-1];
    }

    for(int i = 0; i < n; i++) cout << writeBuffer[i] << (i+1 == n? '\n': ' ');

    return 0;
}
