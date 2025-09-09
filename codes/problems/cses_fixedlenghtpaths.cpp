//fixed-lenght paths I
//
//	descricao: pra uma arvore, responder quantos caminhos
//	simples e distintos de tamanho k existem.
//
//	a ideia eh divide and conquer em arvore. divido o 
//	grafo no meio (no centroide) e, pra cada um desses 
//	cetroides, responder quantos caminhos de tamanho k
//	passam por ele.
//	O(nlogn)

const int MAX = 2e5+10;
vector<int> g[MAX];
vector<int> dists;
int foi[MAX], ver[MAX], sub[MAX], cont[MAX];
int n, k, t = 0, m, res_cen;
ll res = 0;
 
void dfs_tam(int u, int p) {
	m++;
	for (int v : g[u]) if (v != p and !foi[v]) {
		dfs_tam(v, u);	
	}
}
 
int dfs_cen(int u, int p) {
	sub[u] = 1;
	for (int v : g[u]) if (v != p and !foi[v]) {
		sub[u] += dfs_cen(v, u);
	}
	
	int ok = (m - sub[u] <= m/2);
	for (int v : g[u]) if (v != p and !foi[v]) {
		ok &= (sub[v] <= m/2);
	}
	if (ok) res_cen = u;
 
	return sub[u];
}
 
int centroid(int u, int p) {
	res_cen = -1, m = 0;
	dfs_tam(u, p);
	dfs_cen(u, p);
	return res_cen;
}
 
void dfs_dis(int u, int p, int d) {
	if (d > k) return;
	dists.push_back(d);
	for (int v : g[u]) if (v != p and !foi[v]) {
		dfs_dis(v, u, d+1);
	}
}
 
void f(int u, int p) {
	auto cen = centroid(u, p);
	foi[cen] = 1;
 
	ver[0] = ++t;
	cont[0] = 1;
	for (int U : g[cen]) {
		if (foi[U]) continue;
 
		dists.clear();
		dfs_dis(U, cen, 1);
		for (int d : dists) {
			if (k - d < 0) continue;
			res += (ver[k-d] == t ? cont[k-d] : 0LL);
		}
 
		for (int d : dists) {
			if (ver[d] != t) {
				ver[d] = t;
				cont[d] = 1;
			} else {
				cont[d]++;
			}
		}
	}
 
	for (int U : g[cen]) {
		if (!foi[U]) {
			f(U, cen);
		}
	}
}
 
int solve() {
	cin >> n >> k;
	for (int i = 0, u, v; i < n-1; i++) {
		cin >> u >> v; u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
 
	f(0, -1);
	cout << res << endl;
 
	return(0);
}
