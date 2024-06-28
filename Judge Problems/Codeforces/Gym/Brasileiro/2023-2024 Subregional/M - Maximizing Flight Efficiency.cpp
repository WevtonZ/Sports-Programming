// https://codeforces.com/gym/104555/problem/M

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<int>> f(n+1, vector<int>(n+1));

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> f[i][j];

    int rs=0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i==j) continue;
            for(int k = 1; k <= n; k++){
                if(i == k || k == j) continue;
                if(f[i][j] > f[i][k]+f[k][j]){
                    cout<<"-1\n";
                    return 0;
                }
                else if(f[i][j] == f[i][k]+f[k][j]){
                    rs++;
                    break;
                }
            }
        }
    }
    cout<<rs/2<<"\n";

    return 0;
}
