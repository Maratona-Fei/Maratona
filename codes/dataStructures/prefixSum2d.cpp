// PrefixSum 2D

// Complexidade: O(m*n)
vector<vector<int>> prefixSum2d(vector<vector<int>>& arr, int n){
	vector<vector<int>> prefix(n+1, vector<int>(n+1));

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			prefix[i][j] = arr[i][j]
						 + prefix[i-1][j]
						 + prefix[i][j-1]
						 - prefix[i-1][j-1];
		}
	}
	return prefix;
}

int query(vector<vector<int>>& prefix, int x1, int y1, int x2, int y2){
	return prefix[x2][y2]
	     - prefix[x1-1][y2]
		 - prefix[x2][y1-1]
		 + prefix[x1-1][y1-1];
}
