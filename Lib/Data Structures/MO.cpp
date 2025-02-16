/*
    MO data structure to solve problems that revolves around MO algorithm. Pretty easy to use, u can just copypaste
    and use it as a blackbox, only changing the add, remove and calc function.
    Sometimes u may need to change vector<int> rs to some other type, but u can manage it.
*/

struct query{
    static const int K = 350; // constante milagrosa do sqrt(N).
    int l, r, idx; // left, right e indice da query.

    query(int _l, int _r, int _idx) : l(_l), r(_r), idx(_idx) {}

    // operador de desigualdade para ordenar as queries.
    bool operator <(const query &o){
        if(l/K == o.l/K){
            if((l/K)&1){
                return r > o.r;
            }
            return r<o.r;
        }
        return l/K<o.l/K;
    }
};

struct MO{
    /*
        Here we can change everything. Add more things if you think it is necessary for solving your problem,
        be it more variables, vectors and such.
    */
    vector<query> & queries; // vetor para guardar as queries.
    vector<int> rs; // vetor que guarda as respostas.

    MO(vector<query> & queries) : queries(queries){}

    // adiciona esse cara na resposta.
    void add(int x){
      
    }

    // remove esse cara da resposta.
    void rmv(int x){
      
    }

    // calcula a resposta dessa query.
    int calc(){
      
    }

    void run(){
        sort(queries.begin(), queries.end()); // ordena tudo.
        rs.resize(queries.size()); // coloca o tamanho correto nas respostas.

        /*
            Pelo amor de Deus ande com a variável j antes de andar a variável i, pelo simples fato de que, no começo, 
            ela vai estar removendo coisas da sua resposta. Então imagine o estrago que isso causa quando você tenta
            remover itens inexistentes de um set por exemplo. Isso pode ser ruim. Então ande com a variável j sempre em
            primeiro lugar, se você for montar seu próprio MO baseado nesse, em qualquer MO que você for fazer na sua vida
            inteira.
        */
        int i = 0, j = -1;
        for(auto [l, r, idx]: queries){
            while(j < r){ // coloca coisas na minha resposta e anda pra frente.
                j++;
                add(j);
            }

            while(j > r){ // remove coisas da minha resposta e anda pra trás.
                rmv(j);
                j--;
            }

            while(i > l){ // coloca coisas na minha resposta e anda pra trás.
                i--;
                add(i);
            }

            while(i < l){ // remove coisas da minha resposta e anda pra frente.
                rmv(i);
                i++;
            }

            rs[idx]=calc(); // calcula a resposta atual.
        }
    }
};
