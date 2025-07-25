// Articulation Point

// complexidade: O(V+E)
vector<vector<int>> g;
vector<int> ap, low, disc;
int Time = 0;

int dfsAP(int u, int p){
	int filhos = 0;

	low[u] = disc[u] = ++Time;

	for(int v : g[u]){
		if(v == p) continue;
		
		if(!disc[v]){ // se nao foi descoberto
			filhos++;
			dfsAP(v, u);
			
			// verifica se o filho achou um caminho com descoberta menor
			// se nao 'u' eh um AP
			if(disc[u] <= low[v]) ap[u] = 1;

			low[u] = min(low[u], low[v]);
		} 
		else {
			low[u] = min(low[u], disc[v]);
		}
	}
	return filhos;
}

void AP(){
	for(int u = 0; u < g.size(); u++)
		if(!disc[u])
			ap[u] = dfsAP(u, u) > 1; // verifica se a raiz tem dois nos
}
int main(){ _

	return 0;
}
