#include <bits/stdc++.h>

using namespace std;

// SPOJ - Can you answer these queries VII
const int MAXN = 100005, MAXL = 131072, MAXLOGN = 25; // L is the lowest power of 2 greater than or equal to N
const int NO_MARK = 0x3fffffff;

struct Tree {
	int N;
	struct Node {
		int id, depth, size, val;
		Node *father, *hSon, *top;
		vector<Node *> neighbors;
	}nodes[MAXN];
	void addEdge(int x, int y) {
		nodes[x].neighbors.push_back(&nodes[y]);
		nodes[y].neighbors.push_back(&nodes[x]);
	}
}tree;

struct SegmentTree {
	struct Info {
		Info(): sum(0), maxSum(0), lMaxSum(0), rMaxSum(0), mark(NO_MARK) {}
		int sum, maxSum, lMaxSum, rMaxSum, mark;
		void merge(Info lSon, Info rSon) {
			// To be filled in
			sum = lSon.sum + rSon.sum;
			lMaxSum = max(lSon.lMaxSum, lSon.sum + rSon.lMaxSum);
			rMaxSum = max(rSon.rMaxSum, rSon.sum + lSon.rMaxSum);
			maxSum = max(max(lSon.maxSum, rSon.maxSum), lSon.rMaxSum + rSon.lMaxSum);
		}
		Info reverse() {
			// To be filled in
			Info ans = *this;
			swap(ans.lMaxSum, ans.rMaxSum);
			return ans;
		}
	}nodes[MAXL << 1];
	int L;
	void buildTree() {
		L = 1;
		while (L <= tree.N) L <<= 1;
		for (int i = 1; i <= tree.N; ++i) {
			// To be filled in
			nodes[L + tree.nodes[i].id].sum = tree.nodes[i].val;
			nodes[L + tree.nodes[i].id].maxSum
			= nodes[L + tree.nodes[i].id].lMaxSum
			= nodes[L + tree.nodes[i].id].rMaxSum = max(tree.nodes[i].val, 0);
			nodes[L + tree.nodes[i].id].mark = NO_MARK;
		}
		for (int i = tree.N; i < L; ++i)
			nodes[L + i] = Info();
		for (int i = L - 1; i >= 1; --i)
			nodes[i].mark = NO_MARK, nodes[i].merge(nodes[i << 1], nodes[(i << 1) | 1]);
	}
	void paint(int id, int l, int r, int val) { // Paint a node (for range modification only)
		// To be filled in
		nodes[id].sum = val * (r - l);
		nodes[id].maxSum = nodes[id].lMaxSum = nodes[id].rMaxSum = max(0, nodes[id].sum);
		nodes[id].mark = val;
	}
	void pushDown(int id, int l, int r) {
		if (id >= L) return;
		if (NO_MARK == nodes[id].mark) return;
		paint(id << 1, l, (l + r) >> 1, nodes[id].mark);
		paint((id << 1) | 1, (l + r) >> 1, r, nodes[id].mark);
		nodes[id].mark = NO_MARK;
	}
	void modify(int id, int l, int r, int p, int q, int val) {
		if (l == p && r == q) {
			paint(id, l, r, val);
			return;
		}
		int m = (l + r) >> 1;
		pushDown(id, l, r);
		if (q <= m) modify(id << 1, l, m, p, q, val);
		else if (p >= m) modify((id << 1) | 1, m, r, p, q, val);
		else modify(id << 1, l, m, p, m, val), modify((id << 1) | 1, m, r, m, q, val);
		nodes[id].merge(nodes[id << 1], nodes[(id << 1) | 1]);
	}
	/*void modify(int x, int val) { // Single-node modification
		// To be filled in
		nodes[L + x].val += val;
		for (int i = (L + x) >> 1; i >= 1; i >>= 1)
			nodes[i].merge(nodes[i << 1], nodes[(i << 1) | 1]);
	}*/
	Info query(int id, int l, int r, int p, int q) { // nodes[id] represents the interval [l, r); query the interval [p, q)
		if (p == l && r == q) {
			return nodes[id];
		}
		pushDown(id, l, r);
		int m = (l + r) >> 1;
		if (q <= m) return query(id << 1, l, m, p, q);
		if (p >= m) return query((id << 1) | 1, m, r, p, q);
		Info ans;
		ans.merge(query(id << 1, l, m, p, m), query((id << 1) | 1, m, r, m, q));
		return ans;
	}
}segTree;

struct HeavyLightDecomposition {
	int cnt;
	void dfs(Tree::Node *x) { // First-round DFS; in particular, find the heavy sons
		x->size = 1;
		int s = x->neighbors.size();
		for (int i = 0; i < s; ++i) {
			Tree::Node *y = x->neighbors[i];
			if (y != x->father) {
				y->father = x;
				y->depth = x->depth + 1;
				dfs(y);
				if (NULL == x->hSon || x->hSon->size < y->size)
					x->hSon = y;
				x->size += y->size;
			}
		}
	}
	void dfs2(Tree::Node *x, Tree::Node *t) { // Put the tree nodes into the segment tree
		x->id = cnt++;
		x->top = t;
		if (NULL != x->hSon) dfs2(x->hSon, t);
		int s = x->neighbors.size();
		for (int i = 0; i < s; ++i) {
			Tree::Node *y = x->neighbors[i];
			if (y != x->father && y != x->hSon) dfs2(y, y);
		}
	}
	void modify(int x, int y, int val) {
		Tree::Node *u = &tree.nodes[x], *v = &tree.nodes[y];
		Tree::Node *tu = u->top, *tv = v->top;
		while (tu != tv) {
			// Be careful whether reversions are required here
			if (tu->depth > tv->depth) {
				segTree.modify(1, 0, segTree.L, tu->id, u->id + 1, val);
				u = tu->father;
				tu = u->top;
			}
			else {
				segTree.modify(1, 0, segTree.L, tv->id, v->id + 1, val);
				v = tv->father;
				tv = v->top;
			}
		}
		if (u->depth <= v->depth) segTree.modify(1, 0, segTree.L, u->id, v->id + 1, val);
		else segTree.modify(1, 0, segTree.L, v->id, u->id + 1, val);
	}
	int query(int x, int y) {
		SegmentTree::Info infos1[MAXLOGN], infos2[MAXLOGN], ans;
		int cnt1 = 0, cnt2 = 0;
		Tree::Node *u = &tree.nodes[x], *v = &tree.nodes[y];
		Tree::Node *tu = u->top, *tv = v->top;
		while (tu != tv) {
			if (tu->depth > tv->depth) {
				infos1[cnt1++] = segTree.query(1, 0, segTree.L, tu->id, u->id + 1).reverse();
				u = tu->father;
				tu = u->top;
			}
			else {
				infos2[cnt2++] = segTree.query(1, 0, segTree.L, tv->id, v->id + 1);
				v = tv->father;
				tv = v->top;
			}
		}
		if (u->depth <= v->depth)
			infos1[cnt1++] = segTree.query(1, 0, segTree.L, u->id, v->id + 1);
		else
			infos1[cnt1++] = segTree.query(1, 0, segTree.L, v->id, u->id + 1).reverse();
		for (int i = 0; i < cnt1; ++i) ans.merge(ans, infos1[i]);
		for (int i = cnt2 - 1; i >= 0; --i) ans.merge(ans, infos2[i]);
		return ans.maxSum;
	}
	void decompose() {
		tree.nodes[1].depth = 0;
		dfs(&tree.nodes[1]);
		dfs2(&tree.nodes[1], &tree.nodes[1]);
		segTree.buildTree();
	}
}hld;

void init() { // Initialize tree and hld. segTree is initialized in SegmentTree::buildTree().
	for (int i = 1; i <= tree.N; ++i)
		tree.nodes[i].hSon = NULL, tree.nodes[i].neighbors.clear();
	hld.cnt = 0;
}

int main() {
	int Q, op, x, y, val;
	scanf("%d", &tree.N);
	init();
	for (int i = 1; i <= tree.N; ++i)
		scanf("%d", &tree.nodes[i].val);
	for (int i = 1; i < tree.N; ++i)
		scanf("%d%d", &x, &y), tree.addEdge(x, y);
	hld.decompose();
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d", &op);
		if (1 == op) scanf("%d%d", &x, &y), printf("%d\n", hld.query(x, y));
		else scanf("%d%d%d", &x, &y, &val), hld.modify(x, y, val);
	}
	return 0;
}

