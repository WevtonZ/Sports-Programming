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

struct Trie{
    map<char,Trie> children;
    int count = 0;
    bool is_word = false;

    void insert(const string & s, int pos){
        if(pos != s.size()){
            children[s[pos]].insert(s, pos+1);
        }
        else{
            is_word = true;
        }
        count++;
    }

    void erase(const string & s, int pos){
        if(pos != s.size()){
            children[s[pos]].erase(s,pos+1);
            children[s[pos]].count--;
            if(children[s[pos]].count == 0){
                children.erase(s[pos]);
            }
        }
    }

    int search(const string & s, int pos){
        if(pos != s.size() && children.find(s[pos]) != children.end()){
            return children[s[pos]].search(s, pos+1)+1;
        }
        else return 0;
    }
};

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Trie trie;

    int n, q;
    cin >> n;
    vector<string> s(n);
    for(int i = 0; i < n; i++){
        cin >> s[i];
        trie.insert(s[i], 0);
    }

    for(int i = 0; i < n; i++){
        trie.erase(s[i], 0);
        cout << trie.search(s[i], 0) << "\n";
        trie.insert(s[i], 0);
    }

    return 0;
}
