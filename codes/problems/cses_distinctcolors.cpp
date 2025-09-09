///*
//distinct colors
//
//	descricao: pra cada nodo em uma arvore, responder
//	a quantidade de 
//
//	versao 1:
//
//	maneiro porque dsu on tree.
//	comeco das folhas e vou subindo unindo filhos de um
//	vertice escolhendo migrar valores do filho menos
//	pesado.
//	O(nlog^2(n)) porque tem o set.
//*/
int solve() {
	int n; cin >> n;
	vector<vector<int>> G(n);
 
	vector<int> A(n), id(n);
	vector<set<int>> S(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		S[i].insert(A[i]);
		id[i] = i;
	}
 
	for (int i = 0, u, v; i < n-1; i++) {
		cin >> u >> v; u--, v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
 
	function<int(int, int)> merge = [&](int a, int b) {
		if (S[a].size() < S[b].size()) swap(a, b);
		for (int i : S[b]) S[a].insert(i);
		S[b].clear();
		return a;
	};
 
	vector<int> R(n);
	function<int(int, int)> dfs = [&](int u, int p) {
		int c = u;
		for (int v : G[u]) if (v != p) {
			c = merge(c, dfs(v, u));
		}
		R[u] = S[c].size();
		return c;
	};
 
	dfs(0, -1);
	for (int i : R) cout << i << ' '; cout << endl;
 
	return(0);
}

/*
	versao 2:
	
	maneiro por duas coisas:
	1. linearizacao da arvores com euler tour.
	se voce marca o tempo de entrada de um vertice u eu L[u]
	e o de saida em R[u], entao todos os nodos em [L[u], R[u]]
	nesse vetor pertencem a subarvore de u.

	2. pra fazer query de distinto em range, da pra usar ordenar
	e com ordered set pra saber quantos valores tem a sua ultima
	ocorrencia depois do meu L[u].

	O(nlogn)
*/
int solve() {
	int n; cin >> n;
	vector<vector<int>> g(n);
	vector<int> cor(n);

	for (int& i : cor) cin >> i;
	for (int i = 0, u, v; i < n-1; i++) {
		cin >> u >> v; u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	int t = 0;
	vector<int> tin(n), tout(n), euler(n);
	vector<vector<int>> fins(n);
	function<void(int, int)> dfs = [&](int u, int p) {
		tin[u] = t, euler[t++] = u;
		for (int v : g[u]) if (v != p) {
			dfs(v, u);
		}
		fins[t-1].push_back(u);
		tout[u] = t-1;
	};
	dfs(0, -1);

	vector<int> res(n);
	ordered_set us;
	map<int, int> ult;
	for (int i = 0; i < n; i++) {
		if (ult.count(cor[euler[i]])) {
			us.erase(ult[cor[euler[i]]]);
		}
		us.insert(ult[cor[euler[i]]] = i);

		for (int u : fins[i]) {
			res[u] = (int)us.size() - us.order_of_key(tin[u]);
			//dbg(u);
		}
	}
	for (int i : res) cout << i << ' '; cout << endl;

	return(0);
}
