
vector<vector<int>>up;
vector<int>adj[N],depth;
int l;
void dfs(int u,int p){
    for(auto i:adj[u]){
        if(i==p)continue;
        up[i][0]=u;
        for(int j=1;j<l;j++){
            up[i][j]=up[up[i][j-1]][j-1];
        }
        depth[i]=depth[u]+1;
        dfs(i,u);
    }
}
int get_LCA(int u,int v){
    if(depth[u]<depth[v])swap(u,v);
    int k=depth[u]-depth[v];
    for(int i=0;i<l;i++){
        if(k&(1<<i)){
            u=up[u][i];
        }
    }
    if(u==v){
        return u;
    }
    for(int i=l-1;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }
    return up[u][0];
}
