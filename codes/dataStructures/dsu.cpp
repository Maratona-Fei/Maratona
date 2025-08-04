// DSU

// combina quaisquer dois conjuntos
// unite(a, b) -- fundi o conj em que 'a' esta e o em que 'b' esta
// find(v) -- retorna a raiz (representante) de v

// complexidade: O(1) amortizado

struct DSU{
	vector<int> id, size;

	DSU(int n) : id(n), size(n) {iota(id.begin(), id.end(), 0);} 

	int find(int v){
		if(v == id[v]) return v;
		return id[v] = find(id[v]);
	}

	void unite(int a, int b){
		a = find(a), b = find(b);
		if(a != b) 
			if(size[a] < size[b]) swap(a, b);
		id[b] = a;
		size[a] += size[b];
	}
};
