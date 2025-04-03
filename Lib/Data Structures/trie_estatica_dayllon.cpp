const int N = 1e6+2, K = 18;

struct Node {
    int child[26];
    bool leaf;

    Node() {
        memset(child,0,sizeof(child));
        leaf=false;
    }
};

Node trie[N*K];
int ct[N*K];
int tam = 0;

void insert(const string & s) {
    int at = 0;
    ct[at]++;
    for(auto ch: s) {
        int pos = ch-'a';
        if(trie[at].child[pos] == 0) trie[at].child[pos] = ++tam;
        at = trie[at].child[pos];
        ct[at]++;
    }

    trie[at].leaf=true;
}

void erase(const string & s) {
    int at=0;
    for(auto ch: s) {
        int pos = ch-'a';
        at = trie[at].child[pos];
        ct[at]--;
    }
    if(ct[at]==0) trie[at].leaf=false;
}
