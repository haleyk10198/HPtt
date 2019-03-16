static unsigned long x=123456789, y=362436069, z=521288629;
unsigned long gen(void) {          //period 2^96-1
unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

   t = x;
   x = y;
   y = z;
   z = t ^ x ^ y;

  return z;
}

struct Node{
	int rem, res, id, pend, pendres;
	unsigned long pr;
	Node *l, *r;
	Node(int id, int cost):rem(cost), id(id){
		res = pend = pendres = 0;
		pr = gen(); //Use any random generating function
		l = r = nullptr;
	}
	Node(){
		l = r = nullptr;
	}
};

void push(Node *T){
	//push updates
	if(T->l){
		T->l->res += T->pendres;
		T->l->pendres += T->pendres;
		T->l->rem -= T->pend;
		T->l->pend += T->pend;
	}
	
	if(T->r){
		T->r->res += T->pendres;
		T->r->pendres += T->pendres;
		T->r->rem -= T->pend;
		T->r->pend += T->pend;		
	}
	
	T->pendres = T->pend = 0;
	return;
}

int great(Node *T){
	if(T == nullptr)
		return -INF;
	push(T);
	if(T->r == nullptr)
		return T->rem;
	return great(T->r);
}

void merge(Node* &T, Node *L, Node *R){
	/*merging two treaps, and store it to T
		requires max(L) <= min(R)*/
	if(L == nullptr){
		T = R;
		return;
	}
	if(R == nullptr){
		T = L;
		return;
	}
	if(L->pr > R->pr){
		push(L);
		merge(L->r, L->r, R);
		T = L;
		return;
	}
	else{
		push(R);
		merge(R->l, L, R->l);
		T = R;
		return;
	}
}

void split(Node *T, int val, Node* &L, Node* &R){
	/*
		how to split the treap:
			provide L, R placholder
			eg: R
			R->r is an auto-include
			R->l is passed as R recursively to determine the parts which fulfills val >= v
			if there are no more candidtaes then set R->l as nullptr
		*/
	if(T == nullptr){
		L = R = nullptr;
		return;
	}
	push(T);
	if(T->rem >= val){
		R = T;
		split(T->l, val, L, T->l);
	}
	else{
		L = T;
		split(T->r, val, T->r, R);
	}
	return;
}

void insert(Node* &T, Node *n){
	Node *L, *R;
	split(T, n->rem, L, R);
	merge(T, L, n);
	merge(T, T, R);
	return;
}

void ext(Node* &ptr, Node* &ret, Node* now, int val){
	/*Use split + pushall instead of this function
		having a hint pointer could greatly improve the performance*/
	if(not now) return;
	push(now);
	if(now->rem >= val){
		ext(now->l, ret, now->l, val);
		return;
	}
	else{
		ret = now;
		merge(ptr, now->l, now->r);
		now->l = now->r = nullptr;
		return;
	}
}

void pushall(Node* &L, Node* &R){
	if(not R) return;
	push(R);
	pushall(L, R->l);
	pushall(L, R->r);
	insert(L, R);
	R = nullptr;
	return;
}

void unorderedMerge(Node* &T, Node* &L, Node* &R){
	split(R, great(L), T, R);
	pushall(L, T);
	merge(T, L, R);
	return;
}
