/*
berntown roads

explicacao:
	transforme um grafo nao direcionado em um
	direcionado mas o mantenha conexo (da pra
	ir de qualquer um pra qualquer outro. o
	mais importante aqui sao os bridges. uma
	bridge eh um vertice que, se tirado, 
	aumenta o numero de componentes conexos).
*/
int main()
{
    _;
	// todas as span-edges vao pra baixo e as back-edges pra cima. 
	// mas se tiver alguma bridge eh impossivel.

	int n, m; cin >> n >> m;
	map<pair<int, int>, int> ed;
	vector<vector<int>> g(n);
	for (int i = 0, u, v; i < m; i++) {
		cin >> u >> v; u--, v--;
		g[u].push_back(v);	
		g[v].push_back(u);	
		ed[ii(u, v)] = 0;
	}

	int cont = 0;
	vector<int> dp(n, 0), d(n, -1); d[0] = 0;
	function<void(int)> bridge = [&](int u) {
		for (int v : g[u]) {
			if (d[v] == -1) {
				d[v] = d[u] + 1;
				bridge(v);
				dp[u] += dp[v];
				if (ed.count(ii(u, v))) ed[ii(u, v)] = 1;
				else ed[ii(v, u)] = 1;
			} else if (d[v] < d[u]) {
				dp[u]++;
			} else if (d[v] > d[u]) {
				dp[u]--;
			}
		}

		dp[u]--;
		if (d[u] and !dp[u]) cont++;
	};
	bridge(0);

	if (cont) return cout << 0 << endl, 0;

	for (auto& [p, dir] : ed) {
		int baixo = (d[p.f] < d[p.s] ? p.f : p.s), alto = baixo ^ p.f ^ p.s;
		int a = (dir ? baixo : alto), b = a ^ p.f ^ p.s;
		a++, b++;

		cout << a << ' ' << b << endl;
	}
    
    return(0);
}

