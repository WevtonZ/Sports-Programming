// https://cses.fi/problemset/task/1087/

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
// using i128 = __int128_t;
 
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

const int inf = 1e9;
const int N = 1e6+10;

int n;
vector<int> caracteres[300];

string AC = "ACGT";

int dp[N];

int prox(int id, char c) {
    auto tmp = upper_bound(all(caracteres[c]), id);
    if(tmp == caracteres[c].end()) return n+1;
    return *tmp;
}

int solve(int i){
    if(i>n) return dp[i] = 0;
    int &rs = dp[i];
    if(rs!=-1) return rs;
    rs=inf;
    for(auto c: AC) {
        rs = min(rs, solve(prox(i, c))+1);
    }
    return rs;
}

void walk(int i) {
    if(i > n) return;
    for(auto c: AC){
        if(dp[i] == dp[prox(i, c)]+1){
            cout<<c;
            walk(prox(i,c));
            break;
        }
    }
}

void test(){
  /*
    Problema adicional do CSES.
    A ideia é que podemos achar a menor subsequência que não existe na string usando uma DP. Nessa DP, a gente
    calcula:
      DP[i] = min(DP[i], DP[prox(i,c)]+1)
    Onde prox é o próximo índice do caractere c. Se fizermos assim, podemos com certeza achar a menor string
    que não pertence, pois estamos calculando todas as possibilidades de achar uma string válida. Após isso,
    podemos só andar de volta nos estados que a gente criou e recuperar a resposta.
  */
    string s;
    cin >> s;
    s = '$' + s;
    n = s.size();
    memset(dp, -1, sizeof dp);

    for(int i=1; i<n; i++){
        int tt = s[i];
        caracteres[tt].pb(i);
    }
    solve(0);
    walk(0);
    cout<<"\n";
}
 
int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(15);
 
    int t = 1;
    // cin >> t;
 
    for(int i=1; i<=t; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
