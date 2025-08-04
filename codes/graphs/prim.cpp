// Prim

// o grafo deve ser bidirecional

// complexidade: o(mlogn)

struct edge {
	int w = INF, to = -1;
	bool operator<(const edge& other) const{
		return make_pair(w, to) < make_pair(other.w, other.to);
	}
};

int prim(vector<vector<edge>> g){
	int n = g.size(), cost = 0;

	vector<edge> min_e(n);
	
	vector<pair<int,int>> mst;

	min_e[0].w = 0;
	set<edge> q;
	q.insert({0, 0});

	vector<int> flg(n);

	for(int i = 0; i < n; i++){
		if(q.empty()) { 
			cout<<"nao tem mst"<<endl;
			return -1;
		}

		int v = q.begin()->to;
		flg[v] = 1;
		cost += q.begin()->w;
		q.erase(q.begin());

		if(min_e[v].to != -1) mst.push_back({v, min_e[v].to});
		
		for(edge e : g[v]) {
			if(!flg[e.to] and e.w < min_e[e.to].w) { 
				q.erase({min_e[e.to].w, e.to});
				min_e[e.to] = {e.w, v};
				q.insert({e.w, e.to});
			}
		}
	}
	return cost;
}
