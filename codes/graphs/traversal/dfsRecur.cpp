void dfs(vector<vector<int>>& g, int s){
  vis[s] = true;
  for(int& i : g[s]){
    if(!vis[i]){
      dfs(i);
    }
  }
}
