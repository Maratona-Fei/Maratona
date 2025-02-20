int mul(int x, int y){
	return (1LL * x * y) % mod;
}

// Complexidade: O(logn)
int exp(int x, ll n){
	int ans = 1 % mod;

	while(n > 0){
		if(n & 1) ans = mul(x, ans);
		x = mul(x, x);
		n >>= 1;
	}
	return ans;
}
