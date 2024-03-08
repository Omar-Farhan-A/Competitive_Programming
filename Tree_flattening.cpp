vector<ll>seg(4 * N);
ll merge(ll a,ll b){
    return a + b;
}
ll query(int idx,int lx,int rx,int l,int r){
    if(lx>=l&&rx<=r){
        return seg[idx];
    }
    int mid=(lx+rx)>>1;
    if(l<=mid&&r>mid) {
        return merge(query(idx * 2, lx, mid, l, r), query(idx * 2+1, mid + 1, rx, l, r));
    }
    else if(r<=mid){
        return query(idx * 2, lx, mid, l, r);
    }
    else {
        return query(idx * 2+1, mid + 1, rx, l, r);
    }
}
void update(int idx,int lx,int rx,int i,int v){
    if(lx>i||rx<i)return;
    if(lx==rx){
        seg[idx]=v;
        return;
    }
    int mid=(lx+rx)>>1;
    update(2*idx,lx,mid,i,v);
    update(2*idx+1,mid+1,rx,i,v);
    seg[idx]= merge(seg[2 * idx], seg[2 * idx + 1]);
}
vector<int>adj[N];
vector<int>in,out;
int cur;
void pre(int u,int p){
    in[u]=cur;
    for(auto i:adj[u]){
        if(i==p)continue;
        cur++;
        pre(i,u);
    }
    out[u]=cur;
}
void burn() {
    int n,q;cin>>n>>q;
    cur=1;
    out=vector<int>(n+1);
    in=vector<int>(n+1);
    vector<int>a(n);
    cin>>a;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pre(1,-1);
    for(int i=0;i<n;i++){
        update(1,1,n,in[i+1],a[i]);
    }
    while (q--){
        int k;cin>>k;
        if(k&1){
            int u,v;cin>>u>>v;
            update(1,1,n,in[u],v);
        }
        else{
            int u;cin>>u;
            cout<<query(1,1,n,in[u],out[u])<<'\n';
        }
    }
 
 
}
