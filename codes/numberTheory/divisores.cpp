ll numeroDeDivisores(ll num){
    ll total = 1;
    for(int i = 2 ; (ll)i * i <= num ; i++){
            if(num % i == 0){
                    int e = 0;
                    do{
                       e++;
                       num /= i;
                        }while(num % i == 0);
                        total *= e + 1;
                }
        }
        if(num > 1)
            total *= 2;
        return total;
}

//Complexidade(N^1/3)
//Nota: precisa de crivo para a execucao
int numeroDevisores(int num){
    int ans = 1;

    for(auto& p : primos){
           if(p*p*p > num) break;
           int cont = 1;
           while(num % p == 0){
                    num /= p;
                    cont++;
               }
           ans *= cont;
    }
    if(primo[num])
        ans *= 2;
    else if((int)sqrt(num) == sqrt(num) and primo[(int)sqrt(num)]){
        ans *= 3;
    }
    else if(num != 1)
        ans *= 4;
    return ans;
}

ll somaDosDivisores(ll num){
    ll total = 1;        

    for(int i = 2 ; (ll)i * i <= num ; i++){
            if(num % i == 0){
                    int e = 0; 
                    do{
                        e++;
                        num /= i;
                        }while(num % i == 0);

                    ll sum = 0 , pow = 1;
                    do{
                        sum += pow;
                        pow *= i;
                        }while(e-- > 0);
                        total *= sum;
                }
        }
        if(num > 1)
            total *= (1 + num);

        return total;
}
