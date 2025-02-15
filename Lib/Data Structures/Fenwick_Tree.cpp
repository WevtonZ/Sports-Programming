/*
  Struct da Fenwick Tree.
  Indexado de 1.
  Tem uma flag pra identificar se a estrutura é de prefixo ou sufixo.
*/
template<class T = int>
struct BIT {
    vector<T> bit; // bit ou fenwick tree.
    int n;
    bool flag; // saber se é fenwick de prefixo ou sufixo (0 ou 1). settado como prefixo por padrão.

    BIT(int n, int flag = 0) : n(n), flag(flag) {
        bit.assign(n+10, 0);
    }

    // funcao da fenwick tree. Settado como soma por padrão.
    T f(T a, T b) {
        return a+b;
    }

    // lowest significant bit
    int lsb(int x){ return x&-x; }

    // fazer o update na fenwick tree.
    void updt(int x, T val) {
        if(!flag){
            while(x<n){
                bit[x] = f(bit[x], val);
                x += lsb(x);
            }
        }
        else{
            while(x){
                bit[x] = f(bit[x], val);
                x -= lsb(x);
            }
        }
    }

    // buscar algo na fenwick tree.
    T query(int x) {
        T rs=0;
        if(!flag){
            while(x){
                rs = f(rs, bit[x]);
                x-=lsb(x);
            }
        }
        else{
            while(x<n){
                rs=f(rs,bit[x]);
                x+=lsb(x);
            }
        }
        return rs;
    }
};
