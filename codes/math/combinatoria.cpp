// pré-calcula fatoriais e permite calcular coeficientes binomiais (n escolhe k) usando exponenciacao rapida e inverso modular

const int MAX, mod;
ll fat[MAX];

// calculo do fatorial
// complexidade: O(MAX)
void fatorial(){
    fat[0] = 1;
    for(int i = 1 ; i < MAX; i++){
        fat[i] = i * fat[i -1] % mod;
    }
}

// exponenciacao rapida
// complexidade: O(log b)
ll fexp(ll a, ll b){
    if(b == 0){
        return 1;
    }
    if(b % 2 == 0){
        return fexp(a * a % mod, b/2);
    }
    return a * fexp(a, b - 1) % mod;
}

// inverso modular
// complexidade: O(log mod)
ll inv(ll a){
    return fexp(a, mod - 2);
}

// combinacao n "escolhe" i
// complexidade: O(log mod)
ll comb(int n, int i){
    return fat[n] * inv(fat[i]) % mod * inv(fat[n - i]) % mod;
}
