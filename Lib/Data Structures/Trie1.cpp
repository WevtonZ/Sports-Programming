/*
  Struct da árvore Trie.

  Alguns pontos sobre a estrutura:
    1. Foi feita de forma recursiva.
    2. Usa mapa, então é um pouco mais lento do que criar globalmente.

  TODO:
    * Fazer a TRIE iterativa;
*/

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
