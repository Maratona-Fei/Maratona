// LIS

// LIS q utiliza busca binaria | O(nlogn)
// para subseq decrescente colocar lower_bound
vector<int> lis(vector<int> v, int n){
	vector<int> d(n+1, INF), idx(n+1), p(n+1, -1);
	d[0] = -INF;
	idx[0] = -1;

	for(int i = 0; i < n; i++){
		int l = upper_bound(d.begin(), d.end(), v[i]) - d.begin();

		if(d[l-1] < v[i] and v[i] < d[l]){
			d[l] = v[i], idx[l] = i;

			if(l > 0)
				p[i] = idx[l-1];
		}
	}

	int len = 0;

	for(int l = 0; l <= n; l++)
		if(d[l] < INF) len = l;
	
	int act = idx[len];
	
	vector<int> ans;

	while(act != -1){
		ans.push_back(v[act]);
		act = p[act];
	}

	reverse(ans.begin(), ans.end());

	return ans;
}
