int cnt[N];
bool big[N];
void add(int u, int p, int x){
    cnt[ col[u] ] += x;
    for(auto i: adj[u])
        if(i != p && !big[i])
            add(i, u, x);
}
void dfs(int u, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto i : adj[u])
        if(i != p && siz[i] > mx)
            mx = siz[i], bigChild = i;
    for(auto i : adj[u])
        if(i != p && i != bigChild)
            dfs(i, u, 0);
    if(bigChild != -1)
        dfs(bigChild, u, 1), big[bigChild] = 1;
    add(u, p, 1);
    ans[u-1]= query(1,1,n,1,n).sum;
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0)
        add(u, p, -1);
}
