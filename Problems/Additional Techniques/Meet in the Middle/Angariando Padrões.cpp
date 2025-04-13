// https://codeforces.com/group/btcK4I5D5f/contest/346791/problem/A

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
typedef long double ld;

#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back

map<char,int> M = {{'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};

ll f(string x) {
    ll rs=0;
    ll p=1;
    reverse(all(x));
    for(char c: x) {
        if(c >= '1' && c <= '9'){
            rs = rs + (c-'0')*p;
        }
        else{
            rs = rs+M[c]*p;
        }
        p = p*16ull;
    }
    return rs;
}

void test() {
    /*
      Esse é um tipo de problema que as vezes aparece em competições, onde não importa o que você faça, parece muito que tudo é lento, mas que no final isso acaba sendo a resposta
      correta para ele, mas precisa de uma otimização que é mais complicada de se ver.

      Aplicamos aqui a técnica de Meet in the Middle, onde a gente divide o nosso problema em dois, para assim podermos resolver ele em O(n^2log(n)). Resolvemos o primeiro e
      segundo vetores separado do terceiro e quarto vetores. Guardamos a resposta deles em um mapa de frequência de valores, e aí a gente conta quantos deles existem em ambos os vetores,
      pois precisamos combiná-los de algum modo. Para combinar, podemos só multiplicar a frequência deles em ambos mapas, e assim contamos quantos XORs são 0.

      É isso, problema resolvido.
    */
    int n;
    cin >> n;
    map<ll,ll> A, B;
    vector<ll> a(n), b(n), c(n), d(n);
    for(int i=0; i<n; i++){
        string s; cin >> s;
        a[i]=f(s);
    }
    for(int i=0; i<n; i++){
        string s; cin >> s;
        b[i]=f(s);
    }
    for(int i=0; i<n; i++){
        string s; cin >> s;
        c[i]=f(s);
    }
    for(int i=0; i<n; i++){
        string s; cin >> s;
        d[i]=f(s);
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            A[a[i]^b[j]]++;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            B[c[i]^d[j]]++;
        }
    }

    ll rs = 0;
    for(auto [val, cnt]: A) {
        rs += cnt*B[val];
    }
    cout<<rs<<"\n";
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while(t--){
        test();
    }

    return 0;
}
