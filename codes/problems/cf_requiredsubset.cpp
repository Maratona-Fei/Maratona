//segment with required subset
//
//	descricao: achar a menor subarray que tem
//	um subconjunto que soma x. essa do subconj
//	eh bem simples (dp. coin sum). agora manter
//	isso em uma sliding window eh foda.
//
//	pra isso, tem que usar swag (sliding window
//	agreggate, truque de duas stacks monotonicas)
//	e a parada fica mais facil.

template<typename T>
struct swag {
	stack<pair<int, T>> in, out;

	T e() { T bs; bs.reset(); bs[0] = 1; return bs; };
	T op(int a, T b) {
		auto c = b | (b << a);
		c[0] = 1;
		return c;
	}
	void push(int x) {
		in.emplace(x, op(x, in.empty() ? e() : in.top().s));
	}
	void pop() {
		if (!out.empty()) {
			out.pop();
			return;
		}

		while (!in.empty()) {
			auto [a, b] = in.top(); in.pop();
			out.emplace(a, op(a, out.empty() ? e() : out.top().s));
		}
		out.pop();
	}
	bool query(int t) {
		T L = (out.empty() ? e() : out.top().s) , R = (in.empty() ? e() : in.top().s);
		for (int i = 0; i <= t/2; i++) {
			bool c = L[i];
			L[i] = L[t-i];
			L[t-i] = c;
		}
		for (int i = t + 1; i < 1010; i++) L[i] = 0;
		return (L & R).any();
	}
	int size() { return in.size() + out.size(); };
	bool empty() { return in.empty() and out.empty(); };
};

int solve() {
	int n, s; cin >> n >> s;
	vector<int> A(n);
	for (int& i : A) cin >> i;

	swag<bitset<1010>> S;

	int res = INF;
	for (int r = 0, l = 0; r < n; r++) {
		S.push(A[r]);

		while (l <= r and S.query(s)) {
			res = min(res, r - l + 1);
			S.pop();
			l++;
		}
	}
	cout << (res == INF ? -1 : res) << endl;

	return(0);
}
