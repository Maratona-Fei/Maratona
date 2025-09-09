//teletransporte
//
//explicacao:
//	todos os caminhos de tamanho l entre
//	nodo a e b. exponencia a matriz de adj
//	por l.
matriz matrixMultiply (const matriz& a, const matriz& b, int n) {
	matriz c(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
			}
		}
	}
	return c;
}

matriz matrixExpo (matriz& a, ll k, int n) {
	matriz res(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) res[i][i] = 1;

	while (k > 0) {
		if (k & 1) res = matrixMultiply(res, a, n);
		a = matrixMultiply(a, a, n);
		k >>= 1;
	}
	return res;
}

int main()
{
    _;

	int n, s, t;
	ll l;
	while (cin >> n >> l >> s >> t) {
		s--, t--;
		matriz adj(n, vector<int>(n));
		for (int u = 0; u < n; u++) {
			for (int j = 0; j < 4; j++) {
				int v; cin >> v; v--;
				adj[u][v]++;
			}
		}

		matriz res = matrixExpo(adj, l, n);
		cout << res[s][t] << endl;
	}
    
    return(0);
}

