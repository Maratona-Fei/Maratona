const int K = 26;

// Complexidade:
// add_string: O(m)
// build: O(m)
// build2: O(t)
// dfs: O(m + n)

// build2 tem q receber a stringzona
// dfs padrao recebe o root
// appear[i] = mostra a pos q apareceu o patterno 
// na stringzona
// Boa sorte

struct Aho{
    vector<int> appear;
    struct Node {
        int jump[26];
        vector<int> pos, adj;
        int link = -1, depth = -1, i = -1;
        Node(){
            memset(jump, -1, sizeof jump);
        }
    };
    
    Aho (int num_patterns){
        appear.assign(num_patterns, -1);
    };

    vector<Node> trie = {Node()};

    void add_string(string& s, int idx){
        int v = 0;

        for(char ch : s){
            int to = ch - 'a'; 
            if(trie[v].jump[to] == -1){
                int n = trie.size();
                trie[v].jump[to] = n, trie.emplace_back(); 
                trie[n].depth = trie[v].depth + 1;
            }

            v = trie[v].jump[to];
        }
        trie[v].pos.push_back(idx);
    }

    void build(){
        queue<int> q;

        for(int i = 0; i < 26; i++){
            if(trie[0].jump[i] != -1){
                int to = trie[0].jump[i];

                trie[to].link = 0;
                trie[0].adj.push_back(to);

                q.push(to);
            }
            else trie[0].jump[i] = 0;
        }

        while(q.size()){
            int v = q.front();q.pop();

            for(int i = 0; i < 26; i++){
                int to = trie[v].jump[i];

                if(to != -1){
                    int fail = trie[v].link;
                    int p = trie[fail].jump[i];

                    trie[to].link = trie[fail].jump[i];
                    trie[p].adj.push_back(to);

                    q.push(to);
                }
                else{
                    int fail = trie[v].link;
                    trie[v].jump[i] = trie[fail].jump[i];
                }
            }
        }
    }
    
    void build2(string& s){
        int n = s.size();
        int v = 0;

        for(int i = 0; i < n; i++){
            int j = s[i] - 'a';
             
            v = trie[v].jump[j];

            if(trie[v].i == -1)
                trie[v].i = i - trie[v].depth; 
        }
    }

    void dfs(int u){
        for(int v : trie[u].adj){
            dfs(v);
            int diff = trie[v].depth - trie[u].depth;

            if(trie[v].i != -1 and (trie[u].i == -1 or trie[u].i > trie[v].i + diff))
                trie[u].i = trie[v].i + diff;
        }

        for(int i : trie[u].pos)
            appear[i] = trie[u].i;
    }
};
