/*
    A ideia de usar Li Chao Tree em vez de LineContainer é que LineContainer não consegue lidar com segmentos de reta, apenas com retas infinitas.
    Assim, podemos resolver problemas que envolvem achar um ponto em uma reta ótima usando Li Chao Tree. Podemos usar essa estrutura em vez do LineContainer,
    ela é mais poderosa, mas é bastante overkill.

    Sobre complexidade:

    1. query de busca é O(log n);
    2. adicionar retas custa O(n log^2 n), pois primeiro precisamos achar a range para adicionar a reta e depois adicioná-la de fato, e ambas custam O(log n).

    TODO: Fazer a Li Chao Tree dinâmica, para poder usar float ou números gigantes e não apenas se limitar a inteiros.
*/

using ll = long long;
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)

// Struct para manter uma reta. Pode ser usado para manter um segmento de reta também.
struct Line {
    ll a, b;
 
    Line() {}
    Line(ll a, ll b) : a(a), b(b) {}
};
 
// pegar o valor da reta ax+b.
ll f(Line l, ll x) {
    return l.a*x + l.b;
}
 
const int N = 2e5+10;
const ll inf = numeric_limits<ll>::min();

// segment tree de linhas.
Line tree[N << 2];

// inicializar a segtree com valores infinitos do tipo (0,inf) ou (0,-inf), dependendo se vc quer maximizar ou minimizar.
void build(int x, int tl, int tr) {
    tree[x] = {0,inf};
    if(tl == tr) {
        return;
    }
    else{
        int tm = (tl+tr)/2;
        build(lef(x), tl, tm);
        build(rig(x), tm+1, tr);
    }
}

// adiciona uma linha no segmento [l, r] que só é válida nele. Ou seja, um segmento de reta.
void add_line(int x, int tl, int tr, Line line) {
    int tm = (tl+tr)/2;
    if(f(line, tm) > f(tree[x], tm)){
        swap(line, tree[x]);
    }
 
    if(f(line, tl) > f(tree[x], tl)){
        add_line(lef(x), tl, tm, line);
    }
 
    if(f(line, tr) > f(tree[x], tr)){
        add_line(rig(x), tm+1, tr, line);
    }
}

// procura a range [l,r] para adicionar a reta. Tudo isso demora O(n*log^2n)
void add_seg(int x, int tl, int tr, int l, int r, Line line) {
    if(tl > r || tr < l) return;
    else if(tl >= l && tr <= r) {
        add_line(x, tl, tr, line);
    }
    else{
        int tm = (tl + tr)/2;
        add_seg(lef(x),tl,tm,l,r,line);
        add_seg(rig(x),tm+1,tr,l,r,line);
    }
}

// faz a query em um ponto pos qualquer. Se não houver, retorne algo infinito, que já está settado.
ll get(int x, int tl, int tr, int pos) {
    if(tl == tr) return f(tree[x], pos);
    else{
        int tm = (tl+tr)>>1;
        ll rs = f(tree[x],pos);
 
        if(pos <= tm) rs=max(rs,get(lef(x),tl,tm,pos));
        else rs=max(rs,get(rig(x),tm+1,tr,pos));
        return rs;
    }
}
