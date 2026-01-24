#include <bits/stdc++.h>
using namespace std;

#pragma region

#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define ft first
#define sd second
#define get_bit(i, x) ((1ll << (i)) & (x)) // testar bit i no valor x
#define mp make_pair
#define mt make_tuple
#define dbg(x) cout << #x << " = " << x << endl;
#define el '\n'

using ll = long long;
using ld = long double;
using pii = pair<int,int>;

// template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#pragma endregion

const ll inf = -1e18;
const int K = 600;

void test() {
    /**
     * Dado dois vetores A e B de n elementos cada, você tem uma operação que é remover quaisquer elementos de A. Após a remoção, pareie os elementos restantes
     * com o prefixo de B. Calcule o somatório de a_i*b_i para os m elementos restantes em A.
     * 
     * Para resolver esse problema, podemos calcular uma DP:
     * 
     * DP[i,j] -> Valor máximo considerando os primeiros i valores, removendo j deles no processo.
     * 
     * O problema é que essa dp tem complexidade O(n^2). Para esse problema em específico, temos que os números no vetor são gerados de forma aleatória,
     * tanto os valores em A (entre [1,10^9]) quanto os valores em B (entre [0,1]). Com isso em mente, podemos observar que o seguinte evento acontece: Os valores
     * de B nunca tem mais que log(n) 0s seguidos, pois a probabilidade desse evento acontecer é muito baixa. Com isso, podemos criar o seguinte algoritmo:
     * 
     * Fazemos a mesma programação dinâmica, porém, como tem no máximo log(n) operações de remover, faremos uma espécie de SQRT nos passos que daremos na DP, já
     * que a quantidade de elementos a serem removidos é bem pouca a cada vez que um novo elemento é processado.
     * 
     * Além disso, iremos processar a quantidade de caras removidos de trás pra frente para remover um estado da DP. Assim, temos uma dp linear na quantidade de
     * elementos que tem no vetor. Com essa solução, o bound da complexidade é algo do tipo O(n*sqrt(n)).
     */
    int n;
    cin >> n;

    vector<ll> a(n+1), b(n+1);
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=1; i<=n; i++) cin >> b[i];
    ll rs=0;
    vector<ll> dp(n+1, inf);
    dp[0]=0;

    for(int i=1; i<=n; i++) {
        int v=i/9;
        int d=4*sqrt(i)+10;

        int l=max(0,v-d), r=min(i,d+v);

        for(int j=r; j>=l; j--) {
            ll x,y;
            x=y=inf;
            if(i-j>=1 && dp[j]!=inf) x=dp[j]+a[i]*b[i-j];
            if(j) y=dp[j-1];

            dp[j]=max(x,y);
        }
    }

    for(int i=1; i<=n; i++) rs=max(rs,dp[i]);

    cout<<rs<<"\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(10);

    int tt=1;
    // cin >> tt;
    
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
        // if(_<tt) cout<<"\n";
    }
    
    return 0;
}

