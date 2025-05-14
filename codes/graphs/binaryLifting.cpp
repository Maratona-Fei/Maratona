// Binary Lifting

struct Tree {
	const int root = 0;

	const vector<vector<int>>& g;
	const int log2dist;
	vector<int> pai;
	vector<vector<int>> up;
	vector<int> dep;

	// dfs para calcular pais e profundidade de cada v
	void process(int at, int prev){
		dep[at] = dep[prev]+1;
		for(int v : g[at]){
			if(v != prev){
				process(v, at);
				pai[v] = at;
			}
		}
	}
	Tree(vector<vector<int>>& adj)
		: g(adj), log2dist(ceil(log2(adj.size()))), pai(adj.size()),
		up(pai.size(), vector<int>(log2dist+1)), dep(adj.size()) {

		pai[root] = dep[root] = -1;
		process(root, root);

		//up[n][k] contem o 2^kth pai do vertice n
		//se n tiver o 2^kth pai, o valor eh -1
		for(int n = 0; n < pai.size(); n++){up[n][0] = pai[n];}
		for(int p = 1; p <= log2dist; p++){
			for(int n = 0; n < pai.size(); n++){
				int mid = up[n][p-1];

				if(mid == -1)
					up[n][p] = -1;
				else
					up[n][p] = up[mid][p - 1];
			}
		}
	}

	int kth_parent(int n, int k){
		if(k > pai.size()){return -1;}

		int at = n;
		//vai quebrando k em potencias de 2 fznd looping pelos seus bits
		for(int pow = 0; pow <= log2dist; pow++){
			if((k & (1 << pow)) != 0){
				at = up[at][pow];

				if(at == -1) break;
			}
		}
		return at;
	}

	//retorna lca entre nodos n1 e n2
	int lca(int n1, int n2){
		if(dep[n1] < dep[n2]){return lca(n2, n1);}

		//sobe n1 ate a mesma altura n2
		n1 = kth_parent(n1, dep[n1]-dep[n2]);

		///se n2 for ancestral direto de n1
		if(n1 == n2)return n2;

		//move os vertices ate se tornarem iguais
		for(int i = log2dist; i >= 0; i--){
			if(up[n1][i] != up[n2][i]){
				n1 = up[n1][i];
				n2 = up[n2][i];
			}
		}

		//nesse ponto lcs sera o pai de qualquer vertice
		return up[n1][0];
	}
	int dist(int n1, int n2){
		return dep[n1]+dep[n2] - dep[lca(n1,n2)]*2;
	}
};
