/*
    Simple algorithm for Disjoint Set Union Data Structure. Uses Union by Size instead of rank because they are
    almost the same complexity. Uses path compression heuristic.
    
    1 indexed.
*/

struct Edge {
    int u, v, w;

    Edge(int _u, int _v, int _w) {
        this->u= _u;
        this->v= _v;
        this->w= _w;
    }

    bool operator<(const Edge &o) {
        return w < o.w;
    }
};

struct DSU {
    vector<int> pai, sz; // pai e quantidade que ele guarda.
    int n; // quantidade de vértices no meu DSU.

    DSU(int n) : n(n) {
        pai.resize(n+10);
        sz.assign(n+10, 1);
        for(int i=0; i<=n; i++){
            pai[i]=i;
        }
    }

    // procura o representante desse cara. Usa compressão de caminhos.
    int find(int x) {
        if(x == pai[x]) return x;
        return pai[x] = find(pai[x]);
    }

    // une os conjuntos entre dois caras. Usa união por tamanho.
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a,b);
        sz[a]+=b;
        pai[b]=a;
        return true;
    }
};
