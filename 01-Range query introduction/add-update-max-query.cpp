#include <bits/stdc++.h>

using namespace std;

#define MAXN 30
#define INF 2e9

int n;

struct Node{
//    Node *lchild, *rchild;
    int val;
    int push_needed, push_value;
    Node(){
        val = 0;
        push_needed = 0;
        push_value = 0;
    }
}T[MAXN*4];

int a[MAXN] = {0, 3, 5, 4, 2, 6, 5, 1};

void apply(int id, int v){
    T[id].push_needed = 1;
    T[id].push_value += v;
    T[id].val += v;
}

void build(int id = 1, int l = 0, int r = n){
    if(l+1 == r){
        T[id].val = a[l];
        return;
    }

    build(id<<1, l, l+r>>1);
    build(id<<1|1, l+r>>1, r);

    T[id].val = max(T[id<<1].val, T[id<<1|1].val);
}

void push(int id){
    if(T[id].push_needed){
        apply(id*2, T[id].push_value);
        apply(id*2+1, T[id].push_value);

        T[id].push_needed = 0;
        T[id].push_value = 0;
    }
}

void update(int x, int y, int v, int id = 1, int l = 0, int r = n){
    if(l >= y || x >= r)
    {
        return;
    }

    if(x <= l && r <= y)
    {
        apply(id, v);
        return;
    }

    push(id);

    int mid = (l+r)/2;
    update(x, y, v, id*2, l, mid);
    update(x, y, v, id*2+1, mid, r);

    T[id].val = max(T[id<<1].val, T[id<<1|1].val);

    return;
}

int ask(int x, int y, int id = 1, int l = 0, int r = n)
{
    if(l >= y || x >= r)
    {
        return -INF;
    }

    if(x <= l && r <= y)
    {
        return T[id].val;
    }

    push(id);

    int mid = (l+r)/2;
    int r1 = ask(x, y, id*2, l, mid);
    int r2 = ask(x, y, id*2+1, mid, r);

    return max(r1, r2);
}

int main() {
    ios_base::sync_with_stdio(false);

    int op, x, y, v;

    n = 8;
    build();
    while(cin >> op){
        if(op == 0){
            cin >> x >> y >> v;
            update(x, y, v);
        }
        else if(op == 1){
            cin >> x >> y;
            cout << ask(x, y) << endl;
        }
    }

    return 0;
}
