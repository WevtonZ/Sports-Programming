// https://codeforces.com/contest/706/problem/D

// classic problem of Trie on Bits. There is a trick to pick the boolean value of an integer when
// only that is needed and nothing more.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define all(x) x.begin(), x.end()
#define ft first
#define sd second
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define dbg(x) cout << #x << " = " << x << "\n"

const int inf = 1e9;
const int N = 2e5+3;
const int MAX = 31;

struct Trie{
    map<char,Trie> child;
    int ct=0;

    void insert(int s, int pos=MAX){
        if(pos>=0){
            int nx = !!(s&(1<<pos));
            child[nx].insert(s,pos-1);
            child[nx].ct++;
        }
    }

    void erase(int s, int pos = MAX){
        if(pos>=0){
            int nx=!!(s&(1<<pos));
            child[nx].erase(s,pos-1);
            child[nx].ct--;
            if(child[nx].ct==0){
                child.erase(nx);
            }
        }
    }

    int xor_max(int s, int pos = MAX){
        int rs=0;
        if(pos>=0){
            int nx=!!(s&(1<<pos));
            if(child.count(nx^1)){
                rs += (1<<pos) + child[nx^1].xor_max(s,pos-1);
            }
            else{
                rs += child[nx].xor_max(s,pos-1);
            }
        }
        return rs;
    }
};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q; cin >> q;
    Trie trie;
    trie.insert(0);
    while(q--){
        char ch;
        int x;
        cin >> ch >> x;

        if(ch == '+'){
            trie.insert(x);
        }
        else if(ch == '-'){
            trie.erase(x);
        }
        else{
            cout<<trie.xor_max(x)<<"\n";
        }
    }

    return 0;
}
