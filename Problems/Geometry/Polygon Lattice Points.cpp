// https://cses.fi/problemset/task/2193

#include <bits/stdc++.h>
using namespace std;

#define ft first
#define sd second

using ll = long long;

void test(){

    /*
      A ideia desse problema é usar o Teorema de Pick. Esse teorema nos diz que a área de um polígono pode ser dada pelos pontos na borda e os pontos
      no interior do polígono. Mais especificamente:

      Area = i + b/2 - 1.

      Onde i são os pontos no interior do polígono e b são os pontos da borda.

      Agora, sabendo duas das três informações entre área, i e b, podemos facilmente achar a terceira variável mexendo nas contas. Mais especificamente,
      podemos achar a área do polígono usando a fórmula de Shoelace, e podemos achar os pontos na borda do polígono usando Máximo Divisor Comum. O que
      nos resta é achar os pontos de dentro do polígono. Assim, modificando a equação, temos:

      i = Area - b/2 + 1
      2i = 2Area - b + 2

      Com isso, podemos achar os pontos de dentro do polígono, e imprimir as duas respostas: os pontos da borda e os pontos de dentro do polígono.
    */
  
    int n;
    cin >> n;
 
    vector<pair<int,int>> a(n);
    for(int i=0; i<n; i++) cin >> a[i].ft >> a[i].sd;
 
    ll bd=0;
    ll area=0;
 
    for(int i=0; i<n; i++){
        int j=(i+1)%n;
        bd+=gcd(a[i].ft-a[j].ft, a[i].sd-a[j].sd);
        area += 1ll*a[i].ft*a[j].sd - 1ll*a[i].sd*a[j].ft;
    }
 
    cout << (llabs(area)-bd+2)/2 << " " << bd << "\n";
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
