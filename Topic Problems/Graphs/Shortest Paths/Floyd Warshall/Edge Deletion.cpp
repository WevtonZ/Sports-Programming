// https://atcoder.jp/contests/abc243/tasks/abc243_e

#include <bits/stdc++.h>
using namespace std;

#pragma region

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
typedef pair<double,double> pdb;

#define all(x) x.begin(), x.end()
#define lef(x) (x<<1)
#define rig(x) (lef(x)|1)
#define ft first
#define sd second
#define pb push_back

 
template<class T> using ordset = tree<T,
                        null_type, less<T>, 
                        rb_tree_tag, tree_order_statistics_node_update>;

#pragma endregion

const int N = 1e3+3;
const ll inf = 1e15;

ll dist[400][400];
char e[400][400];

void test(){
    int n, m;
    cin >> n >> m;

    for(int i = 0; i <= n+1; i++){
        for(int j = 0; j <= n+1; j++){
            dist[i][j] = inf;
        }
        dist[i][i] = 0;
    }

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        dist[a][b] = w;
        dist[b][a] = w;
        e[a][b] = 1;
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(!e[i][j]) continue;

            for(int k = 1; k <= n; k++){
                if(k == i || k == j) continue;

                if(dist[i][j] == dist[i][k] + dist[k][j]){
                    ans++;
                    break;
                }
            }
        }
    }

    cout << ans << "\n";
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int teste = 1;
    // cin >> teste;

    while(teste--){
        test();
    }

    return 0;
}
