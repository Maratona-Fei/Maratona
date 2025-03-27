// Complexidade: construtor - O(|s|) | operator() - O(1)
// fonte: github - brunomont

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

int uniform(int l, int r){
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

struct str_hash {
	static int P;
	vector<ll> h, p;

	str_hash(string& s) : h(s.size()), p(s.size()) {
		p[0] = 1, h[0] = s[0];
		for(int i = 1; i < s.size(); i++)
			p[i] = p[i - 1]*P%mod, h[i] = (h[i - 1]*P + s[i])%mod;
	}
	ll operator()(int l, int r){ // retorna hash s[l...r]
		ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%mod : 0);
		return hash < 0 ? hash + mod : hash;
	}
};
int str_hash::P = 277;
