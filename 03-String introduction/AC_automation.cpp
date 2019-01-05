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
		
		nxt[x-'a'][pos] = nodecnt;
	}
	
	has_str[nodecnt] = id;
}

void build(){
	queue<int> q;
	queue.push(0);
	
	while(not q.empty()){
		int now = q.front();
		q.pop();
		
		for(int i = 0; i < 26; i++){
			if(nxt[i][now] != 0){
				int f = fail[now];
				while(f != 0 && nxt[i][f] == 0){
					f = fail[now];
				}
				
				fail[nxt[i][now]] = nxt[i][f];
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
