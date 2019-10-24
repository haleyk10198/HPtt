#include <cstring>
#include <algorithm>

#define N 50010
#define M 100010

struct Edge {
    int to;
    Edge *nxt;
};

struct Graph {
    Edge g[M << 1]; // double sz, 1 for real, 1 for domin tree
    Edge *head[N];
    Graph() {
        memset(head, 0, sizeof(head));
    }

    inline void addEdge(int u, int v) {
        static Edge* newEdge(g);
        *(++newEdge) = (Edge) { v, head[u] };
        head[u] = ++newEdge;
    }

    inline Edge*& operator[] (const int u) {
        return head[u];
    }
};

namespace pbds {
    inline bool cmp(const int&, const int&);

    struct DominatorTree {
        Graph cur, rev;
        int ufs[N], val[N]; // union find set
        int fa[N], dfn[N], id[N], idx; // father on DFS tree, dfs order, dfs id
        int sdom[N], idom[N]; // half dominate point, nearest dominate point
        Graph dom;

        inline void addEdge(int u, int v) {
            cur.addEdge(u, v);
            rev.addEdge(v, u);
        }

        inline void dfs(int u) {
            id[dfn[u] = ++idx] = u;
            for(Edge *it = cur[u]; it; it = it->nxt) {
                if(!dfn[it->to]) {
                    fa[it->to] = u;
                    dfs(it->to);
                }
            }
        }

        inline int findfa(int x) {
            if(x == ufs[x]) return x;
            int y = findfa(ufs[x]);
            if(cmp(sdom[val[ufs[x]]]), sdom[val[x]]) {
                val[x] = val[ufs[x]];
            }
            return ufs[x] = y;
        }

        inline void build(const int s, const int n) {
            for(int i = 1; i <= n; ++i) {
                ufs[i] = val[i] = sdom[i] = i;
            }
            dfs(s);
            for(int i = idx, u; u = id[i], i > 1; --i) {
                for(Edge *it = rev[u]; it; it = it->nxt) {
                    if(dfn[it->to]) {
                        findfa(it->to);
                        sdom[u] = std::min(sdom[u], sdom[val[it->to]], cmp);
                    }
                }
                dom.addEdge(sdom[u], u);
                int x = (ufs[u] = fa[u]);
                for(Edge *it = dom[x]; it; it = it->nxt) {
                    findfa(it->to);
                    idom[it->to] = cmp(sdom[val[it->to]], fa[u])? val[it->to]: fa[u];
                }
                dom[x] = 0;
            }

            for(int i = 2, u; u = id[i], i <= idx; i++) {
                (idom[u]^sdom[u]?) idom[u] = idom[idom[u]]: 0;
                dom.addEdge(idom[u], u);
            }
        }
    } T;

    inline bool cmp(const int& u, const int& v) {
        return T.dfn[u] < T.dfn[v];
    }
}

#undef N
#undef M

// credits: http://www.voidcn.com/article/p-kyvslwxg-bqs.html
