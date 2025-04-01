#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

#define f first
#define s second

#define vi vector<int>
#define grafo vector<vector<int>>

#define dbg(x) cout << #x << " = " << x << endl;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

struct Edge {
	int w = INF, to = -1;
	bool operator<(Edge const& other) const {
		return make_pair(w, to) < make_pair(other.w, other.to);
	}
};

int n;
vector<vector<Edge>> adj;

void prim(){
	int total_weight = 0;

	vector<Edge> min_e(n);
	
	min_e[0].w = 0;
	set<Edge> q;

	q.insert({0, 0});

	vector<bool> selected(n, false);

	for(int i = 0; i < n; i++){
		if(q.empty()){
			cout << "IMPOSSIBLE" << endl;
			return;
		}

		int v = q.begin()->to;
		selected[v] = 1;

		total_weight += q.begin()->w;
		q.erase(q.begin());

		if(min_e[v].to != -1)
			cout << v << ' ' << min_e[v].to << endl;

		for(Edge e : adj[v]) {
			if(!selected[e.to] and e.w < min_e[e.to].w){
				q.erase({min_e[e.to].w, e.to});
				min_e[e.to] = {e.w, v};
				q.insert({e.w, e.to});
			}
		}
	}
	cout<<total_weight<<endl;
}
int main(){ _

	return 0;
}
