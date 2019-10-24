#include <bits/stdc++.h>

using namespace std;

string str[MAXN];
int nxt[26][TOTLEN], fail[MAXN], has_str[MAXN], nodecnt = 1;

void insert(int id){
	int pos = 0;
	for(auto x: str[id]){
		if(nxt[x-'a'][pos] == 0){
			nxt[x-'a'][pos] = nodecnt++;
		}
		
		pos = nxt[x-'a'][pos];
	}
	
	// add str to has_str
}

void build(){
	queue<int> q;
	for(int i = 0; i < 26; i++){
		if(nxt[i][0] != 0){
			q.push(nxt[i][0]);
		}
	}
	
	while(not q.empty()){
		int now = q.front();
		q.pop();
		
		for(int i = 0; i < 26; i++){
			if(nxt[i][now] != 0){
				int f = fail[now];
				while(f != 0 && nxt[i][f] == 0){
					// pick some other children z
					f = fail[now];
				}
				
				// don't need to check equality with this implementation
				fail[nxt[i][now]] = nxt[i][f];
				//also propagate has_str too, which we will need special DS
				q.push(nxt[i][now]);
			}
		}
	}
}

void match(string str){
	int pos = 0;
	for(auto x: str){
		while(pos && nxt[x-'a'][pos] == 0){
			pos = fail[pos];
		}
		
		pos = nxt[x-'a'][pos];
		if(has_str[pos]){
			//do something
		}
	}
}
