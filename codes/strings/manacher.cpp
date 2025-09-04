// Manacher

// complexidade: O(n)
// p[i] = raio do maior palíndromo
// centrado em i (na string transformada)
// comprimento real = p[i] - 1
// i for # = palindromos de tam par
// i for carac = palindromos de tam impar
// impar centro em i/2
// par centro entre i/2-1 e i/2

vector<int> manacher_odd(string s){
	int n = s.size(); 
	s = "$" + s + "^";

	vector<int> p(n+2);

	int l = 0, r = 1;

	for(int i = 1; i <= n; i++){
		p[i] = min(r - i, p[l + (r - i)]);

		while(s[i - p[i]] == s[i + p[i]]) p[i]++;

		if(i + p[i] > r)
			l = i - p[i], r = i + p[i];
	}

	return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
