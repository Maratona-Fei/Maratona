/*
skyline photo

	descricao: qual a melhor subdivisao da array
	em subarrays tal que a o valor de cada subarray
	eh o max dela.

	malandragem usando stack monotonica nas transic
*/

int solve() {
	int n; cin >> n;
	vector<int> H(n), B(n);
	for (int& i : H) cin >> i;
	for (int& i : B) cin >> i;
	H.insert(H.begin(), 0);
	B.insert(B.begin(), 0);

	vector<ll> dp(n+1, -LINF);
	stack<array<ll, 2>> S;
	for (int i = 1; i <= n; i++) {
		ll agr = dp[i-1];
		while (S.size() and H[S.top()[0]] >= H[i]) {
			agr = max(agr, S.top()[1]);
			S.pop();
		}
		dp[i] = max((S.empty() ? B[i] : dp[S.top()[0]]), agr + B[i]);
		S.push({i, agr});
	}
	cout << dp[n] << endl;

	return(0);
}
