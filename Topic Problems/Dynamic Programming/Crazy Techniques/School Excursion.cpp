// https://cses.fi/problemset/task/1706/

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
using i128 = __int128_t;

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

vector<vector<int>> graph;
vector<bool> vis;

int dfs(int x) {
    vis[x]=true;
    int rs=1;
    for(auto i: graph[x]){
        if(!vis[i]) rs += dfs(i);
    }
    return rs;
}

void test(){
    /*
    Uso de um truque de programação dinâmica chamado de 3k trick. A ideia desse truque é perceber os seguintes fatores:

    1. A sua programação dinâmica parece muito pesada em memória ou em tempo (ou em ambos);
    2. Suas contas viram algo do tipo:

        x_1 + x_2 + x_3 + ... + x_k = N
    
    Se isso é verdade, então existem apenas sqrt(N) caras distintos nessa soma. A grande sacada aqui é que podemos diminuir
    essa quantidade ainda mais caso tenhamos caras iguais no nosso vetor, pois podemos juntá-los como se fossem potências
    de 2. Assim, podemos fazer rapidamente a knapsack.
    Por que o nome é 3k trick eu não faço ideia, mas é um bom nome.
    */
    int n, m;
    cin >> n >> m;
    graph.resize(n+1);
    vis.assign(n+1, false);
    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    vector<int> ct(n+1, 0);
    for(int i=1; i<=n; i++){
        if(!vis[i]) ct[dfs(i)]++;
    }

    vector<int> x;
    x.pb(0);
    for(int i=1; i<=n; i++){
        if(ct[i]){
            int sum=1;
            while(sum<=ct[i]){
                ct[i]-=sum;
                x.pb(i*sum);
                sum+=sum;
            }
            if(ct[i]) x.pb(ct[i]*i);
        }
    }
    m=x.size();
    vector<vector<int>> dp(m+10, vector<int>(n+10, 0));

    for(int i=0; i<=m; i++) dp[i][0]=1;
    
    for(int j=1; j<=n; j++){
        for(int i=1; i<m; i++){
            dp[i][j] = dp[i-1][j];
            if(j-x[i]>=0) dp[i][j] |= dp[i-1][j-x[i]];
        }
    }
    for(int i=1; i<=n; i++){
        cout<<dp[m-1][i];
    }
    cout<<"\n";
}

int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(10);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
