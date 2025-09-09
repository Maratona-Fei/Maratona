//coprime pairs
//
//	descricao: quantos pairs (i, j), com i < j,
//	existe, tam que gcd(A[i], A[j]) == 1.
//
//	a ideia eh usar contagem de fatores normal,
//	mas quando for contar usar inclusao exclusao
//
//	pra todo i, eu olho pras frequencias de fator
//	< i e computo com quantos eu nao sou coprimo
//	(compartilho ao menos 1 primo).
//	O(nlogn)

const int MAX = 1e6+10;
int divi[MAX];

void crivo(int lim) {
	for (int i = 1; i <= lim; i++) divi[i] = 1;

	for (int i = 2; i <= lim; i++) if (divi[i] == 1)
		for (int j = i; j <= lim; j += i) divi[j] = i;
}

void fact(vector<int>& v, int n) {
	if (n != divi[n]) fact(v, n/divi[n]);
	v.push_back(divi[n]);
}

vector<int> fact_(int n) {
	vector<int> res;
	fact(res, n);
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	return res;
}

int main()
{
    _;

	crivo(MAX-1);
	int n; cin >> n;
	vector<int> cont(MAX+1, 0);

	ll res = 0;
	for (int i = 0, x; i < n; i++) {
		cin >> x;

		if (x == 1) {
			res += i;
			continue;
		}

		auto f = fact_(x);
		int m = f.size(), ncop = 0;
		for (int mask = 1; mask < (1 << m); mask++) {
			int agr = 1;
			for (int j = 0; j < m; j++) {
				if (mask & (1 << j)) agr *= f[j];
			}
			ncop += (__builtin_popcount(mask) & 1 ? +1 : -1) * cont[agr];
			cont[agr]++;
		}

		res += i - ncop;
	}
	cout << res << endl;

    return(0);
}
