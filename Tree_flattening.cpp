vector<int>adj[N];
vector<int>in(N),out(N);
int timer;
void pre(int u,int p){
    in[u]=++timer;
    for(auto &i:adj[u]){
        if(i==p)continue;
        pre(i,u);
    }
    out[u]=++timer;
}
