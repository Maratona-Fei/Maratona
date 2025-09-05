/*
maximum manhattan distances

	descricao: eh isso ai. O(n)
*/

int solve() {
	int n; cin >> n;
 
	ll max_soma = -INF, min_soma = INF, max_dif = -INF, min_dif = INF;
	for (ll i = 0, x, y; i < n; i++) {
		cin >> x >> y;
		ll soma = x + y, dif = x - y;
		max_soma = max(max_soma, soma);
		min_soma = min(min_soma, soma);
		max_dif = max(max_dif, dif);
		min_dif = min(min_dif, dif);
		cout << max(max_soma - min_soma, max_dif - min_dif) << endl;
	}
 
	return(0);
}
