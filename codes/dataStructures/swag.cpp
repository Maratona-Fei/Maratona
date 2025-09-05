// swag (sliding-window aggregate)
//
// o(1) amortizado pra manter uma queue com os valores
// de uma janela.
// serve pra qualquer operacao que seja assossiativa , 
// que tenha um identidade, e que nao tenha inverso.
// (se tiver inverso facil nao precisa codar isso)
//
// op() tem que ser a operacao.
// e() tem que ser a identidade.

template<typename T>
struct swag { 
	stack<pair<T, T>> in, out;

	T e() { return 0; };
	T op(T a, T b) {
		return a | b;
	}
	void push(T x) {
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
	T query() {
		return op(in.empty() ? e() : in.top().s, out.empty() ? e() : out.top().s);
	}
	int size() { return in.size() + out.size(); };
	bool empty() { return in.empty() and out.empty(); };
};
