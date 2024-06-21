// https://cses.fi/problemset/task/1096

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
 
void mult(ll A[6][6], ll B[6][6]){
    ll aux[6][6] = {0};
 
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 6; k++){
                aux[i][j] = (aux[i][j] + (A[i][k] * B[k][j])%mod)%mod;
            }
        }
    }
 
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            A[i][j] = aux[i][j];
        }
    }
}
 
ll dice(ll n){
    ll mat[6][6] = {{1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 0, 1, 0, 0, 0},
                    {0, 0, 0, 1, 0, 0},
                    {0, 0, 0, 0, 1, 0}};
 
    ll ans[6][6] = {{1, 0, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0, 0},
                    {0, 0, 1, 0, 0, 0},
                    {0, 0, 0, 1, 0, 0},
                    {0, 0, 0, 0, 1, 0},
                    {0, 0, 0, 0, 0, 1}};
 
    
    while(n){
        if(1&n) mult(ans,mat);
        mult(mat,mat);
        n >>= 1;
    }
    return ans[0][0];
}
 
void test(){
    ll n;
    cin >> n;
 
    cout << dice(n) << "\n";
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
