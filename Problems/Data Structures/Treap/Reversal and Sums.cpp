// https://cses.fi/problemset/task/2074/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // rng. geralmente fica do lado de fora da estrutura.

/*
    Indexado de 0.

    coisas importantes a se notar:

    1. o In-Order de uma árvore binaria de busca sempre dá as coisas ordenadas pelo valor. Estamos ordenando a prioridade
    do nó, então ela nos dá os nós em ordem de prioridade. Isso faz com que a forma da nossa árvore seja unicamente
    determinada.
    2. reverse é roubado.
    3. Operações na Treap são O(log N) com alta probabilidade.

*/
template<class T = int> struct Treap {
    struct Node {
        T value; // valor do no. Qualquer tipo é bem vindo, desde que voce faça as alterações necessárias pra operar ele.
        Node * l; // No a esquerda do atual.
        Node * r; // No a direita do atual.
        bool rev; // saber se a subarvore com esse Node com raiz está invertida. Usar lazy pra propagar pros filhos.
        int sz; // contagem de filhos da subarvore do No atual. Útil para o merge/split.
        int p; // representa a prioridade desse Node. Prioridade aleatória. Desnecessário mudar esse parâmetro.

        T sum; // soma da subarvore de um nó.

        Node() {}
        Node(T value) : l(nullptr), r(nullptr), rev(false), sz(1), p(rng()), value(value), sum(0) {}
    };

    typedef Node * pnode; // ponteiro pra nao ficar usando Node * em tudo.
    pnode root; // raiz da arvore.

    Treap() : root(nullptr) {}
    ~Treap() {clear(root);} // limpa a árvore. Ainda nao sei exatamente como isso funciona.

    // retorna quantidade de filhos do nó t.
    int size(pnode t) {
        return t!=nullptr ? t->sz : 0;
    }
    // saber quantos nós tem na treap.
    int size(){
        return size(root);
    }

    T calc_sum(pnode t) {
        return t != nullptr ? t->sum : 0;
    }

    // atualiza a contagem de nos da subarvore.
    void updt(pnode t) {
        if(t != nullptr) {
            t->sz = 1 + size(t->l) + size(t->r);
            t->sum = t->value + calc_sum(t->l) + calc_sum(t->r);
        }
    }

    // tecnica de lazy propagation. Usando com o reverse. Pode ser usado em outras coisas, tipo soma na subarvore.
    void push(pnode t) {
        if(t != nullptr && t->rev == true){
            t->rev = false;
            swap(t->l, t->r);
            if(t->l != nullptr) t->l->rev ^= true;
            if(t->r != nullptr) t->r->rev ^= true;
            updt(t); // caso seja necessario dar update na contagem de nos. Se nao, comentar.
        }
    }
    
    // quebrar a treap em duas.
    void split(pnode t, pnode & left, pnode & right, int key, int add = 0) {
        if(t == nullptr){
            return void(left=right=nullptr);
        }
        push(t);
        int cur_key = add + size(t->l);
        if(key <= cur_key) {
            split(t->l, left, t->l, key, add);
            right=t;
        }
        else{
            split(t->r, t->r, right, key, add + 1 + size(t->l));
            left=t;                                                                                                                                                                 
        }
        updt(t);
    }

    // juntar duas treaps.
    void merge(pnode & t, pnode l, pnode r) {
        push(l), push(r);
        if(l == nullptr || r == nullptr){
            t = l ? l : r;
        }
        else if(l->p > r->p){ 
            merge(l->r, l->r, r);
            t = l;
        }
        else{
            merge(r->l, l, r->l);
            t = r;
        }
        updt(t);
    }

    // inserir um no val na posicao pos da arvore t.
    void insert(pnode &t, pnode val, int pos) {
        pnode t1, t2;
        split(t, t1, t2, pos);
        merge(t1, t1, val);
        merge(t, t1, t2);
    }

    // inserir um valor val na arvore, na posicao pos.
    void insert(T val, int pos) {
        pnode x = new Node(val);
        insert(root, x, pos);
    }

    // apagar um elemento na posicao dada na árvore.
    void erase(int pos) {
        pnode t1, t2, t3;
        split(root, t1, t2, pos-1);
        split(t2, t2, t3, pos);
        delete t2, t2 = nullptr;
        merge(root, t1, t3);
    }

    // inverte um subarray [l, r].
    void reverse(pnode t, int l, int r) {
        if(l >= r) return;
        pnode t1, t2, t3;
        split(t, t1, t2, l);
        split(t2, t2, t3, r-l+1);
        t2->rev ^= true;
        merge(t, t1, t2);
        merge(t, t, t3);
    }

    void reverse(int l, int r) {
        reverse(root, l, r);
    }

    // mover um bloco [l,r] para a posicao indicada.
    void move(int l, int r, int pos) {
        pnode t1, t2, t3;
        split(root, t1, t2, l);
        split(t2, t2, t3, r-l+1);
        if(pos <= l) insert(t1, t2, pos);
        else insert(t3, t2, pos-r);
        merge(root, t1, t3);
    }

    // imprime a arvore.
    void print(pnode t) {
        if(t == nullptr) return;
        push(t);
        print(t->l);
        cout << t->value;
        print(t->r);
        return;
    }

    // faz alguma query na range [l, r]. Usar
    ll query(int l, int r) {
        pnode t1, t2, t3;
        split(root, t1, t2, l);
        split(t2, t2, t3, r-l+1);
        ll rs = t2->sum;
        merge(root, t1, t2);
        merge(root, root, t3);

        return rs;
    }

    void print(){
        print(root);
    }
    
    // limpa a arvore.
    void clear(pnode t) {
        if(t == nullptr) return;
        clear(t->l);
        clear(t->r);
        delete t;
        t = nullptr;
    }
};

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    Treap<ll> treap;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    for(int i=0; i<n; i++){
        treap.insert(a[i], i);
    }

    while(q--){
        int p, l, r;
        cin >> p >> l >> r;
        l--, r--;
        if(p == 1) treap.reverse(l, r);
        else cout << treap.query(l, r) << "\n";
    }
    
    return 0;
}
