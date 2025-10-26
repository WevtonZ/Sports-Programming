/**
 * Quando executamos a Prefix Function, temos um vetor chamado "fail", que indica quando a função falha e para onde devemos ir. Com isso, sabemos, para um
 * padrão fixo, para onde devemos ir e como proceder com a função.
 * 
 * No automato, o que a gente quer é pular para o próximo caractere rapidamente, e sem saber qual ele é, só que ele pertence a um alfabeto sigma pré-definido.
 * A grande sacada é que podemos fazer o automato a partir do vetor "fail" da prefix function. Pré processar esse automato custa sigma * N, com N sendo o
 * tamanho da string passada pra função.
 */

const int N = 1e6+10;
const int A = 26;

int go[N][A]; // automato do kmp

void kmp(string s) {
    // essa parte cuida de fazer o KMP ou Prefix Function. O(|s|)
    vector<int> p(s.size(), 0); // vetor "fail" do KMP. Será usado para fazer o automato.
    for(int i=1; i<s.size(); i++) {
        int j = i-1;
        while(p[j] > 0 && s[i] != s[p[j]]) j = p[j]-1;
        if(s[i] == s[p[j]]) p[i] = p[j]+1;
        else p[i]=0;
    }

    // função para calcular o automato do kmp. O(A * |s|)
    for(int i=1; i<=s.size(); i++) {
        go[i-1][s[i-1]-'a'] = i; // dizemos que o link do cara anterior vai para o atual.
        for(int a = 0; a < A; a++) { // percorremos todo o alfabeto. Nesse caso, o alfabeto são os caracteres minúsculos.
            go[i][a] = go[p[i-1]][a]; // esse cara vai para onde o link dele falhar, ou seja, só tem como ele ir para trás.
        }
    }
}
