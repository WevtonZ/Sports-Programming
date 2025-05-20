// https://cses.fi/problemset/task/2191

#include <bits/stdc++.h>
using namespace std;

#define ft first
#define sd second

using ll = long long;

void test(){

    /*
        Podemos achar a área de um polígono usando produto vetorial. A ideia principal é que podemos simplesmente somar todos os produtos
        vetoriais das arestas existentes do polígono. Isso funciona pois, na fórmula de shoelace, temos que

        (p_x - p_y) * (q_x + q_y) = (p_x*q_x + p_x*q_y - q_x*p_y - p_y*q_y).

        O que acontece é que, como o polígono é simples, os termos p_x*q_x e p_y*q_y se cancelam em algum momento, pois, quando eles são adicionados,
        na aresta adjacente a ele, ele será removido da soma. Assim, podemos concluir que somar os produtos vetoriais 2D é suficiente para
        achar a área dobrada do polígono. Para achar a verdadeira área, dividimos essa área por 2.
    */

    int n;
    cin >> n;

    vector<pair<int,int>> a(n);
    for(int i=0; i<n; i++) cin >> a[i].ft >> a[i].sd;

    ll area = 0;

    for(int i=0; i<n; i++){
        int j = (i+1)%n;
        area += 1ll*a[i].ft*a[j].sd - 1ll*a[i].sd*a[j].ft;
    }
    cout<<llabs(area)<<"\n";
}
 
int32_t main(){ 
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout<<fixed<<setprecision(15);
    
    int tt = 1;
    // cin >> tt;
 
    for(int i=1; i<=tt; i++){
        // cout<<"Case "<<i<<": ";
        test();
    }
    
    return 0;
}
