// KMP

// matching(s, t) retorna os indices das ocorrencias 
// de s em t
// autKMP constroi o automato do KMP

// Complexidades:
// pi - O(n)
// match - O(n + m)
// construir o automato - O(|sigma|)*n)
// n = |padrao| e m = |texto|
// fonte: github.com/brunomaletta

#define st string
vector<int> pi(st s){
	vector<int> p(s.size());
	for(int i = 1, j = 0; i < s.size(); i++){
		while(j and s[j] != s[i]) j = p[j-1];
		if(s[j] == s[i]) j++;
		p[i] = j;
	}
	return p;
}

vector<int> matching(st& s, st& t){
	vector<int> p = pi(s), match; 
	for(int i = 0, j = 0; i < t.size(); i++){
		while(j and s[j] != t[i]) j = p[j-1]; //at = aut.nxt[t[i]-'a'][at];
		if(s[j] == t[i]) j++;
		if(j == s.size()) match.push_back(i-j+1), j = p[j-1];
	}
	return match;
}

struct autKMP {
	vector<vector<int>> nxt;

	autKMP(st& s) : nxt(26, vector<int>(s.size()+1)){
		vector<int> p = pi(s);
		nxt[s[0]-'a'][0] = 1;
		for(char c = 0; c < 26; c++)
			for(int i = 1; i <= s.size(); i++)
				nxt[c][i] = c == s[i]-'a' ? i+1 : nxt[c][p[i-1]];
	}
};
