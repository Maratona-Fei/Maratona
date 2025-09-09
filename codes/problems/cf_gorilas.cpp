///*
//gorillas
//
//explicacao:
//	atualiza todos os quadrados de tamanho k
//	em uma matriz maior. legal porque da pra 
//	atualizar um retangulo todo em o(1).
//
//	um exemplo de como usar difference array em range.
//*/
void solve() {
    int n, m, k; cin >> n >> m >> k;
	int w; cin >> w;
    vector<int> v(w);
    for (int& i : v) cin >> i;
    sort(v.rbegin(), v.rend());
    
    vector<vector<ll>> cont(n + 1, vector<ll>(m + 1, 0));
    for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j + k <= m; j++) {
            cont[i][j]++;
            cont[i + k][j]--;
            cont[i][j + k]--;
            cont[i + k][j + k]++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0) cont[i][j] += cont[i - 1][j];
            if (j > 0) cont[i][j] += cont[i][j - 1];
            if (i > 0 && j > 0) cont[i][j] -= cont[i - 1][j - 1];
        }
    }

    priority_queue<ll> pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pq.push(cont[i][j]);
        }
    }

    ll res = 0;
	for (int i : v) {
		res += (ll)i * (ll)pq.top();
		pq.pop();
	}
    
    cout << res << endl;
}
