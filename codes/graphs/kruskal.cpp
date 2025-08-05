// Kruskal

// precisa do DSU
// complexidade: O(mlogn)

struct edge {
	int u, v, w;

	bool operator<(edge const& other){
		return w < other.w;
	}
};


int kruskal(vector<edge>& g, int n){
	DSU dsu(n);

	int cost = 0;

	vector<edge> mst;

	sort(g.begin(), g.end());

	for(edge e : g){
		if(dsu.find(e.u) != dsu.find(e.v)){
			cost += e.w;
			mst.push_back(e);
			dsu.unite(e.u, e.v);
		}
	}

	return cost;
}
