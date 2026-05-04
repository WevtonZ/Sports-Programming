/*
  pi[x] -> Quantos primos existem entre 1 e x.
  funciona em O(n^(2/3)), +- N = 10^11.
*/

const int MAX = 1e6+10;
vector<ll> V;
ll S1[MAX+1], S2[MAX+1];
vector<ll> primes;

// esses aqui sao o tamanho do vetor e a raiz desse tamanho, aí dá pra calcular o resto.
ll n, sq;

ll& pi(ll v) {
    if(v <= sq) return S1[v];
    return S2[n/v];
}

void precalc() {
    vector<bool> is_prime(MAX + 1, true);
    sq = sqrt(n);
    if((sq+1)*(sq+1)<=n) sq++;
    if(sq*sq > n) sq--;
    is_prime[0] = is_prime[1] = false;
    for (ll p = 2; p <= sq; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            for (ll i = p * p; i <= sq; i += p) {
                is_prime[i] = false;
            }
        }
    }
    
    for (ll i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ll v = n / i;
        V.push_back(v);
        pi(v) = v - 1; 
    }
    
    for (ll p : primes) {
        ll sp_1 = pi(p - 1);
        ll p2 = p * p;
    
        for (ll v : V) {
            if (v < p2) break; 
            pi(v) -= (pi(v / p) - sp_1);
        }
    }
}
