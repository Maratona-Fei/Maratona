vector<ll> fac(MAX, 1), inv(MAX, 1);
// nao esquece de chamar as funcoes
ll mul(ll x, ll y, ll mod){
    return (x * y) % mod;
}

ll exp(ll x, ll n, ll mod){
    ll ans = 1 % mod;

    while(n > 0){
        if(n & 1) ans = mul(x, ans, mod);
        x = mul(x, x, mod);
        n >>= 1;
    }
    return ans;
}

void factorial(ll mod){
    fac[0] = 1;
    for(int i = 1; i < MAX; i++){
        fac[i] = mul(fac[i-1], i, mod);
    }
}

void inverses(ll mod){
    inv[MAX-1] = exp(fac[MAX-1], mod - 2, mod);
    for(int i = MAX-1; i >= 1; i--){
        inv[i-1] = mul(inv[i], i, mod);
    }
}

ll choose(ll n, ll k, ll mod){
	 return mul(mul(fac[n], inv[k], mod), inv[n-k], mod);
}
