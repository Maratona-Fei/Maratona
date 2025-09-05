/*
segtree pra max subarray sum

descricao:
	nodo.val eh a res pra max subarray sum dele.

complexidades:
	memoria: o(n);
	build: o(n);
	prop: o(1), atualiza valores do nodo;
	query: o(logn), nodo de [a, b];
	update: o(logn), seta x pra [a, b];
*/

namespace seg {
    struct nodo {
        ll sum, pref, suf, val;
        int len;
		nodo() {};
		nodo(int l, ll v)  {
			len = l;
			sum = v * l;
			pref = suf = val = max(0LL, sum);
		}
    };
 
    nodo seg[4*MAX];
	ll lazy[4*MAX], lazyf[4*MAX];
    int n, *v;
 
	nodo combina(nodo a, nodo b) {
        nodo c;
        c.len = a.len + b.len;
        c.sum = a.sum + b.sum;
        c.pref = max(a.pref, a.sum + b.pref);
        c.suf  = max(b.suf, b.sum + a.suf);
        c.val  = max({a.val, b.val, a.suf + b.pref});
        return c;
    }
    nodo build(int p=1, int l=0, int r=n-1) {
		lazy[p] = lazyf[p] = 0;
        if (l == r) return seg[p] = nodo(1, v[l]);
        int m = (l + r) / 2;
        return seg[p] = combina(build(2*p, l, m), build(2*p+1, m+1, r));
    }
	void prop(int p, int l, int r) {
        if (!lazyf[p]) return;

        int m = (l + r) / 2;
        lazy[2*p] = lazy[2*p+1] = lazy[p];
        lazyf[2*p] = lazyf[2*p+1] = 1;
        seg[2*p] = nodo(m - l + 1, lazy[p]);
        seg[2*p+1] = nodo(r - m, lazy[p]);
        lazy[p] = lazyf[p] = 0;
	}
    nodo query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (b < l or r < a) return nodo(0, 0);	
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return combina(query(a, b, 2*p, l, m), query(a, b, 2*p+1, m+1, r));
	}
	void build(int n_, int* v_) {
		n = n_, v = v_;
		build();
	}
	nodo update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (b < l or r < a) return seg[p];
		if (a <= l and r <= b) {
			lazy[p] = x, lazyf[p] = 1;
			seg[p] = nodo(r - l + 1, x);
			if (l != r) prop(p, l, r);
			return seg[p];
		}
		int m = (l+r)/2;
		return seg[p] = combina(update(a, b, x, 2*p, l, m), update(a, b, x, 2*p+1, m+1, r));
	}
}
