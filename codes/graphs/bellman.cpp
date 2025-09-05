// bellman ford
//
// menor caminho de src pra todos. pode usar aresta
// negativa. cic[u] eh 1 sse u pertence a um ciclo
// negativo.
//
// complexidade: o(nm);

int n, m;
vector<vector<int>> g(n);
vector<tuple<int, int, int>> ar(m);

auto bellman = [&](int in) {
	vector<ll> d(n, LINF), cic(n, 0); d[in] = 0;
	for (int i = 0; i <= n; i++) {
		for (auto [u, v, w] : ar) {
			if (d[u] != LINF and d[u] + w < d[v]) {
				if (i < n) d[v] = d[u] + w;
				else cic[v] = 1;
			}
		}
	}

	function<void(int)> dfs = [&](int u) {
		cic[u] = 1;
		for (int v : g[u]) {
			if (cic[v]) continue;
			dfs(v);
		}
	};

	for (int i = 0; i < n; i++) {
		if (cic[i]) {
			dfs(i);
		}
	}
};
bellman(0);
