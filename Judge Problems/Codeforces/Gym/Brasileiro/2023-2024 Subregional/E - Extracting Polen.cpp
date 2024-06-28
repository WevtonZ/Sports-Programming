// https://codeforces.com/gym/104555/problem/E

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

int32_t main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    vector<int> a(1000010, 0);
    for(int i = 0; i < n; i++){
        int x; cin >> x;
        a[x]++;
    }

    int rs=0;

    auto digsum = [&](int x)-> int {
        string s = to_string(x);
        int sum=0;
        for(int i = 0; i < s.size(); i++){
            sum += s[i]-'0';
        }
        return sum;
    };

    for(int i = 1000000; i > 0; i--){
        if(!a[i]) continue;
        int x = digsum(i);
        if(k-a[i]<=0){
            cout<<x<<"\n";
            return 0;
        }
        k-=a[i];
        a[i-x]+=a[i];
        a[i]=0;
    }

    cout<<"0\n";

    return 0;
}
