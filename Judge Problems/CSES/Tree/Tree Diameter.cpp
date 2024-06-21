// https://cses.fi/problemset/task/1131

// I actually found out that the concept of Diameter extends very well in general graphs, so you can
// find the diameter on graphs as well.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
 
vector<int> e[N];
vector<int> d1, d2;
vector<char> vis1, vis2;
int maxDiameter = 0, vMax = 0;
 
void dfs1(int v){
    vis1[v]++;
 
    for(auto i: e[v]){
        if(!vis1[i]){
            d1[i] = d1[v] + 1;
            dfs1(i);
        }
        
        if(maxDiameter < d1[i]){
            maxDiameter = d1[i];
            vMax = i;
        }
    }
}
 
void dfs2(int v){
    vis2[v]++;
 
    for(auto i: e[v]){
        if(!vis2[i]){
            d2[i] = d2[v] + 1;
            dfs2(i);
        }
 
        maxDiameter = max(maxDiameter, d2[i]);
    }
}
 
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
 
    for(int i = 0, a, b; i < n-1; i++){
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
 
    d1.assign(n+10, 0);
    d2.assign(n+10, 0);
    vis1.assign(n+10, 0);
    vis2.assign(n+10, 0);
 
    dfs1(1);
    dfs2(vMax);
 
    cout << maxDiameter << '\n';
 
    return 0;
}
