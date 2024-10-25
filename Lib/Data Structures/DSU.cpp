/*
    Simple algorithm for Disjoint Set Union Data Structure. Uses Union by Size instead of rank because they are
    almost the same complexity. Uses path compression heuristic.
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
    vector<int> pai, sz;
    int n;

    DSU(int n) {
        this->n = n;
        pai.resize(n);
        sz.assign(n, 1);
        for(int i=0; i<n; i++){
            pai[i]=i;
        }
    }

    int find(int x) {
        if(x == pai[x]) return x;
        return pai[x] = find(pai[x]);
    }

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
