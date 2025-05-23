/*
  Estrutura de Dados que consegue fazer queries em subarrays em O(1). Usa duas stacks para simular uma queue.
*/

template<class T> struct MonoQueue {
    stack<pair<T,T>> s1, s2;

    // funcao da queue monotona. min por padrão.
    T f(T a, T b) {
        return min(a,b);
    }

    void add(T x) {
        T val;
        if(s1.empty()) val = x;
        else val = f(x, s1.top().second);
        s1.push(make_pair(x, val));
    }

    T get() {
        T val;
        if(s1.empty()) val = s2.top().second;
        else if(s2.empty()) val = s1.top().second;
        else val = f(s1.top().second, s2.top().second);

        return val;
    }

    void pop() {
        if(s2.empty()){
            while(!s1.empty()){
                T el = s1.top().first;
                s1.pop();
                T val;
                if(s2.empty()) val = el;
                else val = f(el, s2.top().second);
                s2.push(make_pair(el, val));
            }
        }
 
        s2.pop();
    }
};
