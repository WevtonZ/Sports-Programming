// https://judge.yosupo.jp/problem/set_xor_min

// yeah treating it as a string was not a good idea. you can just insert the whole thing as a binary
// number using bitwise operations.

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
const int N = 1e5+3;
const int MAX = 31;

struct Trie{
    map<char,Trie> child;
    bool is_word = false;
    int count = 0;

    void insert(string const & s, int pos = 0){
        if(pos != s.size()){
            child[s[pos]].insert(s, pos+1);
        }
        else{
            is_word=true;
        }
        count++;
    }

    void erase(string const & s, int pos = 0){
        if(pos != s.size() && child.find(s[pos]) != child.end()){
            child[s[pos]].erase(s,pos+1);
            child[s[pos]].count--;
            if(child[s[pos]].count == 0){
                child.erase(s[pos]);
            }
        }
    }

    bool find(string const & s, int pos = 0){
        if(pos!=s.size() && child.find(s[pos]) != child.end()){
            return child[s[pos]].find(s,pos+1);
        }
        else{
            return pos==s.size();
        }
    }

    int search(string const & s, int pos = 0){
        int rs = 0;
        if(pos != s.size()){
            if(child.find(s[pos]) != child.end()){
                rs += child[s[pos]].search(s,pos+1);
            }
            else{
                char ch;
                if(s[pos]=='1'){
                    ch='0';
                }
                else{
                    ch='1';
                }
                if(child.find(ch)!=child.end())
                    rs += (1<<(MAX-pos-1)) + child[ch].search(s,pos+1);
            }
        }
        else{
            return 0;
        }

        return rs;
    }

};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q; cin >> q;
    Trie trie;
    while(q--){
        int x, y;
        cin >> x >> y;
        string s;
        while(y){
            s += ((y&1) ? '1' : '0');
            y>>=1;
        }
        reverse(all(s));
        while(s.size() < MAX) s = '0' + s;
        if(x == 0){
            if(!trie.find(s))
                trie.insert(s);
        }
        else if(x == 1){
            if(trie.find(s))
                trie.erase(s);
        }
        else{
            cout<<trie.search(s)<<"\n";
        }
    }

    return 0;
}
