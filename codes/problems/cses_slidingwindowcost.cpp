/*
sliding window cost

	descricao: pra toda subarray de tamanho k,
	sabendo que pago 1 pra subtrair 1 de A[i] ou
	somar 1 em A[i], responder quanto tenho que 
	pagar pra transformar toda a subarray em um
	valor so.

	eh resultado conhecido que a resposta otima
	acontece quando o valor escolhido pra ser o
	unico que acontece na array eh a mediana dela.

	entao o problema se resume em responder a soma,
	pra toda subarray de: abs(mediana - A[i]) pra
	todo i em [l, r].

	a ideia eh que, pra todo valor < mediana, eu
	posso resumir abs(mediana - A[i]) como sendo
	mediana * (quantos desse existem) - soma dos
	menores. isso eh facil de responder com Bit.

	pra valores > mediana, da pra fazer algo parecido.
	O(nlogn)
*/

struct Bit {
	int n;
	vector<ll> bit;
	Bit(int _n=0) : n(_n), bit(n + 1) {}
	Bit(vector<int>& v) : n(v.size()), bit(n + 1) {
		for (int i = 1; i <= n; i++) {
			bit[i] += v[i - 1];
			int j = i + (i & -i);
			if (j <= n) bit[j] += bit[i];
		}
	}
	void update(int i, ll x) {
		for (i++; i <= n; i += i & -i) bit[i] += x;
	}
	ll pref(int i) {
		ll ret = 0;
		for (i++; i; i -= i & -i) ret += bit[i];
		return ret;
	}
	ll query(int l, int r) {
		return pref(r) - pref(l - 1); 
	}
};
 
int solve() {
	int n, k; cin >> n >> k;
 
	vector<int> A(n);
	for (int& i : A) cin >> i;
 
	vector<int> B(A);
	sort(all(B));
	B.erase(unique(all(B)), B.end());
	for (int& i : A) i = lower_bound(all(B), i) - B.begin();
	int m = B.size();
 
	ordered_multiset<int> O; 
 
	Bit bit_c(m), bit_s(m);
 
	auto add = [&](int i) {
		O.insert({A[i], i});
		bit_c.update(A[i], +1);
		bit_s.update(A[i], +B[A[i]]);
	};
	auto rem = [&](int i) {
		O.erase({A[i], i});
		bit_c.update(A[i], -1);
		bit_s.update(A[i], -B[A[i]]);
	};
	auto calc = [&]() -> long long {
		int mi = O.find_by_order((k - 1) / 2)->first;
		ll med = B[mi];
 
		ll menores_c = bit_c.pref(mi - 1);
		ll menores_s = bit_s.pref(mi - 1);
		ll res = menores_c * med - menores_s;
 
		ll maiores_c = bit_c.query(mi + 1, m - 1);
		ll maiores_s = bit_s.query(mi + 1, m - 1);
		res += maiores_s - med * maiores_c;
 
		return res;
	};
 
	for (int i = 0; i < k; i++) {
		add(i);
	}
 
	vector<ll> R = {calc()};
	for (int i = k; i < n; i++) {
		rem(i-k);
		add(i);
		R.push_back(calc());
	}
 
	for (ll i : R) cout << i << ' '; cout << endl;
 
	return(0);
}
