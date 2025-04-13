// dont have the link this time :/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back

vector<pair<int,int>> movs = {{1,0},{0,1},{-1,0},{0,-1}};
const int inf = 1e9;

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    while(cin>>n){
        vector<string> s(n);
        for(int i=0; i<n; i++) cin>>s[i];

        auto f=[&](char c) {
            if(c<'a') return c-'A';
            return c-'a';
        };

        auto valid = [&](int x, int y){
            return x>=0 && y>=0 && x<n && y<n;
        };

        int rs=inf;

        for(int i=0; i<(1<<10); i++){
            if(((1<<f(s[0][0]))&i)>0 && s[0][0]>='a') continue;
            if(((1<<f(s[0][0]))&i)==0 && s[0][0]<'a') continue;

            queue<pair<int,int>> q;
            q.push(mp(0,0));
            vector<vector<int>> dist(n,vector<int>(n,inf));
            dist[0][0]=1;
            while(!q.empty()){
                auto [x, y] = q.front();
                q.pop();

                for(auto [u, v]: movs){
                    u+=x;
                    v+=y;
                    if(valid(u,v)){
                        if(((1<<f(s[u][v]))&i) > 0 && s[u][v] >= 'a') continue;
                        if(((1<<f(s[u][v]))&i) == 0 && s[u][v] < 'a') continue;

                        if(dist[u][v] > dist[x][y]+1){
                            q.emplace(u,v);
                            dist[u][v]=dist[x][y]+1;
                        }
                    }
                }
            }
            rs=min(rs,dist[n-1][n-1]);
        }

        if(rs==inf) rs=-1;
        cout<<rs<<"\n";

    }

    return 0;
}
