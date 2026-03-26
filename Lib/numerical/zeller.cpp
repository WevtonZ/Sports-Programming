/**
 * Congruencia de Zeller
 * 
 * d = dia do ano
 * m = mes do ano
 * y = ano do ano
 * 
 * k = dois ultimos digitos do ano
 * j = seculo do ano. aceita que esse funciona.
 * 
 * Essencialmente, esse negócio aqui eh tipo, tu da uma data e ele retorna um id, e esse id diz o dia da semana quando tomado %7.
 * Deve dar pra fazer tipo, dado um id, retornar a data exata, mas to com preguiça
 */
ll zeller(ll d, ll m, ll y) {
    if (m < 3) y--, m += 12;
    ll k=y%100;
    ll j=y/100;
    return d+(((m+1)*26)/10)+k+(k/4)+(j/4)+5*j;
}
