//the search for balance
//
//	descricao: pra todo subconjunto de indices ate n
//	ele quer saber quantos dele tem:
//	La <= soma(all(A[i])) <= Ra
//	Lb <= soma(all(B[i])) <= Rb
//
//	como n <= 40, nao da pra so testar todos os sub
//	conjuntos de toda a array, mas da pra fazer isso
//	pra no maximo uma metade dela.
//
//	(meet in the middle)
//	dai, olhando pros subconj de um lado da array,
//	preciso arranjar um jeito de contar quantos sub
//	conj do lado de la eu consigo juntar com o meu.
//
//	(prefix 2d)
//	nesse caso, preciso achar quantos do lado de la tem
//	a soma do A num range que nao estoure ou falte pra
//	estar dentro de [La, Ra] e similarmente dentro de
//	[Lb, Rb] tambem. tem jeitos mais espertos de fazer
//	(comprimir isso num array e fazer query de contagem
//	de menores), mas esse jeito eh legal: bit2d.

template<class T = ll> struct bit2d {
	vector<T> X;
	vector<vector<T>> Y, t;

	int ub(vector<T>& v, T x) {
		return upper_bound(v.begin(), v.end(), x) - v.begin();
	}
	bit2d(vector<pair<T, T>>& v) {
		for (auto [x, y] : v) X.push_back(x);
		sort(X.begin(), X.end());
		X.erase(unique(X.begin(), X.end()), X.end());

		t.resize(X.size() + 1);
		Y.resize(t.size());
		sort(v.begin(), v.end(), [](auto a, auto b) {
			return a.second < b.second; });
		for (auto [x, y] : v) for (int i = ub(X, x); i < t.size(); i += i&-i)
			if (!Y[i].size() or Y[i].back() != y) Y[i].push_back(y);

		for (int i = 0; i < t.size(); i++) t[i].resize(Y[i].size() + 1);
	}

	void update(T x, T y, T v) {
		for (int i = ub(X, x); i < t.size(); i += i&-i)
			for (int j = ub(Y[i], y); j < t[i].size(); j += j&-j) t[i][j] += v;
	}

	T query(T x, T y) {
		T ans = 0;
		for (int i = ub(X, x); i; i -= i&-i)
			for (int j = ub(Y[i], y); j; j -= j&-j) ans += t[i][j];
		return ans;
	}
	T query(T x1, T y1, T x2, T y2) {
		return query(x2, y2)-query(x2, y1-1)-query(x1-1, y2)+query(x1-1, y1-1);
	}
};

int solve() {
	int n; cin >> n;
	vector<array<int, 2>> A(n);
	for (auto& [a, b] : A) {
		cin >> a >> b;
	}
	ll mna, mnb, mxa, mxb;
	cin >> mna >> mnb >> mxa >> mxb;

	int mid = n / 2;
	vector<array<int, 2>> A1(A.begin(), A.begin() + mid), A2(A.begin() + mid, A.end());
	auto calc = [&](vector<array<int, 2>>& A) {
		int n = (int)A.size();
		vector<array<ll, 2>> R(1 << n);

		for (int i = 0; i < (1 << n); i++) {
			array<ll, 2> a = {0, 0};
			for (int j = 0; j < n; j++) if (i & (1 << j)) {
				a[0] += A[j][0];
				a[1] += A[j][1];
			}
			R[i] = a;
		}
		return R;
	};

	auto B = calc(A1), C = calc(A2);
	vector<pair<ll, ll>> BB;
	BB.reserve(C.size());

	for (auto [a, b] : C) {
		BB.emplace_back(a, b);
	}
	bit2d bit(BB);

	for (auto [a, b] : C) {
		bit.update(a, b, +1);
	}

	ll res = 0;
	for (auto [a, b] : B) {
		res += bit.query(mna - a, mnb - b, mxa - a, mxb - b);
	}
	cout << res << endl;

	return(0);
}
