// https://atcoder.jp/contests/abc293/tasks/abc293_e

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

void power(vector<vector<ll>> &A, vector<vector<ll>>& B, ll mod){
    vector<vector<ll>> aux(2,vector<ll>(2,0));
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            aux[i][j]=0;
            for(int k = 0; k < 2; k++){
                aux[i][j] = (aux[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }

    A = aux;
}

ll fexp(vector<vector<ll>> & A, ll x, ll m){
    vector<vector<ll>> rs = {{1,0},{0,1}};

    while(x){
        if(1&x) power(rs,A,m);
        power(A,A,m);
        x >>= 1ll;
    }

    return rs[0][1];
}

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    ll a, x, m;
    cin >> a >> x >> m;

    vector<vector<ll>> A = {{1,1},{0,a}};

    cout<<fexp(A,x,m)<<"\n";

    return 0;
}
