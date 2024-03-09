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
int K_ANC(int u,int k){
    if(depth[u]<k){
        return -1;
    }
    for(int i=0;i<l;i++){
        if(k&(1<<i)){
            u=up[u][i];
        }
    }
    return u;
}
