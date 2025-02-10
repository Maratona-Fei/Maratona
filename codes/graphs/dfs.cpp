void dfs(vector<vector<int>>& g, int v){
  vector<bool> vis(g.size(), false);
  vis[v] = true;

  stack<int> s;
  s.push(v);

  while(!s.empty()){
    v = s.top();s.pop();

    for(int& x : g[v]){
      if(!vis[x]){
        vis[x] = true;
        s.push(x);
      }
    }
  }
}
