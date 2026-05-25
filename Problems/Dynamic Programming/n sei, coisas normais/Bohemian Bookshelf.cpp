// https://codeforces.com/gym/106124/problem/B

#include <bits/stdc++.h>
using namespace std;

#define lef(x) ((x) << (1ll))
#define rig(x) (lef(x) | 1)
#define all(x) x.begin(), x.end()
#define get_bit(i, x) ((1ll << (i)) & (x))
#define dbg(x) cout << #x << " = " << x << endl
#define el '\n'

using ll = long long;
using ld = long double;
 
template<class T> using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;
template<class T> using vc = vector<T>;
template<class T> using vvc = vc<vc<T>>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Book {
    int h, t, id;
    Book(int _h=0, int _t=0, int _id=0) : h(_h), t(_t), id(_id) {}
    bool operator<(const Book & o) { return h > o.h; }
};

void test() {
    /**
     * O problema essencialmente pede para que você coloque uns livros em pé e deitados em uma estante.
     * A ideia desse problema é perceber que, se você tem um livro fixo como a base dos livros deitados,
     * a gente só precisa fazer uma DP para descobrir o que fazer com os livros que tem altura menor do
     * que a base.
     * 
     * Assim, façamos uma DP para verificar isso, onde verificamos, caso o livro i seja usado como livro
     * deitado, o que fazer com os livros a frente dele (assuma o vetor ordenado descrescente por altura)
     * Caso o livro nao caiba deitado, não usamos ele e vamos para o próximo. Caso contrário, coloque ele.
     * Todos livros anteriores a ele devem estar em pé, já que para colocar coisas na stack de livros eles
     * precisam ser decrescentes na alturas. Agora, vamos resolver pro resto.
     * 
     * A ideia agora é: se é impossível, a gente simplesmente não faz nada e passa para o próximo livro.
     * Se for possível resolver o problema com esse livro i como a base da stack, vamos imprimir essa resposta
     * já que qualquer uma delas é válida.
     * 
     * A ideia pra isso é fazer um backtracking caçando a resposta depois que ela fica pronta. O algoritmo
     * roda em O(n^2HW), com n a quantidade de livros, H a altura máxima e W a largura máxima.-
     */
    int n, H, W;
    cin >> n >> H >> W;

    vector<Book> books(n+1);
    for(int i=1; i<=n; i++) cin >> books[i].h>>books[i].t, books[i].id = i;
    sort(1+all(books)); // ordenando do maior pro menor para conseguir escolher ou nao colocar o atual deitado

    for(int i=1; i<=n; i++){ // colocando o cara i deitado
        // se o iesimo cara está deitado, então eu posso colocar os depois dele deitados ou em pé, mas os anteriores apenas em pé.
        int s_l = 0; // somar a largura
        bool can = true;
        for(int j=1; j<i; j++) {
            if(books[j].h > H) {
                can=false;
                break;
            }
            s_l+=books[j].t;
        }
        if(!can) continue; // nao consigo usar esse cara aqui, passo pro próximo
        int th, tw;
        tw = W - s_l - books[i].h;
        th = H - books[i].t;

        if(tw < 0 || th < 0) continue; // invalido

        int total = 0;
        for(int j=i+1; j<=n; j++) total += books[j].t;

        // dp com duas dimensões, avalia se eu consigo com uma espessura W e depois valido books altura
        vector dp(n+1, vector<char>(vector<char>(tw+1, 0)));
        dp[i][0]=1;

        for(int j=i+1; j<=n; j++){
            bool ok = (books[j].h <= H);
            for(int w=0; w<=tw; w++) {
                if(!dp[j-1][w]) continue;
                dp[j][w]=true;
                if(ok && w+books[j].t <= tw) {
                    dp[j][w+books[j].t]=true;
                }
            }
        }

        int target = -1;
        for(int w=0; w<=tw; w++){
            if(dp[n][w] && total - w <= th){ // testar se a altura funciona
                if(i == 1 && w == 0) continue;
                
                target = w;
                break;
            }
        }
        
        if(target == -1) continue;
        
        // agora, resolver para esse cara, já que ele é válido.
        vector<int> U,S;
        for(int j=1; j<i; j++) U.push_back(books[j].id);
        S.push_back(books[i].id);
        function<void(int,int)> rec = [&](int j, int w) {
            if(j == i) return;
            if(books[j].h <= H && w >= books[j].t && dp[j-1][w-books[j].t]) {
                rec(j-1,w-books[j].t);
                U.push_back(books[j].id);
            }
            else{
                rec(j-1,w);
                S.push_back(books[j].id);
            }
        };

        rec(n,target);

        cout<<"upright ";
        for(auto id: U) cout<<id<<" ";
        cout<<el;
        cout<<"stacked ";
        for(auto id: S) cout<<id<<" ";
        cout<<el;
        return;
    }
    cout<<"impossible"<<el;
}
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout<<fixed<<setprecision(6);
 
    int tt=1;
    // cin >> tt;
    for(int _=1; _<=tt; _++) {
        // cout<<"Case "<<_<<": ";
        test();
    }
    
    return 0;
}
