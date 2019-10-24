struct state {
    int len, link;
    int clone, cnt; // optional
    map<char, int> next; // at most 3n-4 fwd links in total
} st[MAXNLEN<<1]; // at most 2n-1 states

int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
    // reset next and optional fields!
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len+1;
    int p = last;
    while(p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if(p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if(st[p].len+1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len+1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            st[clone].clone = 1;
            while(p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

// call init

bool checkOccurrence(string str) {
    int pos = 0;
    for(auto x: str) {
        if(st[pos].next.count(x)) {
            pos = st[pos].next[x];
        } else return false;
    }
    return true;
}

// exclude empty root by taking -1
int countUniqueSubstrings(int pos = 0) {
    int ret = 1;
    for(auto [_, to]: st[pos].next) {
        ret += countUniqueSubstrings(to);
    }
    return ret;
}

// total length by generalizing the dp above
// k-smallest by dfs on the substring unique
// smallest cyclic shift by S+S and walk n smallest steps

// could be done with BWT
void countOccurrence() {
    for(int i = sz-1; i >= 0; i--) {
        if(!st[i].clone) {
            st[i].cnt++;
        }
        if(st[i].link >= 0) {
            st[st[i].link].cnt += st[i].cnt;
        }
    }
}

// show first and show all are delegated to BWT
// LCS could be done by SA LCP, or just simultaneous tree traversal.

// credits: https://cp-algorithms.com/string/suffix-automaton.html
