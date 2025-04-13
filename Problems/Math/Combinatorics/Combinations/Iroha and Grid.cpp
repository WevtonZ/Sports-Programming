// https://atcoder.jp/contests/abc042/tasks/arc058_b

#include <bits/stdc++.h>
using namespace std;

#pragma region
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

using ll = long long;
using ld = long double;

// template<class T> using ordset = tree<T, null_type, less<T>,
// rb_tree_tag, tree_order_statistics_node_update>;
 
template <typename T, typename T1> ostream & operator<<(ostream & os, pair<T,T1> p) {
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}
 
template <typename T, typename T1> istream & operator>>(istream & is, pair<T,T1> & p) {
    is >> p.ft >> p.sd;
    return is;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const int mod = 1e9+7;
const int N = 2e5+10;
ll fat[N], ifat[N];

ll fexp(ll a, ll b) {
    ll rs=1;
    while(b){
        if((1&b)) rs=rs*a%mod;
        a=a*a%mod;
        b>>=1ll;
    }
    return rs;
}

ll comb(int n, int k){
    ll rs=1;
    rs = fat[n];
    rs = rs*ifat[k]%mod;
    rs = rs*ifat[n-k]%mod;
    return rs;
}

void test() {
    /*
        Basicamente o que o problema quer é que a gente saia da célula (1,1) e ir pra célula (n,m) sem encostar no retângulo
        no canto inferior esquerdo da grid. Para sair do (1,1) e ir pro (n,m) sem se importar com isso, podemos fazer um tomado
        do tipo C(n+m-2, n-1). Vamos usar isso para a segunda parte da conta.

        Vamos basicamente dividir o nosso problema em dois retângulos e calcular cada um de forma separada. Para o primeiro
        retângulo, precisamos ser capazes de chegar nas células acima do limite das linhas e do lado do limite das colunas.
        Para isso, faremos a conta C(n-a+i-2, n-a-1), onde i é uma variável que controla a coluna que estamos calculando agora.
        Para o segundo quadrado, faremos a conta C(a+m-i-1, a-1), que vem do fato de que agora precisamos olhar apenas para
        o final.

        É uma explicação mei ruim. algum dia eu melhoro o porque de cada conta.
    */

    fat[0]=ifat[0]=1;
    for(ll i=1; i<N; i++){
        fat[i] = (fat[i-1]*i)%mod;
        ifat[i] = fexp(fat[i], mod-2);
    }

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    ll rs=0;
    for(int i=b+1; i<=m; i++) {
        rs += comb(n-a+i-2, n-a-1) * comb(a+m-i-1, a-1);
        rs%=mod;
    }
    cout<<rs<<"\n";
}
 
int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    cout<<fixed<<setprecision(8);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
