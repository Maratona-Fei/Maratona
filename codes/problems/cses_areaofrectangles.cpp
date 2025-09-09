//area of rectangles
//
//	descricao: pra um conjunto de retangulos dados,
//	computar qual a area da uniao deles.
//
//	a ideia eh que da pra sweepar em alguma direcao.
//	dai, pra cada linha desse sweep (no maximo 1e6)
//	da pra manter uma seg de "celulas ativas" (celu
//	las que pertencem a pelo menos um retangulo) e
//	fazer uma query pra saber quantas delas nao tao
//	sendo cobertas.
//
//	eh query de min e contagem de min em range. aula
//	1 de segtree do brunomont.
//	O(nlogn)

const int MAX = 2e6+10;
namespace seg {
	struct nodo {
		ll mn, cont;
		nodo() : mn(LLONG_MAX), cont(0) {};
		nodo(ll x) : mn(x), cont(1) {};
		nodo(ll a, ll b) : mn(a), cont(b) {};
		friend nodo operator +(nodo a, nodo b) {
			if (a.mn == b.mn) return nodo(a.mn, a.cont + b.cont);
			if (a.mn < b.mn) return a;
			return b;
		};
	};
	nodo seg[4*MAX];
	ll lazy[4*MAX];
	int n, *v;

	nodo build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) return seg[p] = nodo(0);
		int m = (l+r)/2;
		return seg[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void build_(int n2) {
		n = n2;
		build();
	}
	void prop(int p, int l, int r) {
		seg[p].mn += lazy[p];
		if (l != r) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	nodo query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) return seg[p];
		if (b < l or r < a) return nodo();
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}
	nodo update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] += x;
			prop(p, l, r);
			return seg[p];
		}
		if (b < l or r < a) return seg[p];
		int m = (l+r)/2;
		return seg[p] = update(a, b, x, 2*p, l, m) + update(a, b, x, 2*p+1, m+1, r);
	}
};

vector<pair<int, int>> I[MAX], F[MAX];

int solve() {
	int n; cin >> n;
	ll m = 0;

	vector<array<int, 4>> A(n);
	for (auto& [x1, y1, x2, y2] : A) {
		cin >> x1 >> y1 >> x2 >> y2;

		if (y2 < y1) {
			swap(x1, x2);
			swap(y1, y2);
		}

		x1 += 1e6, x2 += 1e6;
		y1 += 1e6, y2 += 1e6;
		I[y1].push_back(minmax(x1, x2));
		F[y2].push_back(minmax(x1, x2));
		m = max({m, ll(x1), ll(x2)});
	}

	seg::build_(m);

	ll res = 0;
	for (int i = 0; i < MAX; i++) {
		for (auto [l, r] : I[i]) {
			seg::update(l, r-1, +1);
		}
		for (auto [l, r] : F[i]) {
			seg::update(l, r-1, -1);
		}

		auto [mn, cont] = seg::query(0, m-1);
		res += m - (!mn ? cont : 0);
	}
	cout << res << endl;

	return(0);
}
