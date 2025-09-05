// prefix 2d
// 
// query estatica do retangulo (i, j) (ii, jj)

struct pre2d {
	int n, m;
	vector<vector<ll>> pre;

	pre2d(vector<vector<int>> a) : n(a.size()), m(a[0].size()), pre(n+1, vector<ll>(m+1)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				pre[i][j] = a[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
			}
		}
	}

	ll query(int i, int j, int ii, int jj) { // 1-based
		return pre[ii][jj] - pre[ii][j-1] - pre[i-1][jj] + pre[i-1][j-1];
	}
};
