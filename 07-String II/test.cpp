/* Author haleyk10198 */
/* §@ªÌ:  haleyk10198 */
/* CF handle: haleyk100198*/
/* FOR ACM-ICPC WF*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

#define pb push_back

constexpr auto MOD = 1000000007LL;
constexpr auto LINF = (1LL<<60);
constexpr auto INF = 2147483647LL;
constexpr auto PI = 3.1415926535897932384626433;
constexpr auto EPS = 1E-9;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, const pair<T1, T2> p){
	out << p.first << ' ' << p.second;
	return out;
}

template <typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2> &p){
	in >> p.first >> p.second;
	return in;
}

template <typename T>
istream& operator>>(istream &in, vector<T> &v){
	for(auto &x: v)
		in >> x;
	return in;
}

template <typename T>
ostream& operator<<(ostream &out, vector<T> v){
	for(int i = 0; i < v.size(); i++)
		out << v[i] << (i+1 == v.size()? '\n': ' ');
	out.flush();
	return out;
}

#if __cplusplus < 201703L
	#define mp make_pair
#endif

vi manacher(string input){
	string str;
	for(auto x: input){
		str += x+"$";
	}
	str.pop_back();

	int n = str.length();
	vi len(n, 1);

	for(int i = 1, rightmost = 0, pivot = 0; i < n; i++){
		if(rightmost > i){
			int j = pivot-(i-pivot);
			len[i] = min(len[j], rightmost-i);
		}

		for( ; i >= len[i] && i+len[i] < n && str[i-len[i]] == str[i+len[i]]; len[i]++);

		if(i+len[i] > rightmost){
			rightmost = i+len[i];
			pivot = i;
		}
	}

	return len;
}

vi init(string str){
	int n = str.length();
	vi z(n, 0);
	// z[0] = 0;  special case
	for(int i = 1, rightmost = 0, pivot = 0; i < n; i++){
		if(rightmost > i){
			int j = i-pivot;
			z[i] = min(z[j], rightmost-i);
		}

		for( ; i+z[i] < n && str[z[i]] == str[i+z[i]]; z[i]++);

		if(i+z[i] > rightmost){
			pivot = i;
			rightmost = i+z[i];
		}
	}

	return z;
}

vi match(string pattern, string text){
	string str = pattern+"$"+text;
	vi z = init(str);
	vi match_position;
	for(int i = pattern.length()+1; i < str.length(); i++){
		if(z[i] == pattern.length()){
			match_position.push_back(i);
		}
	}
}

int main(){
	#ifdef LOCAL
//		freopen("input.txt","r",stdin);
//		freopen("output.txt","w",stdout);
		freopen("debug.txt", "w", stderr);
	#endif
	ios_base::sync_with_stdio(false);

	string str = "abaabaab";
	cout << "Z of " << str << ": " << init(str);

	return 0;
}

