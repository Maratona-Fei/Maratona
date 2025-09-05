/*
beautiful pairs

	descricao: pra queries [l, r], responder
	quanto eh a soma das distancias de pares
	adjascentes de valores iguais.

	entao se A[i] = A[j] = A[k], responder:
	abs(i - j) + abs(j - k)

	da pra resolver com algoritmo de mo. sorta
	do jeito de mo e depois mantem a sliding
	window das posicoes de cada valor.
*/

const int tam = 400;
int solve() {
	int n, q; cin >> n >> q;
	vector<int> A(n);
	for (int& i : A) cin >> i;

	vector<int> B(A);
	sort(all(B));
	B.erase(unique(all(B)), B.end());
	for (int& i : A) i = lower_bound(all(B), i) - B.begin();
	int m = (int)B.size();

	vector<array<int, 3>> Q(q);
	for (int i = 0, l, r; i < q; i++) {
		cin >> l >> r; l--, r--;
		Q[i] = {l, r, i};
	}

	int tam = ceil(sqrt(n));
	sort(all(Q), [&tam](auto& a, auto& b) {
		if (a[0] / tam != b[0] / tam) return a[0] < b[0];
		if ((a[0] / tam) % 2) return a[1] > b[1];
		return a[1] < b[1];
	});

	vector<deque<int>> P(m);
	vector<ll> S(m, 0);

	ll res = 0;
	auto addl = [&](int i) {
		res += S[A[i]] - (ll(P[A[i]].size()) * i);
		P[A[i]].push_front(i);
		S[A[i]] += i;
	};
	auto reml = [&](int i) {
		res -= S[A[i]] - (ll(P[A[i]].size()) * i);
		P[A[i]].pop_front();
		S[A[i]] -= i;
	};
	auto addr = [&](int i) {
		res += (ll(P[A[i]].size()) * i) - S[A[i]];
		P[A[i]].push_back(i);
		S[A[i]] += i;
	};
	auto remr = [&](int i) {
		res -= (ll(P[A[i]].size()) * i) - S[A[i]];
		P[A[i]].pop_back();
		S[A[i]] -= i;
	};

	vector<ll> R(q);
	int cl = 0, cr = -1;
	for (auto [l, r, id] : Q) {
		while (cr < r) addr(++cr);
		while (cl > l) addl(--cl);
		while (cr > r) remr(cr--);
		while (cl < l) reml(cl++);
		R[id] = res;
	}

	for (ll i : R) {
		cout << i << endl;
	}

	return(0);
}
