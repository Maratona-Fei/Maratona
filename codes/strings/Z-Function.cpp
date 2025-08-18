// Z-Function

// complexidade: O(n)

// z[i] representa o comprimento do maior prefixo da string s
// q tmb eh um sufixo de s que comeca na posicao i

vector<int> z_function(string& s){
	int n = s.size();
	vector<int> z(n);

	int l = 0, r = 0;

	for(int i = 1; i < n; i++){
		if(i < r) z[i] = min(r - i, z[i-l]);

		while(i + z[i] < n and s[z[i]] == s[i + z[i]]) z[i]++;

		if(i + z[i] > r) l = i, r = i + z[i];
	}

	return z;
}
