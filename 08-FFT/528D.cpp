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
#define MAXN 524288
#define EPS 1e-6
#define ld long double
#define op operator

using namespace std;

string itos(int x){
	stringstream ss;
	ss << x;
	return ss.str();
}

map<char, int> m1;
const string gene = "ACGT";
string s, t;

int n, m, k, rescnt;

struct base {
   typedef double T; T re, im;
   base() :re(0), im(0) {}
   base(T re) :re(re), im(0) {}
   base(T re, T im) :re(re), im(im) {}
   base op + (const base& o) const { return base(re + o.re, im + o.im); }
   base op - (const base& o) const { return base(re - o.re, im - o.im); }
   base op * (const base& o) const { return base(re * o.re - im * o.im, re * o.im + im * o.re); }
   base op * (ld k) const { return base(re * k, im * k); }
   base conj() const { return base(re, -im); }
};

base a[4][550000], b[4][550000];

base w[MAXN]; //omega lookup table
int rev[MAXN]; //reverse lookup table

void build_rev(int k) {
   static int rk = -1;
   if( k == rk )return ; rk = k;
   for(int i = 1; i < (1<<k); i++) {
       int j = rev[i-1], t = k-1;
       while( t >= 0 && ((j>>t)&1) ) { j ^= 1 << t; --t; }
       if( t >= 0 ) { j ^= 1 << t; --t; }
       rev[i] = j;
   }
}

void fft(base *a, int k) {
   build_rev(k); int n = 1 << k;
   for(int i = 0; i < n; i++) if( rev[i] > i ) swap(a[i], a[rev[i]]);
   for(int l = 2, lll = 1; l <= n; l += l, lll += lll) {
       if( w[lll].re == 0 && w[lll].im == 0 ) {
           ld angle = PI / lll;
           base ww( cosl(angle), sinl(angle) );
           if( lll > 1 ) for(int j = 0; j < lll; ++j) {
               if( j & 1 ) w[lll + j] = w[(lll+j)/2] * ww;
               else w[lll + j] = w[(lll+j)/2];
           } else w[lll] = base(1, 0);
       }
       for(int i = 0; i < n; i += l) 
	   	 for(int j = 0; j < lll; j++){
           base v = a[i + j], u = a[i + j + lll] * w[lll + j];
           a[i + j] = v + u; a[i + j + lll] = v - u;
       		}
   }
}

int r[4], req[4];

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	for(auto x: gene){
		int sz = m1.size();
		m1[x] = sz;
	}
	cin >> n >> m >> k >> s >> t;
	fill(r, r+4, -1);
	for(int i = 0; i < n; i++){
		r[m1[s[i]]] = i+k;
		for(int j = 0; j < 4; j++)
			if(r[j] >= i)
				a[j][i+MAXN/2].re = 1;
	}
	fill(r, r+4, n);
	for(int i = n-1; i >= 0; i--){
		r[m1[s[i]]] = i-k;
		for(int j = 0; j < 4; j++)
			if(r[j] <= i)
				a[j][i+MAXN/2].re = 1;
	}
	for(int i = 0; i < m; i++){
		b[m1[t[i]]][i].re = 1;
		req[m1[t[i]]]++;
	}
	
	for(int j = 0; j < 4; j++){
		reverse(b[j], b[j]+MAXN);
		fft(a[j], 19), fft(b[j], 19);
	}
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < MAXN; i++)
			a[j][i] = a[j][i]*b[j][i];
		fft(a[j], 19);
		for(int i = 0; i < MAXN; i++)
			a[j][i].re /= MAXN;
	}

	for(int i = 0; i < MAXN; i++){
		int all = 1;
		for(int j = 0; j < 4; j++)
			all &= (a[j][i].re >= req[j]-EPS);
		if(all)
			rescnt += all;
	}
	cout << rescnt << endl;
	return 0;
}
