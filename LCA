vector<vector<int>>up;
vector<int>adj[N],depth;
int l;
void dfs(int u,int p,int d){
    depth[u]=d;
    for(auto i:adj[u]){
        if(i==p)continue;
        up[i][0]=u;
        for(int j=1;j<l;j++){
            up[i][j]=up[up[i][j-1]][j-1];
        }
        dfs(i,u,d+1);
    }
}
void burn() {
    int n,q;cin>>n>>q;
    l=int(log2(n))+2;
    up=vector<vector<int>>(n+1,vector<int>(l,0));
    depth=vector<int>(n+1,0);
    for(int i=2;i<=n;i++){
        int u;cin>>u;
        adj[u].push_back(i);
    }
    dfs(1,1,0);
    while (q--){
      int u,v;cin>>u>>v;
      if(depth[u]<depth[v])swap(u,v);
      int k=depth[u]-depth[v];
      for(int i=0;i<l;i++){
          if(k&(1<<i)){
              u=up[u][i];
          }
      }
      if(u==v){
          cout<<u<<'\n';
          continue;
      }
      for(int i=l-1;i>=0;i--){
          if(up[u][i]!=up[v][i]){
              u=up[u][i];
              v=up[v][i];
          }
      }
      cout<<up[u][0]<<'\n';
    }
 
}
