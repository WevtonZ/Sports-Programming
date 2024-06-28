// https://codeforces.com/gym/104555/problem/C

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define pb push_back
#define mp make_pair
#define eb emplace_back

const int N = 1e5+5;
const ll inf = 1e16;

vector<int> e[N];
int ans[N], a[N], tree[N<<2];
int n;

void updt(int x, int tl, int tr, int pos, int val){
    if(tl == tr){
        tree[x]=val;
    }
    else{
        int tm = tl+tr>>1;
        if(pos<=tm)
            updt(x*2,tl,tm,pos,val);
        else
            updt(x*2+1,tm+1,tr,pos,val);
        
        tree[x]=max(tree[x*2],tree[x*2+1]);
    }
}

int get(int x, int tl, int tr, int l, int r){
    if(tl>r||tr<l)
        return 0;
    else if(tl>=l && tr<=r)
        return tree[x];
    else{
        int tm=tl+tr>>1;
        return max(get(x*2,tl,tm,l,r), get(x*2+1,tm+1,tr,l,r));
    }
}

void dfs(int u, int p){
    int x = get(1,1,n,1,a[u]-1);
    updt(1,1,n,a[u],x+1);

    ans[u] = get(1,1,n,1,n); // pegar a resposta quando chegar no vertice.

    for(auto v: e[u]){
        if(v != p){
            dfs(v, u);
        }
    }
    updt(1,1,n,a[u],0);
}


int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    for(int i = 2; i <= n; i++){
        int x; cin >> x;
        e[i].pb(x);
        e[x].pb(i);
    }

    map<int,vector<int>> M; // contar quantos caras eu tenho de cada um deles. Preciso fazer umas coisas malucas.
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        M[a[i]].pb(i);
    }
    int k=1;
    for(auto [x, vet]: M){
        for(auto v: vet){
            a[v] = k;
        }
        k++;
    }

    dfs(1,1);

    for(int i = 2; i <= n; i++)
        cout<<ans[i]<<" ";
    cout<<"\n";

    return 0;
}
