///*
//maximum xor subarray
//
//	descricao: pra uma array, definir qual o xor maximo
//	que uma subarray pode ter. a ideia eh que, pra um
//	prefixo da array, todo prefixo anterior a ela pode
//	definir um subarray.
//
//	sei la como descrever isso mas basicamente:
//	xor(l, r) = xor(1, r) ^ xor(1, l-1)
//
//	particulamente, faz sentido, pra um prefixo r, escolher
//	aquele que eh anterior e que tem xor maximo comigo.
//	esse lance de xor maximo da pra fazer com trie.
//	O(nlogn)
//*/

struct trie {
	vector<vector<int>> to;
	vector<int> end, pref;
	int sigma; char norm;
	trie(int sigma_=26, char norm_='a') : sigma(sigma_), norm(norm_) {
		to = {vector<int>(sigma)};
		end = {0}, pref = {0};
	}
	void insert(string s) {
		int x = 0;
		for (auto c : s) {
			int &nxt = to[x][c-norm];
			if (!nxt) {
				nxt = to.size();
				to.push_back(vector<int>(sigma));
				end.push_back(0), pref.push_back(0);
			}
			x = nxt, pref[x]++;
		}
		end[x]++, pref[0]++;
	}
	void insert(int a) {
		insert(bitset<40>(a).to_string());
	}
	int max_xor(string s) {
		int u = 0;
		string R = "";
		for (char c : s) {
			char c_ = (c == '0' ? '1' : '0');
			if (to[u][c_ - norm]) {
				u = to[u][c_ - norm];
				R.push_back('1');
			} else {
				u = to[u][c - norm];
				R.push_back('0');
			}
		}
		//cout << R << endl;
		int res = 0;
		reverse(all(R));
		for (int i = 0; i < 40; i++) {
			if (R[i] == '1') res |= (1 << i);
		}
		return res;
	}
	int max_xor(int a) {
		return max_xor(bitset<40>(a).to_string());
	}
};

int solve() {
	int n; cin >> n;
	vector<int> A(n);
	for (int& i : A) cin >> i;

	trie T(2, '0');
	T.insert(0);

	int res = 0;
	for (int i = 0, p = 0; i < n; i++) {
		p ^= A[i];
		res = max(res, T.max_xor(p));
		T.insert(p);
	}
	cout << res << endl;

	return(0);
}
