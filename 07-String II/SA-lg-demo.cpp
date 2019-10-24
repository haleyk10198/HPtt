int tab[LGN][MAXN<<1];
// table is intentionally extended to handle out of bounds
// alternatively you can implement a table lookup function to return -1 for out of bounds input

vi SA;
vi buckets[MAXN];
// note that MAXN should be at least as large as the alphabet set size

void counting_sort(int i, int step){
	for(int j = 0; j < n; j++){
		buckets[tab[i][SA[j]+step]].push_back(SA[j]);
	}
	
	SA.clear();
	
	for(int j = 0; j < MAXN; j++)
	// Go through all buckets!
	{
		copy(buckets[j].begin(), buckets[j].end(), back_inserter(SA));
		// throw the bucket into SA
		buckets[j].clear();
	}
}

void constructSA(string str){
	int n = str.length();
	
	memset(tab, -1, sizeof(tab));
	// set everything to -1, especially to the ones which are out of bounds
	
	for(int i = 0; i < n; i++){
		// give ranks based on its character
		tab[0][i] = str[i]-'a';
	}
	
	SA = vi(n, 0);
	iota(SA.begin(), SA.end(), 0);
	
	for(int i = 1, step = 1; step < n; i++, step<<=1){
		counting_sort(i-1, step);
		counting_sort(i-1, 0);
		
		for(int x = 0, y = 0, rank = 0; x < n; x=y, rank++){
			// same thing as the double lg demo
			for( ; y < n; y++){
				if(tab[i-1][SA[x]] != tab[i-1][SA[y]] || tab[i-1][SA[x]+step] != tab[i-1][SA[y]+step]){
					break;
				}
			}
			for( ; x < y; x++){
				tab[i][SA[x]] = rank;
			}
		}
	}
}

int invert[MAXN]; // from string id to id in SA
int LCP[MAXN], PLCP[MAXN];

void constructLCP(string str){
	// assume SA is built
	int n = str.length();
	
	for(int i = 0; i < n; i++){
		invert[SA[i]] = i;
		// by definition
	}
	
	for(int i = 0, len = 0; i < n; i++, len--){
		if(len < 0)
			len = 0;
		if(invert[i] == 0){
			// there is no previous element
			
		}
		else{
			int j = SA[invert[i]-1]; // the previous element in SA
			
			for( ; i+len < n && j+len < n && str[i+len] == str[j+len]; len++);
		}
		
		PLCP[i] = LCP[invert[i]] = len;
	}
	
	return;
}
