// Bridges

// complexidade: O(V+E)
vector<vector<int>> g;
vector<int> low, disc;
vector<pair<int,int>> br;
int Time = 0;

void dfsAP(int u, int p){
	low[u] = disc[u] = ++Time;

	for(int v : g[u]){
		if(v == p) continue;
		
		if(!disc[v]){ // se nao foi descoberto
			dfsAP(v, u);
			
			// verifica se o filho achou um caminho com descoberta menor
			// se nao 'u' eh uma ponte
			if(disc[u] < low[v]) br.push_back({u, v});

			low[u] = min(low[u], low[v]);
		} 
		else {
			low[u] = min(low[u], disc[v]);
		}
	}
}

void BR(){
	for(int u = 0; u < g.size(); u++)
		if(!disc[u])
			dfsAP(u, u); 
}
