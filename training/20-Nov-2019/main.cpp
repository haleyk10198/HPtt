#include <bits/stdc++.h>

using namespace std;

int n, m;
string str[510];

int res;

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> str[i];
    }

    for(int x1 = 0, x2 = n - 1; x1 <= x2; x1++, x2--) {
        for(int i = 0, j = m-1; i < m; i++, j--) {
            if(x1 == x2 && i > j) break;
            if(str[x1][i] == '8' && str[x2][j] == '8');
            else if(str[x1][i] == '8' || str[x2][j] == '8') {
                cout << -1 << endl;
                return 0;
            }
            else if(pair(x1, i) == pair(x2, j)) {
                cout << -1 << endl;
                return 0;
            }
            else if(str[x1][i] == '7' && str[x2][j] == '7') {
                res++;
            }
            else if(str[x1][i] == '7' || str[x2][j] == '7') {
                cout << -1 << endl;
                return 0;
            }
            else if(str[x1][i] == str[x2][j]) {
                res++;
            } else;
        }
    }

    cout << res << endl;

    return 0;
}