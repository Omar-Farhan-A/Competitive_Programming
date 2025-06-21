struct Edge{
        int node,w;
    };
vector<Edge>adj[N];
vector<ll>Dijkstra(int src,int n){
    vector<ll>dist(n+5,-1);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>>q;
    q.push({0,src});
    while (!q.empty()){
        int u=q.top().second;
        ll cost=q.top().first;
        q.pop();
        if(~dist[u])continue;
        dist[u]=cost;
        for(auto &[v,w]:adj[u]){
            if(dist[v]==-1){
                q.push({cost+w,v});
            }
        }
    }
    return dist;
}
