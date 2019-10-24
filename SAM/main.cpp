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

#include <bits/stdc++.h>

using namespace std;

class SAM{
	public:
	    class Node{
		    public:
		    	int minLength;
		        int len;
		        int suf;
		        int isClone;
		        ll prod;
		        ll ways;
		        map<int, int> nxt;

		        Node(int len = 0, int suf = -1, map<int, int> nxt = map<int, int>()): len(len), suf(suf), nxt(nxt), prod(1), isClone(0), minLength(INF), ways(1){

		        }
	    };
	    int nodeCount;
	    vector<Node> nodes;

	    int cur;

	    SAM(int maxLength){
	        nodeCount = 0;
	        nodes = vector<Node>(maxLength);
	        cur = 0;
	    }

	    int insert(int x){
	        if(nodes[cur].nxt.count(x)){
	            cur = nodes[cur].nxt[x];
	        }
	        else {
	            nodes[nodeCount].len = nodes[cur].len + 1;
	            nodes[cur].nxt[x] = nodeCount++;

	            int prev = nodes[cur].suf;
	            cur = nodes[cur].nxt[x];

	            for( ; prev != -1 && !nodes[prev].nxt.count(x); prev = nodes[prev].suf){
	                nodes[prev].nxt[x] = cur;
	            }

	            if(prev == -1){
	                nodes[cur].suf = 0;
	            }
	            else{
	                int fail = nodes[prev].nxt[x];
	                if(nodes[prev].len+1 == nodes[fail].len){
	                    nodes[cur].suf = fail;
	                }
	                else{
	                    int clone = nodeCount++;
	                    nodes[clone].len = nodes[prev].len+1;
	                    nodes[clone].nxt = nodes[prev].nxt;
	                    nodes[clone].suf = nodes[fail].suf;
	                    nodes[clone].isClone = 1;

	                    nodes[fail].suf = nodes[cur].suf = clone;

	                    for( ; prev != -1 && nodes[prev].nxt[x] == fail; prev = nodes[prev].suf){
	                        nodes[fail].nxt[x] = clone;
	                    }
	                }
	            }
	        }

	    	return cur;
	    }

	    void preprocess(){

	    	auto cmp = [this](int x, int y){
	    		if(nodes[x].len != nodes[y].len) return nodes[x].len < nodes[y].len;
	    		else return x < y;
			};

			set<int> vis;

	    	priority_queue<int, vi, decltype(cmp)> pq;
	    	nodes[0].minLength = 0;

	    	pq.push(0);
	    	while(not pq.empty()){
	    		int n = pq.top();
	    		pq.pop();

	    		if(vis.count(n)) continue;
	    		vis.insert(n);

	    		for(auto [x, y]: pq){
	    			nodes[y].minLength = min(nodes[y].minLength, nodes[n].len+1);
	    			nodes[y].ways += nodes[n].ways;
	    			pq.push(y);
				}
			}

		}
}sam(MAXN);

int n, a[MAXN], pos[MAXN];
string str[MAXN];

int main(){
	#ifdef LOCAL
		freopen("../input.txt","r",stdin);
//		freopen("output.txt","w",stdout);
		freopen("debug.txt", "w", stderr);
	#endif
	ios_base::sync_with_stdio(false);

	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> str[i];
		for(auto x: str[i]){
			sam.insert(x);
		}
		pos[i] = sam.insert(-i);
	}

	for(int i = 0; i < n; i++){
		cin >> a[i];
	}

	return 0;
}

