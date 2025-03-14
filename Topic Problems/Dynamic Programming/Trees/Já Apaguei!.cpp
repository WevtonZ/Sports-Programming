// https://codeforces.com/group/btcK4I5D5f/contest/346791/problem/J

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back

const int N = 1e5+10;

ll a[N];
ll dp[N][2]; // maximo da subarvore com raiz i.

vector<int> graph[N]; // GARFO
set<int> morte;

void solve(int u, int ant) {
    dp[u][1]=a[u];

    for(auto v: graph[u]){
        if(v == ant) continue;
        solve(v, u);
        if(dp[v][0]>dp[v][1]) dp[u][0]+=dp[v][0];
        else dp[u][0]+=dp[v][1];
        dp[u][1] += dp[v][0];
    }
}

void restore(int u, int ant, bool flag) {
    if(flag == true){
        morte.insert(u);
        for(auto v: graph[u]){
            if(v == ant) continue;
            restore(v,u,flag^1);
        }
    }
    else{
        for(auto v: graph[u]) {
            if(v == ant) continue;
            if(dp[v][0] > dp[v][1]) restore(v, u, flag);
            else restore(v, u, flag^1);
        }
    }
}

void test() {
    /*
      Um problema de Programação Dinâmica em Árvores. Precisamos maximizar a soma de caras pegos na árvore, sem pegar caras adjacentes. Uma possível solução é analisar quais
      transições precisamos passar, e como fazê-las. O negócio é que podemos resolver para cada subárvore, qual é o melhor estado para ela no final, pois assim, podemos
      calcular a partir de uma raiz qualquer a resposta correta, já que a resposta não depende da raiz da árvore.

      Nossas transições são:
        dp[u][1] = w_u; // Inicialmente esse cara tem o valor do nó, se escolhermos pegar ele.

        dp[u,0] = sum(max(dp[v,0], dp[v,1]), para todo v que é filho de u.
        dp[u,1] = sum(dp[v,0]), para todo v filho de u.

        Com essas transições, podemos garantir que dp[raiz,0] e dp[raiz,1] tem a maior soma de vértices que é posśivel obter na árvore, com o vértice raiz ou sem.
        Para recuperar, basta andar de novo na árvore, considerando qual dos dois valores dados é maior, e depois disso pegar todos os vértices que foram pegos, ou seja,
        todos os caras com o booleano marcado como 1.
    */
  
    int n;
    cin >> n;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<n; i++){
        int x,y;
        cin >> x >> y;
        graph[x].pb(y);
        graph[y].pb(x);
    }

    solve(1, 1);
    cout<<max(dp[1][0], dp[1][1])<<"\n";
    if(dp[1][0]>dp[1][1]) restore(1,1,0);
    else restore(1,1,1);
    for(auto i: morte) cout<<i<<" ";
    cout<<"\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while(t--){
        test();
    }

    return 0;
}
