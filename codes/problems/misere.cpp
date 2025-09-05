/*
misere nim

explicacao:
	basicamente nim normal mas quem ganha eh
	que pega o ultimo e nao o penultimo. a sol
	eh xor normal mas se tudo for 1 o primeiro
	ganha tbm;
*/
int main()
{
    _;
	
	int t; cin >> t;
	while (t--) {
		int n, res = 0, uns = 0; cin >> n;
		for (int i = 0, si; i < n; i++) {
			cin >> si; res ^= si;
			if (si == 1) uns++;
		}
		cout << (res or uns == n ? "First" : "Second") << endl;
	}
    
    return(0);
}

