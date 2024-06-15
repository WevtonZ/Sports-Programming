// https://codeforces.com/contest/1985/problem/H1

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define ft first
#define sd second
#define mp make_pair

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int _; cin >> _;
    while(_--){
        int n, m;
        cin >> n >> m;

        vector<vector<char>> grid(n, vector<char>(m));
        vector<vector<pair<int,int>>> groups(n, vector<pair<int,int>>(m, mp(-1,-1)));

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) cin >> grid[i][j];
        }

        // marcar os grupos e a qntd de caras em cada grupo.
        // resolver inserir as cerquilhas em cada linha e em cada coluna.

        vector<pair<int,int>> mov = {{1,0},{-1,0},{0,1},{0,-1}};
        vector<vector<char>> vis(n,vector<char>(m,false));

        auto valid=[&](int x,int y){
            return x>=0 && y>=0 && x<n && y<m;
        };

        auto bfs=[&](int sx, int sy){ // contar caras na componente conexa
            queue<pair<int,int>> q;
            q.push(mp(sx,sy));
            vis[sx][sy]++;

            int cnt=1;

            while(!q.empty()){
                auto [u, v] = q.front();
                q.pop();

                for(auto [x, y]: mov){
                    x+=u;
                    y+=v;
                    if(valid(x,y) && !vis[x][y] && grid[x][y] == '#'){
                        vis[x][y]++;
                        cnt++;
                        q.push(mp(x,y));
                    }
                }
            }
            return cnt;
        };

        auto paint=[&](int sx, int sy, int id, int qtd){
            queue<pair<int,int>> q;
            q.push(mp(sx,sy));

            while(!q.empty()){
                auto [u, v] = q.front();
                q.pop();

                groups[u][v]=mp(id,qtd);

                for(auto [x, y]: mov){
                    x+=u;
                    y+=v;
                    if(valid(x,y) && vis[x][y]==1) vis[x][y]++, q.push(mp(x,y));
                }
            }
        };

        int id=1; // id do grupo a ser inserido.

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j]=='#' && !vis[i][j]){
                    int x = bfs(i,j);
                    paint(i,j,id,x);
                    id++;
                }
            }
        }

        int rs=0;
        for(int i = 0; i < n; i++){
            set<pair<int,int>> S;
            int tmp=m;
            for(int j = 0; j < m; j++){
                if(valid(i-1,j)){
                    if(groups[i-1][j].ft != -1){
                        if(S.find(groups[i-1][j]) == S.end()){
                            S.emplace(groups[i-1][j]);
                            tmp+=groups[i-1][j].sd;
                        }
                    }
                }

                if(valid(i+1,j)){
                    if(groups[i+1][j].ft != -1){
                        if(S.find(groups[i+1][j]) == S.end()){
                            S.emplace(groups[i+1][j]);
                            tmp+=groups[i+1][j].sd;
                        }
                    }
                }

                if(groups[i][j].sd!=-1){
                    if(S.find(groups[i][j]) == S.end()){
                        S.emplace(groups[i][j]);
                        tmp+=groups[i][j].sd;
                    }
                    tmp--;
                }
            }
            
            rs=max(rs,tmp);
        }

        for(int i = 0; i < m; i++){
            set<pair<int,int>> S;
            int tmp=n;
            for(int j = 0; j < n; j++){
                if(valid(j,i-1)){
                    if(groups[j][i-1].ft != -1){
                        if(S.find(groups[j][i-1]) == S.end()){
                            S.emplace(groups[j][i-1]);
                            tmp+=groups[j][i-1].sd;
                        }
                    }
                }

                if(valid(j,i+1)){
                    if(groups[j][i+1].ft != -1){
                        if(S.find(groups[j][i+1]) == S.end()){
                            S.emplace(groups[j][i+1]);
                            tmp+=groups[j][i+1].sd;
                        }
                    }
                }

                if(groups[j][i].sd!=-1){
                    if(S.find(groups[j][i]) == S.end()){
                        S.emplace(groups[j][i]);
                        tmp+=groups[j][i].sd;
                    }
                    tmp--;
                }
            }
            rs=max(rs,tmp);
        }

        cout << rs << "\n";
    }
    return 0;
}
