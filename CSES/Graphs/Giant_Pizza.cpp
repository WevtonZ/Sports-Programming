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

vector<int> e[N], re[N];
vector<bool> vis;
vector<int> ord;
int comp[N];

void dfs1(int x){
    vis[x]=true;
    for(auto i: e[x]){
        if(!vis[i]) dfs1(i);
    }
    ord.pb(x);
}

void dfs2(int x, int c){
    vis[x]=true;
    comp[x]=c;
    for(auto i: re[x]){
        if(!vis[i]) dfs2(i,c);
    }
}

void add_edge(int a, bool na, int b, bool nb){
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1;
    int neg_b = b ^ 1;

    e[neg_a].pb(b);
    e[neg_b].pb(a);
    re[a].pb(neg_b);
    re[b].pb(neg_a);
}

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        int x, y;
        char c, d;
        cin >> c >> x >> d >> y;
        x--, y--;
        bool na, nb;
        na = c == '+';
        nb = d == '+';
        add_edge(x, na, y, nb);
    }

    vis.assign(2*m, false);

    for(int i = 0; i < 2*m; i++){
        if(!vis[i]){
            dfs1(i);
        }
    }

    vis.assign(2*m, false);
    reverse(all(ord));
    int c = 1;
    for(auto i: ord){
        if(!vis[i]){
            dfs2(i, c);
            c++;
        }
    }
    vector<int> as(m, false);

    for(int i = 0; i < 2*m; i += 2){
        if(comp[i]==comp[i+1]){
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
        as[i/2]=comp[i]>comp[i+1];
    }

    for(auto i: as)
        cout<<(i==0?'+':'-')<<" ";
    cout<<"\n";

    return 0;
}