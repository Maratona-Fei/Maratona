// antidfs
//
// dfs no grafo complementar de um grafo dado.
// ou seja, a presenca de (u, v) em g_ significa que
// a aresta (u, v) nao existe no grafo.
// 
// grafo tem que ser vector<set<int>> pra suportar
// upper_bound e erase.
//
// o((n + m)logn);

vector<set<int>> g_;
set<int> unvis;
for (int i = 0; i < n; i++) {
	unvis.emplace(i);
}

function<void(int)> dfs = [&](int uu) {
	stack<int> s; s.push(uu);

	while (s.size()) {
		int u = s.top(); s.pop();
		int ult = -1;
		for (int v : g_[u]) {
			auto it = unvis.upper_bound(ult);
			while (it != unvis.end() && *it < v) {
				int w = *it;
				it = unvis.erase(it);
				s.push(w);
			}
			ult = v;
		}

		if (ult < n - 1) {
			auto it = unvis.upper_bound(ult);
			while (it != unvis.end()) {
				int w = *it;
				it = unvis.erase(it);
				s.push(w);
			}
		}
	}
};

while (unvis.size()) {
	int u = *unvis.begin();
	unvis.erase(unvis.begin());
	dfs(u);
}
