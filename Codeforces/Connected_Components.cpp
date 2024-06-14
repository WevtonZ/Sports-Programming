/*
    https://codeforces.com/contest/776/problem/D
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)

#define ft first
#define sd second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

const int N = 2e5+10;

set<int> e[N];

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        e[x].emplace(y);
        e[y].emplace(x);
    }

    set<int> S;
    for(int i = 1; i <= n; i++) S.emplace(i);

    auto bfs = [&](int s)->int {
        queue<int> q;
        q.push(s);
        S.erase(s);
        set<int> tmp; // caras que eu nao consegui visitar.
        int ct=1;
        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(auto i: S){
                if(e[i].find(u) != e[i].end()){
                    // nao da pra alcancar daqui
                    tmp.emplace(i);
                }
                else{
                    ct++;
                    q.push(i);
                }
            }

            swap(S, tmp);
            tmp.clear();
        }
        return ct;
    };

    vector<int> rs;

    for(int i = 1; i <= n; i++){
        if(S.find(i) != S.end()){
            rs.pb(bfs(i));
        }
    }

    sort(all(rs));
    cout<<rs.size()<<"\n";
    for(auto i: rs)
        cout<<i<<" ";
    cout<<"\n";

    return 0;
}