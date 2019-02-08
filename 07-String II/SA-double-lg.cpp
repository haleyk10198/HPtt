int tab[LGN][MAXN<<1];
// table is intentionally extended to handle out of bounds
// alternatively you can implement a table lookup function to return -1 for out of bounds input

int SA[MAXN];

void constructSA(string str){
	int n = str.length();
	
	memset(tab, -1, sizeof(tab));
	// set everything to -1, especially to the ones which are out of bounds
	
	for(int i = 0; i < n; i++){
		// give ranks based on its character
		tab[0][i] = str[i]-'a';
	}
	
	iota(SA, SA+n, 0);
	// iota: SA[0] = 0, SA[1] = 1, ..., SA[n-1] = n-1
	// sorting on i = 0 is not needed here, why?
	
	for(int i = 1, step = 1; step < n; i++, step<<=1)
	// sort until step >= n where lookup tab[i][x+step] must be out of bounds
	{
		sort(SA, SA+n, [&i, step](int x, int y){
			if(tab[i-1][x] != tab[i-1][y]) 
			// lookup first half in the previous table
			{
				return tab[i-1][x] < tab[i-1][y];
			}
			
			if(tab[i-1][x+step] != tab[i-1][y+step])
			// second half
			{
				return tab[i-1][x+step] < tab[i-1][y+step];
			}
			
			return x < y; // stable sort
		});
		
		for(int rank = 0, x = 0, y = 0; x < n; x=y, rank++){
			for( ; y < n; y++){
				// for loop until rank of SA[x] != rank of SA[y]
				if(tab[i-1][SA[x]] != tab[i-1][SA[y]] || tab[i-1][SA[x]+step] != tab[i-1][SA[y]+step])
					break;
			}
			
			for( ; x < y; x++){
				tab[i][SA[x]] = rank;
			}
		}
	}
}
