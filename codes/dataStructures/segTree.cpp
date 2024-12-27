int v[MAX];
int seg[MAX * 4];

int build(int p , int l , int r){
        if(l == r) return seg[p] = v[l];

        int m = (l+r)/2;

        return seg[p] = min(build(2*p , l , m) , build(2*p+1 , m+1 , r));
}

int query(int a , int b , int p , int l , int r){
        if(b < l or r < a) return INF;
        if(a <= l and r <= a) return seg[p];
        int m = (l+r)/2;

        return min(query(a , b , 2*p , l , m) , query(a , b , 2*p+1 , m+1 , r));
}

int update(int i , int x , int p , int l , int r){
        if(i < l or r < i) return seg[p];
        if(l == r) return seg[p] = x;
        
        int m = (l+r)/2;

        return min(update(i , x , 2*p , l , m) , update(i , x , 2*p+1 , m+1 , r));
}
