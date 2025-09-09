//k-th sum
//
//	descricao: pra uma array, responder qual a kesima
//	soma de A[i] + A[j] (pra todo i < j). a ideia eh
//	busca binaria + two pointers pra saber quantos 
//	pares existem tal que a soma eh < que o m da 
//	busca binaria.
//	O(nlogn);

int solve() {
	int n, k; cin >> n >> k;

	vector<int> A(n), B(n);
	for (int& i : A) cin >> i;
	for (int& i : B) cin >> i;
	sort(all(A));
	sort(all(B));

	auto da = [&](int mid) {
		ll res = 0;
		for (int l = 0, r = n-1; l < n; l++) {
			while (r >= 0 and A[l] + B[r] > mid) {
				r--;
			}
			if (r < 0) break;

			res += (r + 1);
		}
		return res >= k;
	};

	int l = A.front() + B.front(), r = A.back() + B.back(), res = r;
	while (l <= r) {
		int mid = l + (r - l) / 2;

		if (da(mid)) {
			res = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	cout << res << endl;

	return(0);
}
