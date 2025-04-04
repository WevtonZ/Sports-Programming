// N é o tamanho da maior string na trie. K é a profundidade da árvore.
// como isso nao funciona muito bem pra mim, eu só boto um tamanho aleatório.

// TODO: Fazer as outras funções da trie de String.
// TODO: Fazer a trie de bits e fazer todas as suas funções.

const int N = 1e6+2, K = 18;

struct Node {
    int child[26];
    bool leaf;

    Node() : leaf(false) {
        memset(child,0,sizeof(child));
    }
};

Node trie[N*K];
int tam = 0;

void insert(const string & s) {
    int at = 0;
    for(auto ch: s) {
        int pos = ch-'a';
        if(trie[at].child[pos] == 0) trie[at].child[pos] = ++tam;
        at = trie[at].child[pos];
    }

    trie[at].leaf=true;
}
