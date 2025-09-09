///*
//periodic strings
//
//explicacao:
//	quais tamanhos de prefixo que podem 'resumir'
//	a string (se repetir o prefixo, reconstruo a
//	string igual toda). legal por causa do hash na
//
//	string e ainda o hash em [l, r] mt brabo
//*/
#include <bits/stdc++.h>
#define f first
#define s second
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
using namespace std;
 
const ll P = 69420;
const ll M = 1e9+9;
 
int main() {
    _;
 
    string s; cin >> s;
    int n = s.size();
 
    vector<ll> base(n), pre(n + 1);
    base[0] = 1;    
    for (int i = 1; i < n; i++) {
        base[i] = base[i - 1] * P % M;
    }
 
    for (int i = 1; i <= n; i++) {
        pre[i] = (pre[i - 1] * P + s[i - 1]) % M;
    }
 
    auto hash = [&] (int l, int r) -> ll {
        ll h = (pre[r + 1] - base[r - l + 1] * pre[l] % M + M) % M;
        return h;
    };
 
    for (int i = 0; i < n; i++) {
        int j = 0, ok = 1;
        while (j < n) {
            int tam = min(i + 1, n - j);
            if (hash(0, tam - 1) != hash(j, j + tam - 1)) {
                ok = 0;
                break;
            }
            j += tam;
        }
        if (ok) {
			cout << i + 1 << ' ';
			break;
		}
    }
    cout << endl;
 
    return 0;
}

