// n log^2(n)
vector<int>adj[N];
vector<int>siz,a;
void pre(int u,int p){
    siz[u]=1;
    for(auto i:adj[u]){
        if(i==p)continue;
        pre(i,u);
        siz[u]+=siz[i];
    }
}
map<int, int> *cnt[N];
vector<int>ans;
void dfs(int v, int p){
    int mx = -1, bigChild = -1;
    for(auto u : adj[v])
        if(u != p){
            dfs(u, v);
            if(siz[u] > mx)
                mx = siz[u], bigChild = u;
        }
    if(bigChild != -1)
        cnt[v] = cnt[bigChild];
    else
        cnt[v] = new map<int, int> ();
    (*cnt[v])[ a[v] ] ++;
    for(auto u : adj[v])
        if(u != p && u != bigChild){
            for(auto x : *cnt[u])
                (*cnt[v])[x.first] += x.second;
        }
    ans[v-1]=int(cnt[v]->size());
}
