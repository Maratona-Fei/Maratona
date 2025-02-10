// Complexidade: O(m log(n))

#define pp pair<ll,int>

vector<vector<pp>>g;

vector<ll> dijkstra(int s){
	// {dist, v}
	priority_queue<pp> pq;

	vector<ll> d(g.size(), LINF);
	d[s] = 0, pq.push({0, s});

	while(!pq.empty()){
		auto [dist, u] = pq.top(); pq.pop();
		if(-dist > d[u])continue;

		for(auto [v, w] : g[u]){
			int sum = d[u] + w;
			if(d[v] > sum){
				d[v] = sum;
				pq.push({-sum, v});
			}
		} 
	}	
	return d;
}
