// Strongly Connected Components and Condensation Graph

#define vi vector<int>
vi vis;

// dfs para armezar nos dps de 
// visitar os vizinhos
void dfs(int v, vector<vi>& g, vi& output){
	vis[v] = 1;

	for(int u : g[v]){
		if(!vis[u]) 
			dfs(u, g, output);
	}
	output.push_back(v);
}

// comps -- componentes do SCCs em g
// g_cond -- grafo condensado dos SCCs

// complexidade: O(n + e)
void scc(vector<vi>& g){
	int n = g.size();
	
	vi order; // vector ordenado dos vertices de acordo
				// com o tempo de saida
	
	vis.assign(n, 0);
	
	vector<vi> comps, g_cond;

	// primeiro dfs nas raizes
	for(int i = 0; i < n; i++)
		if(!vis[i]) 
			dfs(i, g, order);
	
	// criando o G^T
	// g com arestas invertidas
	vector<vi> g_rev(n);
	for(int v = 0; v < n; v++)
		for(int u : g[v])
			g_rev[u].push_back(v);

	vis.assign(n, 0);
	reverse(order.begin(), order.end());

	vi roots(n, 0); // vector q fornece a raiz 
					// para os vertices de cada SCC
	
	// segundo dfs
	for(auto v : order)
		if(!vis[v]){
			vi comp;
			dfs(v, g_rev, comp);
			comps.push_back(comp);
			
			int root = *min_element(comp.begin(), comp.end());
			
			for(auto u : comp) roots[u] = root;

		}

	// adiciona arestas para o G condensado
	g_cond.assign(n, {});
	for(int v = 0; v < n; v++)
		for(auto u : g[v])
			if(roots[v] != roots[u])
				g_cond[roots[v]].push_back(roots[u]);
}
