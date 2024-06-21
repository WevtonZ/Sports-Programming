// https://cses.fi/problemset/task/1723

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<double, double> pdb;
 
#define pb push_back
#define ft first
#define sd second
#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
 
const int N = 1e6+10;
const int mod = 1e9+7;
 
ll graph[101][101], ans[101][101];
 
void mult(ll A[101][101], ll B[101][101], int n){
    ll aux[101][101] = {0};
 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= n; k++){
                aux[i][j] = (aux[i][j] + (A[i][k] * B[k][j])%mod)%mod;
            }
        }
    }
 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            A[i][j] = aux[i][j];
        }
    }
}
 
ll solve(int n, int k){
    while(k){
        if(k&1) mult(ans, graph, n);
        mult(graph, graph, n);
        k >>= 1; 
    }
 
    return ans[1][n];
}
 
void test(){
    memset(graph, 0, sizeof(graph));
    memset(ans, 0, sizeof(ans));
 
    int n, m, k;
    cin >> n >> m >> k;
 
    for(int i = 1; i <= n; i++){
        ans[i][i] = 1;
    }
 
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u][v]++;
    }
 
    cout << solve(n, k) << "\n";
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int teste = 1;
    // cin >> teste;
 
    while(teste--){
        test();
    }
 
    return 0;
}
