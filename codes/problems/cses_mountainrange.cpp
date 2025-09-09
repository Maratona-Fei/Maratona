//mountain range
//
//	descricao: ele quer saber, dado um array, qual
//	o maior "caminho" que pode ser feito comecando
//	de qualquer ponto do array. mas tu so pode sair
//	de i e ir pra j sse A[i] > A[j].
//
//	aqui cabem duas ideias legais:
//	1. pra cada posicao i, eu desenho uma aresta de
//	i pro primeiro valor a direita de i que eh maior
//	que eu. faco o mesmo pra esquerda. isso da pra
//	computar rapido com stack monotonica e nao 
//	precisa de muito esforco pra se convencer que 
//	isso eh otimo.
//
//	2. agora, no grafo construido, basta computar o
//	maior caminho dado. como o grafo eh uma dag, esse
//	eh um problema manjado de dp em ordem topologica.
//	O(n)

int solve() {
	int n; cin >> n;
	vector<int> h(n);
	for (int& i : h) cin >> i;
 
	vector<vector<int>> g(n);
	vector<int> peso(n, 0), vis(n, 0), dp(n, 1);
	stack<int> s;
	for (int i = 0; i < n; i++) {
		while (s.size() and h[s.top()] <= h[i]) {
			s.pop();
		}
 
		if (s.size()) {
			g[s.top()].push_back(i);
			peso[i]++;
		}
		s.push(i);
	}
 
	while (s.size()) s.pop();
	for (int i = n-1; i >= 0; i--) {
		while (s.size() and h[s.top()] <= h[i]) {
			s.pop();
		}
 
		if (s.size()) {
			g[s.top()].push_back(i);
			peso[i]++;
		}
		s.push(i);
	}
 
	function<void(int)> dfs = [&](int u) {
		vis[u] = 1;
 
		for (int v : g[u]) {
			dp[v] = max(dp[v], dp[u] + 1);
			if (--peso[v] == 0) dfs(v);
		}
	};
 
	for (int i = 0; i < n; i++) {
		if (!vis[i] and !peso[i]) {
			dfs(i);
		}
	}
	cout << *max_element(dp.begin(), dp.end()) << endl;
 
	return(0);
}
 
int main()
{
    _;
 
	int t = 1; //cin >> t;
	while (t--) {
		solve();
	}
    
    return(0);
}
