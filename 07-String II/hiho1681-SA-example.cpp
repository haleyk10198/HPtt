/* Author haleyk10198 */
/* §@ªÌ:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

#define MOD 1000000007
#define LINF (1LL<<60)
#define INF 2147483647
#define PI 3.1415926535897932384626433
#define ll long long
#define pii pair<int,int>
#define mp(x,y) make_pair((x),(y))
#define pb(x) push_back((x))
#define vi vector<int>
#define vvi vector<vi>
#define EPS 1e-9

#define MAXN 2000010
#define SIGMA 300

using namespace std;

int n, m, from[MAXN];
string str;

int RA[MAXN], tempRA[MAXN], SA[MAXN], tempSA[MAXN], cnt[MAXN];

void countingSort(int k){
	int n = str.length();
	int maxi = max(SIGMA, n);
	memset(cnt, 0, sizeof(cnt));
	
	for(int i = 0; i < n; i++)
		cnt[i+k < n? RA[i+k]: 0]++;
	
	for(int i = 1; i < maxi; i++)
		cnt[i] += cnt[i-1];
	
	for(int i = maxi; i; i--)
		cnt[i] = cnt[i-1];
	cnt[0] = 0;
	
	for(int i = 0; i < n; i++)
		tempSA[cnt[SA[i]+k < n? RA[SA[i]+k]: 0]++] = SA[i];
	
	for(int i = 0; i < n; i++)
		SA[i] = tempSA[i];	
	
}

void constructSA(){
	int n = str.length();
	int rank = 0;
	for(int i = 0; i < n; i++) RA[i] = str[i];
	for(int i = 0; i < n; i++) SA[i] = i;
	for(int k = 1; k < n; k<<=1){
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = rank = 0;
		for(int i = 1; i < n; i++)
			tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]? rank: ++rank);
		for(int i = 0; i < n; i++)
			RA[i] = tempRA[i];
		if(RA[SA[n-1]] == n-1) break;
	}
}

int Phi[MAXN], PLCP[MAXN], LCP[MAXN];
void computeLCP(){
	int n = str.length();
	Phi[SA[0]] = -1;
	for(int i = 1; i < n; i++)
		Phi[SA[i]] = SA[i-1];
	for(int i = 0, len = 0; i < n; i++){
		if(Phi[i] == -1){
			PLCP[i] = 0;
			continue;
		}
		while(i+len < n && Phi[i]+len < n && str[i+len] == str[Phi[i]+len])
			len++;
		PLCP[i] = len;
		if(--len < 0) len = 0;
	}
	
	for(int i = 0; i < n; i++)
		LCP[i] = PLCP[SA[i]];
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	
	cin >> n >> m;
	
	int res = 0;
	for(int i = 0, tot = 0; i < n; i++){
		if(i) str += '0'+i;
		string t; cin >> t;
		str += t;
		fill(from+tot, from+str.length(), i);
		tot = str.length();
		if(m == 1)
			res = max(res, (int)t.length());
			
	}
	
	if(m == 1){
		cout << res << endl;
		return 0;
	}
	
	constructSA();
	computeLCP();
	
	map<int, int> cnt;
	map<int, int> lens;
	for(int i = 0, j = 0; i < str.length(); i++){
		while(j < str.length() && cnt.size() < m){
			//cout << j << ' ' << str.substr(SA[j]) << ' ' << LCP[j] << endl;
			if(str[SA[j]] < 'a');
			else{
				cnt[from[SA[j]]]++;
				lens[LCP[j]]++;
			}
			j++;
		}
		int check = cnt.size() >= m;
		if(str[SA[i]] < 'a');
		else{
			if(--cnt[from[SA[i]]] == 0)
				cnt.erase(from[SA[i]]);
			if(--lens[LCP[i]] == 0)
				lens.erase(LCP[i]);
		}
		assert(not check || lens.size());
		if(check)
			res = max(res, lens.begin()->first);
	}
	
	cout << res << endl;
	
	return 0;
}

