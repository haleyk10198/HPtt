// This code is written in a bit clunky way, to show possible ways that others may write it
// Afterall, reading other's solution is also important for learning new algorithms

// range add update and sum query

#include <bits/stdc++.h>

using namespace std;

using data_t = int;
constexpr int MAXN = 1e5+10;

#define identity 0
// The identity value of the function, just like what we did in query

#define lhs T[id<<1]
#define rhs T[id<<1|1]

int n;

struct Node{
	// int l, r; bounds of the segment, usually I write this in the update / query functions
	// Node *lchild, *rchild; the children of the node, we are using id*2, id*2+1 instead
	
	data_t value;
	data_t delay; // now this is also needed
}T[MAXN<<2]; // takes 4N memory

data_t a[MAXN];

void maintain(int id)
/*
	Maintain the node T[id]
	Some also call this "pushup", as it "push" the values in the children "upwards"
	
	As this does not maintaining nodes of out of the tree
	Some also pass the lhs and rhs to be merged into T[id],
	this is useful for handling query with the query results stored in T[-1]
	Some even pass maintain(Node &parent, const Node lhs, const Node rhs)
*/
{
	T[id].value = lhs.value + rhs.value;
}

data_t merge(data_t x, data_t y)
/*
	Some also writes a merge function instead of a maintain
	You will need to write T[id].value = merge(lhs.value, rhs.value) in update
*/
{
	return x+y;
}

void apply(int id, data_t value, int l, int r)
// now we also need to pass the size of bound
{
	T[id].value += value*(r-l);
	T[id].delay += value;
	return;
}

void push(int id, int l, int r){
	apply(id<<1, T[id].delay, l, l+r>>1);
	apply(id<<1|1, T[id].delay, l+r>>1, r);
	T[id].delay = identity;
	return;
}

void build(int id = 1, int l = 0, int r = n)
/*
	As there are only N nodes it only take O(N) time to run this function
	You may also call update(i, v0) forall i, which takes O(Nlg N) time to build.
*/
{
	if(l+1 == r)
	// if the lowest layer has been reached
	{
		T[id].value = a[l];
		return;
	}
	
	build(id<<1, l, l+r>>1);
	build(id<<1|1, l+r>>1, r);
	
	maintain(id);
	
	return;
}

void update(int x, int y, data_t value, int id = 1, int l = 0, int r = n)
/*
	Update a[x, y)
	The root of tree is T[1], which represents the segment [0, n)
*/
{
	if(x >= r || l >= y)
	// similar to range query
	{
		return; // quit immediately
	}
	
	if(x <= l && r <= y)
	// similar to range update
	{
		apply(id, value, l, r);
		return;
	}
	
	// push this node before we touch the children
	push(id, l, r);
	
	update(x, y, value, id<<1, l, l+r>>1); // Try to update with the left child T[id*2] which contains [l, mid)
	update(x, y, value, id<<1|1, l+r>>1, r); // Try to update with the right child T[id*2+1]...
	// [l, mid) + [mid, r) = [l, r) = the bounds of this node
	
	maintain(id);
	
	return;	
}

data_t ask(int x, int y, int id = 1, int l = 0, int r = n)
/*
	Asks for the range [x, y)
*/
{
	if(x >= r || l >= y)
	// two segments do not intersect
	{
		return identity;
	}
	
	if(x <= l && r <= y)
	// if the current bound is contained
	{
		return T[id].value;
	}
	
	push(id, l, r);
	
	int mid = (l+r)/2;
	
	data_t r1 = ask(x, y, id*2, l, mid);
	data_t r2 = ask(x, y, id*2+1, mid, r); // retrieve subtask results
	
	return merge(r1, r2); 
}

int main(){
	iota(a, a+MAXN, 0); // a = [0, 1, 2, 3, ..., MAXN-1]
	n = 10;
	build();
	
	cout << "sum of [0, 10) is: " << T[1].value << endl; // T[1].value is also a way to refer the result of the whole array
	
	cout << "Now we +10 on [0, 5)!" << endl;
	update(0, 5, 10);
	
	for(int x, y; cin >> x >> y; ){
		cout << "The sum of a[" << x << ", " << y << ") is: " << ask(x, y) << endl;
	}
}
