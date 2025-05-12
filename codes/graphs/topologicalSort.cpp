// Topological Sort

// Caso exista uma ordem em um grafo direcionado 
// retorna true
// Comlexidade: O(V+E) | Spaco: O(V)

bool topoLogicalSort(vector<vector<int>>& g, vector<int>& deg){
	int n = g.size();
	
	queue<int>q;
	
	for(int i = 0; i < n; i++)
		if(deg[i] == 0) q.push(i);
	
	int idx = 0;

	order.assign(n, 0);

	while(!q.empty()){
		int v = q.front(); q.pop();
		order[idx] = v; idx++;

		for(int& viz : g[v]){
			deg[viz]--;

			if(deg[viz] == 0) q.push(viz);
		}
	}

	if(idx != n) return false;

	return true;
}
