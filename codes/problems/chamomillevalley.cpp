//chamomile valley
//
//	responder, pra cada vertice, qual a ponte mais proxima dele
//	particularmente, qual a ponte que passa em qualquer caminho
//	simples (1, n).
//
//	marca todas as pontes e depois gera uma arvore onde os nodos
//	sao tipo blocos da block cut tree mas as arestas sao pontes.
//
//	dai as pontes que importam sao as pontes do caminho (1, n)
//	nessa nova arvore gerada.

int solve() {

	int n, m; cin >> n >> m;
	vector<vector<array<int, 2>>> G(n);
	vector<array<int, 2>> E(m);

	for (int i = 0, u, v; i < m; i++) {
		cin >> u >> v; u--, v--;
		G[u].push_back({v, i});
		G[v].push_back({u, i});
		E[i] = {u, v};
	}

	int t = 0;
	stack<int> S;
	vector<int> id(n, 0), vis(n, 0), ponte(m, 0);
	function<int(int, int)> dfs = [&](int u, int pe) {
		int lo = id[u] = t++;
		S.push(u);	
		vis[u] = 2;

		for (auto [v, e] : G[u]) if (e != pe) {
			if (!vis[v]) {
				int lo_ = dfs(v, e);
				if (lo_ > id[u]) ponte[e] = 1;
				lo = min(lo, lo_);
			} else if (vis[v] == 2) {
				lo = min(lo, id[v]);
			}
		}

		if (lo == id[u]) while (1) {
			int a = S.top(); S.pop();
			vis[a] = 1;
			if (a == u) break;
		}

		return lo;
	};
	dfs(0, -1);

	t = 0;
	vector<int> comp(n, -1);
	function<void(int)> dfs2 = [&](int u) {
		comp[u] = t;
		for (auto [v, e] : G[u]) if (comp[v] == -1 and !ponte[e]) {
			dfs2(v);
		}
	};

	for (int u = 0; u < n; u++) if (comp[u] == -1) {
		dfs2(u);
		t++;
	}

	vector<vector<array<int, 2>>> G2(t);
	for (int e = 0; e < m; e++) if (ponte[e]) {
		auto [a, b] = E[e];
		if (comp[a] != comp[b]) {
			G2[comp[a]].push_back({comp[b], e});
			G2[comp[b]].push_back({comp[a], e});
		}
	}

	vector<int> P(t, -1), Pe(t, -1);
	function<void(int, int)> dfs3 = [&](int u, int p) {
		for (auto [v, e] : G2[u]) if (v != p) {
			P[v] = u;
			Pe[v] = e;
			dfs3(v, u);
		}
	};
	dfs3(comp[0], -1);

	set<array<int, 3>> pq;
	vector<int> importa(m, 0);
	for (int u = comp[n-1]; u != comp[0]; u = P[u]) {
		importa[Pe[u]] = 1;
	}

	for (int i = 0; i < m; i++) if (importa[i]) {
		auto [a, b] = E[i];
		pq.insert({0, i, a});
		pq.insert({0, i, b});
	}

	vector<int> R(n, -1), RD(n, INT_MAX);
	while (pq.size()) {
		auto [d, val, u] = *pq.begin();
		pq.erase(*pq.begin());

		if (d > RD[u]) continue;
		if (d == RD[u] and val >= R[u] and R[u] != -1) continue;
		RD[u] = d;
		R[u] = val + 1;

		for (auto [v, e] : G[u]) {
			if (d + 1 < RD[v] or (d + 1 == RD[v] and (R[v] == -1 or val < R[v]))) {
				pq.insert({d + 1, val, v});
			}
		}
	}

	int q; cin >> q;
	while (q--) {
		int u; cin >> u; u--;
		cout << R[u] << ' ';
	}
	cout << endl;

	return(0);
}
