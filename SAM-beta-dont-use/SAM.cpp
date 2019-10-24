#include <bits/stdc++.h>

using namespace std;

class SAM{
    class Node{
    public:
        int len;
        int suf;
        map<char, int> nxt;

        Node(int len = 0, int suf = -1, map<char, int> nxt = map<char, int>()): len(len), suf(suf), nxt(nxt){

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

    void insert(char x){
        if(nodes[cur].nxt.count(x)){
            cur = nodes[cur].nxt[x];
            return;
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

                    nodes[fail].suf = nodes[cur].suf = clone;

                    for( ; prev != -1 && nodes[prev].nxt[x] == fail; prev = nodes[prev].suf){
                        nodes[fail].nxt[x] = clone;
                    }
                }
            }
        }
    }
};
