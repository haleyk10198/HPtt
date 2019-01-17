/* Author haleyk10198 */
/* ?@??:  haleyk10198 */
#include <bits/stdc++.h>

#define MOD 1000000007
#define LINF (1LL<<60)
#define INF 2147483647
#define PI 3.1415926535897932384626433
#define ll long long
#define pii pair<int,int>
#define mp(x,y) make_pair((x),(y))

using namespace std;

string itos(int x){
	stringstream ss;
	ss << x;
	return ss.str();
}

ll c[20][20], f[20], dp[20][20], k, t, l, r = LINF, g[20][20];

int canUse[16];
vector<int> now;

ll dpf(int len, int mx){
	if(len == 0)
		return 1;
	if(mx < 0)
		return 0;
	ll &res = dp[len][mx];
	if(res)
		return res;
	for(int i = 0; i <= min(len, canUse[mx]); i++)
		res += c[len][i] * dpf(len - i, mx - 1);
	return res;		
}

ll dpg(int len, int mx){
	if(len == 0)
		return 1;
	if(mx == 16)
		return 0;
	ll &res = g[len][mx];
	if(res)
		return res;
	if(mx){
		for(int i = 0; i <= min(len, canUse[mx]); i++)
			res += c[len][i] * dpg(len - i, mx + 1);
	}
	else{
		for(int i = 0; i <= min(len-1, canUse[mx]); i++)
			res += c[len-1][i] * dpg(len - i, mx + 1);
	}
	return res;		
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	f[0] = 1;
	for(int i = 1; i < 16; i++)
		f[i] = f[i-1] * i;
	for(int i = 0; i < 16; i++)
		for(int j = 0; j <= i; j++)
			c[i][j] = f[i] / f[j] / f[i-j];
	cin >> k >> t;
	fill(canUse, canUse + 16, t);
	while(l+1 < r){
		fill(canUse, canUse + 16, t);
		ll mid = (l+r) / 2;
		ll cnt = 0;
		now.clear();
		for(ll t = mid; t; t /= 16)
			now.push_back(t % 16);
		reverse(now.begin(), now.end());
		for(int i = 1; i < now.size(); i++){
			memset(g, 0, sizeof(g));
			cnt += dpg(i, 0);
		}
		for(int i = 0; i < now.size(); i++){
			for(int j = not i; j < now[i] + (i+1 == now.size()); j++){
				if(canUse[j]--){
					memset(dp, 0, sizeof(dp));
					cnt += dpf(now.size() - i - 1, 15);
				}
				canUse[j]++;
			}
			if(not canUse[now[i]]--)
				break;
		}
		//LUNCH HERE I COME NO MORE STUPID MISTAKES
		if(cnt < k)
			l = mid;
		else
			r = mid;
	}
	cout << hex << r << endl;
	return 0;
}

