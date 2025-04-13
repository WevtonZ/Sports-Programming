// https://atcoder.jp/contests/abc054/tasks/abc054_d

/*
    Basicamente isso é uma DP do tipo dp[i][sa][sb]: Na posição i, eu tenho sa do primeiro líquido e sb do segundo líquido. Como o valor dos líquidos são bem pequenos,
    é possível de armazená-los em uma tabela e assim fazer uma DP em cima disso.
    Bom, como o N desse problema é muito pequeno, dá pra você usar a técnica de Meet in the Middle e dividir o vetor em dois, depois calcular todos os subconjuntos de GCD possíveis
    desses vetores e depois combiná-los de alguma forma. Não me recordo de que forma você tem que juntá-los, mas é possível.
*/

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)

#define int long long
#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const int N = 2e5+3;
const int inf = 1e15;

int dp[41][403][403];
vector<tuple<int,int,int>> a;
int n, x, y;

int solve(int i, int sa, int sb){
    if(i==n){
        int g = gcd(sa, sb);
        if(g != 0 && sa/g == x && sb/g == y){
            return 0;
        }
        return inf;
    }

    int &ans = dp[i][sa][sb];
    if(ans != -1) return ans;
    ans = inf;

    ans = solve(i+1, sa, sb);
    auto [u, v, w] = a[i];
    ans = min(ans, solve(i+1, sa+u, sb+v)+w);
    return ans;
}

void teste(){
    cin >> n >> x >> y;
    a.resize(n);
    for(auto &[u, v, w]: a){
        cin >> u >> v >> w;
    }

    memset(dp,-1,sizeof(dp));
    int rs = solve(0, 0, 0);
    if(rs == inf) rs = -1;
    cout<<rs<<"\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test = 1;
    // cin >> test;

    while(test--){
        teste();
    }

    return 0;
}
