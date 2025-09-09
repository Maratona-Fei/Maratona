///*
//maximum building I
//
//	descricao: qual a area do maior retangulo
//	que cabe no matriz. um retangulo so cabe
//	se nao conter nenhum '*'.
//
//	tambem malandragem com stack monotonica.
//	preguica de descrever melhor. eh isso ai.
//
//	O(nm);
//*/

int solve() {
	int n, m; cin >> n >> m;
	vector<string> A(n);
	vector<vector<int>> Ha(n, vector<int>(m));
	vector<vector<int>> B(m);

	for (auto& i : A) cin >> i;
	for (int j = 0; j < m; j++) {
		for (int l = 0, r; l < n; l = r) {
			r = l + 1;
			if (A[l][j] == '*') {
				Ha[l][j] = 0;
				continue;
			}

			while (r < n and A[r][j] == '.') r++;
			for (int i = l; i < r; i++) {
				Ha[i][j] = r;
			}
		}
	}

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++) {
	//		cout << Ha[i][j] << " \n"[j == m-1];
	//	}
	//}

	int res = 0;
	for (int i = 0; i < n; i++) {
		vector<int> H(m);
		for (int j = 0; j < m; j++) {
			H[j] = max(0, Ha[i][j] - i);
		}

		stack<int> S;
		vector<int> L(m), R(m);
		for (int j = 0; j < m; j++) {
			while (S.size() and H[S.top()] >= H[j]) {
				S.pop();
			}
			L[j] = (S.size() ? S.top() : -1);
			S.push(j);
		}

		while (S.size()) S.pop();
		for (int j = m-1; j >= 0; j--) {
			while (S.size() and H[S.top()] >= H[j]) {
				S.pop();
			}
			R[j] = (S.size() ? S.top() : m);
			S.push(j);
		}

		for (int j = 0; j < m; j++) {
			res = max(res, H[j] * (R[j] - L[j] - 1));
		}

		//for (int j = 0; j < m; j++) {
		//	printf("(%d, [%d, %d]) ", H[j], L[j], R[j]);
		//}
		//printf("\n");
	}
	cout << res << endl;

	return(0);
}
