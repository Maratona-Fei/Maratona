//s-nim
//
//explicacao:
//	quase um nim normal, mas pra cada posicao eu so posso
//	algum valor em s[]. o exemplo mais simples pra uso de
//	mex. lembra que uma posicao eh ganha em nim se o ^ de
//	tudo nao eh 0.

int main()
{
    _;

	int k; cin >> k;
	vector<int> s(k);
	for (int& i : s) cin >> i;

	// calculo dos grundy para cada heap possivel
	// nao eh um nim simples, entao o grundy number permite que eu reduza o jogo pra um nim que eu conheco.
	vector<int> grundy(MAX + 1, 0);
	for (int i = 1; i <= MAX; i++) {
		set<int> chega;
		for (int si : s) {
			if (i >= si) {
				chega.insert(grundy[i - si]);
			}
		}
		int mex = 0;
		while (chega.count(mex)) {
			mex++;
		}
		grundy[i] = mex;
	}

	int m; cin >> m;
	while (m--) {
		int l, res = 0; cin >> l;
		for (int i = 0, x; i < l; i++) {
			cin >> x; res ^= grundy[x];
		}
		cout << (res ? "W" : "L");
	}
	cout << endl;
    
    return(0);
}

