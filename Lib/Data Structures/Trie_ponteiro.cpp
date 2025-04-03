/*
  Ponto engraçado sobre essa trie:
  Ela é mais lenta do que usar mapa.
*/

const int K = 26;

struct Node {
    vector<Node *> child;
    int ct;

    Node() {
        child.assign(K, nullptr);
        ct = 0;
    }
};

struct Trie {
    Node * root;
    Trie() { root = new Node(); }
    ~Trie() {clear(root);}

    void clear(Node * at) {
        for(int i=0; i<K; i++){
            if(at->child[i] != nullptr) clear(at->child[i]);
        }
        delete at;
        at = nullptr;
    }

    void insert(const string & s) {
        Node * at = root;
        at->ct++;
        
        for(auto ch: s) {
            int pos = ch-'a';
            if(at->child[pos] == nullptr) at->child[pos] = new Node();
            at = at->child[pos];
            at->ct++;
        }
    }

    void erase(const string & s) {
        if(find(s) == 0) return;
        Node * at = root;
        at->ct--;
        for(auto ch: s) {
            int pos = ch-'a';
            if(at->child[pos] == nullptr) at->child[pos] = new Node();
            at=at->child[pos];
            at->ct--;
        }
    }

    int find(const string & s) {
        int tam = 0;
        Node * at = root;
        for(auto ch: s) {
            int pos = ch-'a';
            if(at->child[pos] == nullptr || at->child[pos]->ct == 0) return tam;
            at = at->child[pos];
            tam++;
        }
        return tam;
    }
};
