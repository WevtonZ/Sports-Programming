// https://codeforces.com/gym/103960/problem/J

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
    // cout<<fixed<<setprecision(0);

    int n;
    cin >> n;

    int a, b;
    a = b = 0;

    vector<int> mark(15,0);

    int x, y;
    cin >> x >> y;

    a=a+min(10,x)+min(10,y); // elton john

    mark[x]++;
    mark[y]++;
    
    cin>>x>>y;
    
    b=b+min(10,x)+min(10,y); // blood mary
    
    mark[x]++;
    mark[y]++;

    for(int i = 0; i < n; i++){
        cin >> x;
        a+=min(10,x);
        b+=min(10,x);
        mark[x]++;
    }

    for(int i = 1; i <= 13; i++){
        if(mark[i]>=4) continue;
        if(a>b){
            if(a+min(10,i)>23 && b+min(10,i)<=23){
                cout<<i<<"\n";
                return 0;
            }
        }
        else{
            if(b+min(10,i)==23){
                cout<<i<<"\n";
                return 0;
            }
        }
    }

    cout<<"-1\n";

    return 0;
}
