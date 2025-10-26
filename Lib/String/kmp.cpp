/*
    Prefix function ou KMP, função para achar as substrings de uma string s que são também prefixos dela mesma
*/

const int N = 1e5+10;

vector<int> kmp(string & s) {
    vector<int> p(s.size(), 0);
    for(int i=1; i<s.size(); i++){
        int j = i-1;
        while(p[j] > 0 && s[i] != s[p[j]]) j = p[j]-1;
        if(s[i] == s[p[j]]) p[i] = p[j]+1;
        else p[i] = 0;
    }
    return p;
}
