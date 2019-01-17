#include <iostream>
#include <cstring>
#include <vector>

#define MOD 1000000007
#define ll long long
#define pb push_back

using namespace std;

ll tmp[32][32];

class Matrix{
	public:
		ll mat[32][32];
		int n, m;
		
		Matrix(int n = 0, int m = 0): n(n), m(m){
			memset(mat, 0, sizeof(mat));
		}
		
		void ID(){
			for(int i = 0; i < n; i++)
				mat[i][i] = 1;
		}
		
		Matrix& operator=(const Matrix rhs){
			n = rhs.n;
			m = rhs.m;
			
			for(int i = 0; i < n; i++)
				for(int j = 0; j < m; j++)
					mat[i][j] = rhs.mat[i][j];
			
			return *this;
		}
		
		Matrix& operator*=(const Matrix rhs){
			memset(tmp, 0, sizeof(tmp));
			
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					for(int k = 0; k < n; k++)
						(tmp[i][j] += mat[i][k]*rhs.mat[k][j]) %= MOD;
			
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					mat[i][j] = tmp[i][j];
		}
};

Matrix tran[7];

inline int lg2(int x){
	return sizeof(int)*8 - __builtin_clz(x);
}

ll calcTran(int x, int y){
	vector<int> v1, v2;
	v1.pb(-1), v2.pb(-1);
	
	while(x){
		v1.pb(lg2(x&-x));
		x -= x&-x;
	}
	
	while(y){
		v2.pb(lg2(y&-y));
		y -= y&-y;
	}
	
	v1.pb(100), v2.pb(100);
	
	int ret = 1;
	for(int i = 0, j = 0; i+1 < v1.size() && j+1 < v2.size(); ){
		if(v1[i] != v2[j]){
			if(v1[i] < v2[j])
				i++;
			else
				j++;
		}	
		else{
			if(v1[i+1] == v2[j+1])
				ret <<= 1;
			i++, j++;
		}
	}
	
	return ret%MOD;
}

int main(){
	
	for(int k = 1; k <= 6; k++){
		tran[k].n = tran[k].m = (1<<(k-1));
		
		for(int i = 0; i < (1<<(k-1)); i++)
			for(int j = i; j < (1<<(k-1)); j++)
				tran[k].mat[i][j] = tran[k].mat[j][i] = calcTran(i, j);
	}
	
	int T; scanf("%d", &T);
	for(int no = 1; no <= T; no++){
		int m, n; scanf("%d%d", &m, &n);
		
		int dim = 1<<(m-1);
		n--;
		
		Matrix t = tran[m];
		Matrix acc(dim); 
		acc.ID();
		
		for(int e = 1; e <= n; e<<=1){
			if(n&e)
				acc *= t;
			t *= t;
		}
		
		int res = 0;
		for(int i = 0; i < dim; i++)
			for(int j = 0; j < dim; j++)
				(res += acc.mat[i][j]) %= MOD;
		
		printf("Case %d: %d\n", no, res);
	}
	
	return 0;
}
