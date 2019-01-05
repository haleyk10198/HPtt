// This code is written in a bit clunky way, to show possible ways that others may write it
// Afterall, reading other's solution is also important for learning new algorithms

// range max, point update

#include <bits/stdc++.h>

using namespace std;

using data_t = long long;
constexpr int MAXN = 1e5+10;

#define lhs T[id<<1]
#define rhs T[id<<1|1]

int n;

struct Node{
	// int l, r; bounds of the segment, usually I write this in the update / query functions
	// Node *lchild, *rchild; the children of the node, we are using id*2, id*2+1 instead
	
	data_t value;
	// write a constructor if you want, but I am showing the build() method instead
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
	T[id].value = lhs.value+rhs.value;
}


data_t merge(data_t x, data_t y)
/*
	Some also writes a merge function instead of a maintain
	You will need to write T[id].value = merge(lhs.value, rhs.value) in update
*/
{
	return x+y;
}

void apply(int id)
{
  //fix this later on
  T[id].value = sqrt(T[id].value);
  
  //update T[id], but not lhs rhs
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
    cin >> a[l];
		T[id].value = a[l];
		return;
	}
	
	build(id<<1, l, l+r>>1);
	build(id<<1|1, l+r>>1, r);
	
	maintain(id);
	
	return;
}

void update(int position, int id = 1, int l = 0, int r = n)
/*
	Update a[position]
	The root of tree is T[1], which represents the segment [0, n)
*/
{
	if(position >= r || position < l)
	// if it is out of bounds
	{
		return; // quit immediately
	}
	
	if(l+1 == r)
	// if this entry contains exactly a[position], i.e. [position, position+1)
	{
		apply(id);
		return;
	}
	
	update(position, id<<1, l, l+r>>1); // Try to update with the left child T[id*2] which contains [l, mid)
	update(position, id<<1|1, l+r>>1, r); // Try to update with the right child T[id*2+1]...
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
		data_t null_value = 0; // for sum, this is 0, for max, this is -INF
		return null_value;
	}
	
	if(x <= l && r <= y)
	// if the current bound is contained
	{
		return T[id].value;
	}
	
	int mid = (l+r)/2;
	
	data_t r1 = ask(x, y, id*2, l, mid);
	data_t r2 = ask(x, y, id*2+1, mid, r); // retrieve subtask results
	
	return merge(r1, r2); 
}

int main(){
  cin >> n;
  build();
  int m; cin >> m;
  for(int i = 0, op; i < m; i++){
    cin >> op;
    if(op == 0){
      int x, y; cin >> x >> y;
      for(int j=x-1; j < y; j++){
        if(a[j] == 1);
        else{
          update(j);
        }
      }
    }
    else if(op == 1){
    	int x, y; cin >> x >> y;
      cout << ask(--x, y) << endl;
    }
  }
}
