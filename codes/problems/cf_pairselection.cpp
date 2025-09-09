///*
//pair selection
//
//	descricao: pra um conjunto de pares (a, b)
//	responder qual a maior possivel valor de um
//	subconjunto desses pares desse jeito:
//	(ai + a_i+1 + ... + an) /
//	(bi + b_i+i + ... + bn)
//*/

int solve() {
	int n, k; cin >> n >> k;
	vector<int> A(n), B(n);

	for (int i = 0; i < n; i++) {
		cin >> A[i] >> B[i];
	}

	auto da = [&](double mid) {
		vector<double> C(n);
		for (int i = 0; i < n; i++) {
			C[i] = A[i] - mid * B[i];
		}
		sort(all(C)); reverse(all(C));

		return accumulate(C.begin(), C.begin() + k, 0.0) >= 0.0;
	};

	double l = 0, r = 1e12;
	for (int i = 0; i < 100; i++) {
		double mid = (l + r) / 2.0;

		if (!da(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << fixed << setprecision(13) << l << endl;

	return(0);
}
