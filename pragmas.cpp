/*
Necessário explicar os pragmas:
  * O3 e unroll-loops servem para o código ser trocado para outros tipos de instruções. Isso aumenta o tamanho do código de máquina gerado, mas tira
  uma parte da lógica que antes estava sendo usada, como por exemplo, loops simples agora viram n coisas simples.

  * Quando falamos da parte de hardware, usamos o target ali. Todos eles são focados em manipulação de bits, e a ideia é que a gente ativa um monte deles pra acelerar/
  mudar a forma como algumas coisas são calculadas, delegando pra outros componentes do computador fazerem as contas, e aí fica mais rápido fazer operações binárias.
*/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
