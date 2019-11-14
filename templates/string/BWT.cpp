class BWT {
public:
    string encodedString;
    int *SA;
    map<char, vi> lt, eq;
    BWT(int *SA): SA(SA) {
        int n = str.length();
        encodedString = string(n, ' ');
        for(int i = 0; i < n; i++) {
            encodedString[i] = str[(i-1+n)%n];
        }

        for(auto x: str) {
            if(!lt.count(x)) {
                lt[x] = eq[x] = vi(n+1, 0);
                for(int i = 0; i < n; i++) {
                    lt[x][i+1] = lt[x][i]+(encodedString[SA[i]] < x);
                    eq[x][i+1] = eq[x][i]+(encodedString[SA[i]] == x);
                }
            }
        }
    }

    pii matchPattern(string str) {
        reverse(str.begin(), str.end());
        pii r0 = pair(lt[str[0]].back(), lt[str[0]].back()+eq[str[0]].back());
        for(int i = 1; i < str.length(); i++) {
            r0 = pair(lt[str[i]].back()+eq[str[i]][r0.first]+1, lt[str[i]].back()+eq[str[i]][r0.second+1]);
        }
        return r0;
    }

    pii extend(pii p, char x) {
        if(lt[x].empty()) lt[x] = eq[x] = vi(1,0 );
        int uu = lt[x].back() + (eq[x].size() <= p.first ? eq[x].back(): eq[x][p.first]);
        int vv = lt[x].back() + (eq[x].size() <= p.second ? eq[x].back(): eq[x][p.second]);
        return pair(uu, vv);
    }
};
