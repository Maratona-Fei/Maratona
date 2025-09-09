///*
//distinct values queries II
//
//	descricao: pra cada query responder "YES"
//	se nenhum valor entre [l, r] tem repeticao
//	nesse range.
//
//	a ideia eh simples: pra cada valor, eu marco,
//	nele, qual a proxima ocorrencia dele no array.
//	dai, se a proxima ocorrencia de A[i] <= r, 
//	pra todo i [l, r], entao esse valor repete 
//	nessa subarray.
//
//	o problema entao eh so query de min em range e
//	update em ponto. segtree facil. mas o atualizar
//	dos "ponteiros" de next sao um porre e achei
//	que vale a pena marcar.
//	O(nlogn + qlogn)
//*/

const int MAX = 2e5+10;
namespace seg {
	int seg[4*MAX], *v;
	int n;

	int build(int p=1, int l=0, int r=n-1) {
		if (l == r) return seg[p] = v[l];
		int m = (l+r)/2;
		return seg[p] = min(build(2*p, l, m), build(2*p+1, m+1, r));
	}
	void build(int n_, int* v_) {
		n = n_, v = v_;
		build();
	}
	int query(int a, int b, int p=1, int l=0, int r=n-1) {
		if (b < l or r < a) return INF;
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return min(query(a, b, 2*p, l, m), query(a, b, 2*p+1, m+1, r));
	}
	int update(int i, int x, int p=1, int l=0, int r=n-1) {
		if (i < l or r < i) return seg[p];
		if (l == r) return seg[p] = x;
		int m = (l+r)/2;
		return seg[p] = min(update(i, x, 2*p, l, m), update(i, x, 2*p+1, m+1, r));
	}
};

int solve() {
	int n, q; cin >> n >> q;
	vector<int> A(n);

	map<int, set<int>> p;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		p[A[i]].emplace(i);
	}

	vector<int> V(n);
	for (int i = 0; i < n; i++) {
		V[i] = (*p[A[i]].rbegin() == i ? INF : *p[A[i]].upper_bound(i));
	}

	seg::build(n, V.data());

	while (q--) {
		int tp; cin >> tp;

		if (tp == 1) {
			int k, u; cin >> k >> u; k--;
			if (u == A[k]) continue;

			auto &S = p[A[k]];
			auto it = S.find(k);
			int prv = (it == S.begin() ? -1 : *prev(it));
			auto nit = next(it);
			int nxt = (nit == S.end() ? INF : *nit);

			if (prv != -1) seg::update(prv, nxt);
			seg::update(k, INF);
			S.erase(it);

			auto &S_ = p[u];
			auto it_ = S_.lower_bound(k);
			int prv_ = (it_ == S_.begin() ? -1 : *prev(it_));
			int nxt_ = (it_ == S_.end()   ? INF : *it_);

			S_.insert(k);
			if (prv_ != -1) seg::update(prv_, k);
			seg::update(k, nxt_);

			A[k] = u;
		} else {
			int l, r; cin >> l >> r; l--, r--;
			cout << (seg::query(l, r) <= r ? "NO" : "YES") << endl;
		}
	}

	return(0);
}
