#define vi vector<int>
const int LG = 18;

// Complexidades: 
// induced_sort(): O(n + val_range)
// sa_is(): O(n)
// suffix_array(): O(n)
// construct_lcp(): O(n)
// prec(): O(n)
// build(): O(nlogn)
// query(): O(1)
// get_lcp(): O(1) // find_ocurrence(): O(logn)
// count_substr(): O(n)
// lcs(): O(n+m)

void induced_sort(const vi& v, int val_range, vi& sa, const vector<bool>& sl, const vi& lms_idx){
    vi l(val_range), r(val_range);

    for(int c : v){
        if(c + 1 < val_range) ++l[c+1];
        ++r[c];
    }

    partial_sum(l.begin(), l.end(), l.begin());
    partial_sum(r.begin(), r.end(), r.begin());
    fill(sa.begin(), sa.end(), -1);

    for(int i = lms_idx.size() - 1; i >= 0; --i)
        sa[--r[v[lms_idx[i]]]] = lms_idx[i];

    for(int i : sa)
        if(i >= 1 and sl[i-1])
            sa[l[v[i-1]]++] = i - 1;
    fill(r.begin(), r.end(), 0);

    for(int c : v) ++r[c];

    partial_sum(r.begin(), r.end(), r.begin());

    for(int k = sa.size()-1, i = sa[k]; k >= 1; --k, i = sa[k])
        if(i >= 1 and !sl[i - 1]) sa[--r[v[i-1]]] = i - 1;
}

vi sa_is(const vi& v, int val_range){
    const int n = v.size();

    vi sa(n), lms_idx;
    vector<bool> sl(n);

    sl[n-1] = 0;

    for(int i = n - 2; i >= 0; --i){
        sl[i] = (v[i] > v[i + 1] or (v[i] == v[i + 1] and sl[i+1]));
        if(sl[i] and !sl[i+1]) lms_idx.push_back(i+1);
    }

    reverse(lms_idx.begin(), lms_idx.end());
    induced_sort(v, val_range, sa, sl, lms_idx);

    vi new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());

    for(int i = 0, k = 0; i < n; i++)
        if(!sl[sa[i]] and sa[i] >= 1 and sl[sa[i] - 1]) 
            new_lms_idx[k++] = sa[i];
    int cur = 0;
    sa[n-1] = cur;

    for(size_t k = 1; k < new_lms_idx.size(); ++k){
        int i = new_lms_idx[k - 1], j = new_lms_idx[k];
        if(v[i] != v[j]){
            sa[j] = ++cur;
            continue;
        }

        bool flag = 0;
        for(int a = i + 1, b = j + 1;; ++a, ++b){
            if(v[a] != v[b]){
                flag = 1;
                break;
            }
            if((!sl[a] and sl[a - 1]) or (!sl[b] and sl[b - 1])){
                flag = !((!sl[a] and sl[a - 1]) and (!sl[b] and sl[b - 1]));
                break;
            }
        }
        sa[j] = (flag ? ++cur : cur);
    } 

    for(size_t i = 0; i < lms_idx.size(); ++i)
        lms_vec[i] = sa[lms_idx[i]];

    if(cur + 1 < (int)lms_idx.size()) {
        auto lms_sa = sa_is(lms_vec, cur + 1);
        for(size_t i = 0; i < lms_idx.size(); ++i){
            new_lms_idx[i] = lms_idx[lms_sa[i]];
        }
    }
    induced_sort(v, val_range, sa, sl, new_lms_idx);

    return sa;
}

vi suffix_array(const string& s, const int LIM = 128){
    vi v(s.size() + 1);
    copy(begin(s), end(s), begin(v));
    v.back() = '$';
    auto ret = sa_is(v, LIM);
    ret.erase(ret.begin());
    return ret;
}

struct SuffixArray {
    int n;
    string s;
    vi sa, rank, lcp;
    vector<vi> t;
    vi lg;

    SuffixArray() {}
    SuffixArray(string _s){
        n = _s.size();
        s = _s;
        sa = suffix_array(s);
        rank.resize(n);
        for(int i = 0; i < n; i++) rank[sa[i]] = i;
        construct_lcp();
        prec();
        build();
    }
    
    void construct_lcp(){
        int k = 0;
        lcp.resize(n - 1, 0);
        for(int i = 0; i < n; i++){
            if(rank[i] == n - 1){
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while(i + k < n and j + k < n and s[i+k] == s[j+k]) k++;
            lcp[rank[i]] = k;
            
            if(k) k--;
        }
    }

    void prec(){
        lg.resize(n, 0);
        for(int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
    }

    void build(){
        int sz = n - 1;
        t.resize(sz);

        for(int i = 0; i < sz; i++){
            t[i].resize(LG);
            t[i][0] = lcp[i];
        }

        for(int k = 1; k < LG; ++k){
            for(int i = 0; i + (1 << k) - 1 < sz; ++i){
                t[i][k] = min(t[i][k-1], t[i + (1 << (k - 1))][k-1]);
            }
        }
    }

    int query(int l, int r){ // minimo do lcp[l] ... lcp[r]
        int k = lg[r - l + 1];
        return min(t[l][k], t[r - (1 << k) + 1][k]); 
    }

    int get_lcp(int i, int j){ // lcp do sufixo comecando em i e j
        if(i == j) return n - i;
        int l = rank[i], r = rank[j];
        if(l > r) swap(l, r);
        return query(l, r-1);
    }

    int lower_bound(string& t){
        int l = 0, r = n - 1, k = t.size(), ans = n;

        while(l <= r){
            int mid = (l + r) >> 1;
            if(s.substr(sa[mid], min(n - sa[mid], k)) >= t) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }

    int upper_bound(string& t){
        int l = 0, r = n - 1, k = t.size(), ans = n;

        while(l <= r){
            int mid = l + r >> 1;
            if(s.substr(sa[mid], min(n - sa[mid], k)) > t) ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        return ans;
    }

    pair<int,int> find_occurrence(int p, int len){
        p = rank[p];
        pair<int,int> ans = {p, p};
        int l = 0, r = p - 1;

        while(l <= r){
            int mid = l + r >> 1;
            if(query(mid, p - 1) >= len) ans.f = mid, r = mid - 1;
            else l = mid + 1;
        }
        l = p + 1, r = n - 1;

        while(l <= r){
            int mid = (l + r) >> 1;
            if(query(p, mid - 1) >= len) ans.s = mid, l = mid + 1;
            else r = mid - 1;
        }
        return ans;
    }

    ll count_substr(){
        ll ans = 0;
        ans += n - sa[0];

        for(int i = 1; i < sa.size(); i++) ans += n - sa[i]-lcp[i - 1];

        return ans;
    }

    // tem q add # entre as duas palavras
    // divisor == posicao do %
    string lcs(int divisor){
                            //tam e pos
        pair<int, int> sub = {0, -1};
        string ans = "";

        for(int i = 0; i < lcp.size(); i++){
            if(sa[i] == divisor or sa[i+1] == divisor) continue;
            if(!(sa[i] < divisor ^ sa[i+1] < divisor)) continue;

            int tam = lcp[i];

            if(tam > sub.f){
                ans = s.substr(sa[i], tam);
                sub = {tam, sa[i]};
            }
        }

        return ans;
    }
};
