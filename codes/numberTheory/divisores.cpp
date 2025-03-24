//Complexidade(N^1/3)
//Nota: precisa de crivo para a execucao
int numeroDivisores(int num){
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

// Complexidade: O(sqrt(num))
ll numberOfDivisors(ll num){
	ll total = 1;

	for(int i = 2; (ll)i*i <= num; i++){
		if(num % i == 0){
			int e = 0;
			do{
				e++;
				num /= i;
			} while(num % i == 0);
			total *= e + 1;
		}
	}
	if(num > 1) total *= 2;

	return total;
}

// Soma de todos os divisores de num
// Complexidade: O(sqrt(num))
ll sumOfDivisors(ll num){
	ll total = 1;

	for(int i = 2; (ll)i*i <= num; i++){
		if(num % i == 0){
			int e = 0;

			do{
				e++;
				num /= i;
			} while(num % i == 0);

			ll sum = 0, pow = 1;
			
			do{
				sum += pow;
				pow *= i;
			} while(e-- > 0);
			
			total *= sum;
		}
	}

	if(num > 1) total *= (1 + num);

	return total;
}

const int two_mod_inv = 500000004;

ll total_sum(ll start, ll end){
	return ((((end - start + 1) % mod) * ((start + end) % mod) % mod) * two_mod_inv % mod);
}
// Soma dos divisores de 1 a n
// Complexidade: O(confia)
ll sum_divisors(ll n){
	ll total = 0;

	ll at = 1;

	while (at <= n) {

		ll add_amt = n / at;  // Our divisor to process

		// The largest number that still has the same value of q

		ll last_same = n / add_amt;

		total = (total + add_amt * total_sum(at, last_same)) % mod;

		at = last_same + 1;

	}

	return total;
}
