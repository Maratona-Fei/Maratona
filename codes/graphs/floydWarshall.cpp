// Floyd Warshall

// Complexidade: O(n^3)
// Lembrar de receber arestas no padrao
// d[v][u] = d[u][v] = min(d[v][u], (ll)c);
const int MAX = 500;
vector<vector<ll>> d(MAX+10, vector<ll>(MAX+10, LINF));

void floyd(int n){
	for(int i = 0; i < n; i++) d[i][i] = 0;

	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				// Considera arestas com peso neg
				if(d[i][k] < LINF and d[k][j] < LINF)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
