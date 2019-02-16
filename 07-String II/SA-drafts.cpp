int SA[MAXN], n;
int tab[LGN][MAXN<<1];
// dp[n]
// dp[2], dp[i-1] (i-1%2) dp[i] dp[i%2]

// tab[log(n/2)][i], rank/comparator for str.substr(i, n/2)

vector<int> bucket[MAXN];
// if MAXN < 128 -> MAXN = 128
// n = 30, i < n buckets, 'abcdef' -> bucket[97='a'] ...

void counting_sort(int offset, int id){
	for(int i = 0; i < n; i++){
    	bucket[tab[id-1][SA[i]]].push_back(SA[i]);
    }
  
  	for(int rank = 0, i = 0, SA_id = 0; i < max(128, n); i++){
    	for(int x = 0, y = 0; y < n; x=y, rank++){
          if(offset == 0){
            if(tab[id-1][bucket[i][x]] == tab[id-1][bucket[i][y]] && 
                         tab[id-1][bucket[i][x]+(1<<(id-1))] == tab[id-1][bucket[i][y]+(1<<(id-1))]){
                  tab[id][bucket[i][y]] = rank;
              }
            else break;
          }
          else{
            if(tab[id-1][bucket[i][x]+offset] == tab[id-1][bucket[i][y]+offset]){
                  tab[id][bucket[i][y]] = rank;
            }
            else break;
          }
          SA[SA_id] = tab[id][bucket[i][y]];
        }
      	bucket[i].clear();
    }
}

vi SA;
void counting_sort(int i, int step){
	for(int j = 0; j < n; j++){
		buckets[tab[i][SA[j]+step]].push_back(SA[j]);
	}
	
	SA.clear();
	
	for(int j = 0; j < MAXN; j++)
	// Go through all buckets!
	{
		copy(buckets[j].begin(), buckets[j].end(), back_inserter(SA));
      	// Python: SA.append(buckets[j]);
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
		couting_sort(i-1, 0);
		
		for(int x = 0, y = 0, rank = 0; x < n; x=y, rank++){
			// same thing as the double lg demo
			for( ; y < n; y++){
				if(tab[i-1][SA[x]] != tab[i-1][SA[y]] || tab[i-1][SA[x]+step] != tab[i-1][SA[y]+step]){
					break;
				}
              	else{
                  tab[i][SA[y]] = rank;
                }
			}
		}
	}
}

void constructSA(string str){
	memset(SA, 0, sizeof(SA));
  	memset(tab, -1, sizeof(tab));
  
  	n = str.length();
  	for(int i = 0; i < n; i++){
      	// str.substr(0, i);
    	tab[0][i] = str[i]-'A';
    }
  
  	for(int i = 0; i < n; i++){
      	SA[i] = i;
    }
  	sort(SA, SA+n, 0);
  
//   	for(int len = 2, i = 1; len <= n; len*=2, i++){
//       	sort(SA, SA+n, [&len](int x, int y){
//           	if(tab[i-1][x] != tab[i-1][y]){
//             	return tab[i-1][x] < tab[i-1][y];
//             }
//           	else if(tab[i-1][x+len/2] != tab[i-1][y+len/2]){
//               	return tab[i-1][x+len/2] < tab[i-1][y+len/2];
//             }
//           	else return x < y;
//         });
      
//       	for(int x = 0, y = 0; x < n; x=y){
//           	// [x, y)
//           	// str.substr(x, len) == str.substr(y, len);
//           	// str.substr(x, len/2) == str.substr(y, len/2) && str.substr(x+len/2, len/2) == str.substr(y+len/2, len/2);
//           	for( ; y < n; y++){
//               	if(tab[i-1][SA[x]] == tab[i-1][SA[y]] && tab[i-1][SA[x]+len/2] == tab[i-1][SA[y]+len/2]);
//               	else break;
//             }
          		for(int rank=x ; x < y; x++){
                  	tab[i][SA[x]] = rank;
                }
//         }
//     }
  
  // DONT USE
// 	for(int len = 2, i = 1; len <=n ; len*=2, i++){
//     	for(int j = 0; j < n; j++){
//         	bucket[tab[i-1][j]].push_back(j);
//         }
      
//       	for(int i = 0, rank = 0; i < max(128, n); i++){
//         	sort(bucket[i].begin(), bucket[i].end(), [&len](int x, int y){
//               if(tab[i-1][x] != tab[i-1][y]){
//                   return tab[i-1][x] < tab[i-1][y];
//               }
//               else if(tab[i-1][x+len/2] != tab[i-1][y+len/2]){
//                   return tab[i-1][x+len/2] < tab[i-1][y+len/2];
//               }
//               else return x < y;
//             });
  
          
//           	for(int x = 0, y = 0; y < n; x=y, rank++){
//                 for( ; y < n; y++){
//                     if(tab[i-1][bucket[i][x]] == tab[i-1][bucket[i][y]] && 
//                        tab[i-1][bucket[i][x]+len/2] == tab[i-1][bucket[i][y]+len/2]){
//                       	tab[i][bucket[i][y]] = rank;
//                     }
//                     else break;
//                 }
              
//             }
  			// bucket[i].clear();
//         }
  
      
      	
//     }
  // DONT USE
  
  		for(int len = 1, i = 1; len*2 <= n; len*=2, i++){
        	counting_sort(len, i);
          	counting_sort(0, i);
        }
}

void invert[MAXN]; // from string id to id in SA
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

PLCP(str.substr(i), str.substr(j));
void ask(int x, int y){
  if(x == y) return str.length()-x;
  x = inv[x];
  y = inv[y];
  if(x > y) swap(x, y);
  
  // segment tree query[x, y)
  
  return query(x+1, y+1);
}

