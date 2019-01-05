#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define MAXN 100010
#define SIGMA 10
#define OFFSET '0'

int nxt[SIGMA][MAXN];
int leaf[MAXN];
int nodecnt, ok;

void reset(){
    memset(nxt, 0, sizeof(nxt));
    memset(leaf, 0, sizeof(leaf));
    nodecnt = 1;
    ok = 1;
}

void insert(string str){
    int pos = 1;
    for(auto x: str){
        if(nxt[x-OFFSET][pos] == 0)
            nxt[x-OFFSET][pos] = ++nodecnt;

        pos = nxt[x-OFFSET][pos];
    }

    leaf[pos] = 1;
}

void dfs(int pos){
    if(leaf[pos]){
        for(int i = 0; i < SIGMA; i++)
            if(nxt[i][pos]){
                ok = 0;
            }
        return;
    }

    for(int i = 0; i < SIGMA; i++)
        if(nxt[i][pos])
            dfs(nxt[i][pos]);

}

int main() {
#ifdef LOCAL
    freopen("../input.txt","r",stdin);
//		freopen("output.txt","w",stdout);
    freopen("../debug.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while(T--){
        int n; cin >> n;
        reset();

        for(int i = 0; i < n; i++){
            string str; cin >> str;
            insert(str);
        }

        dfs(1);

        cout << (ok? "YES": "NO") << endl;
    }

    return 0;
}
