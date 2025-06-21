//used when we don't know the roots
vector<int>adj[N];
string getNodeCanoincalForm(int u, vector<vector<string>>&subcan){
    string curNode="(";
    std::sort(subcan[u].begin(), subcan[u].end());
    for(auto &i:subcan[u])curNode+=i;
    curNode+=")";
    return curNode;
}
string treeCanoincalForm(){
    int n;//n=number of nodes
    // Prepare level one nodes :the leaves
    queue<int>leafNodes;
    vector<int>deg(n+1,-1);
    int remNodes=n;
    for(int i=1;i<=n;i++){
        if(adj[i].size()<=1){
            leafNodes.push(i);
        }
        else deg[i]=int(adj[i].size());
    }
    vector<vector<string>>subCan(n+1);
    while (remNodes>2){
        int sz=sz(leafNodes);
        while (sz--){
            int u=leafNodes.front();
            leafNodes.pop();
            string curNode= getNodeCanoincalForm(u,subCan);
            for(auto &i:adj[u]){
                subCan[i].push_back(curNode);
                if(--deg[i]==-1){
                    leafNodes.push(i);
                }
            }
            --remNodes;
        }
    }
    int v1=leafNodes.front();
    leafNodes.pop();
    int v2=leafNodes.empty()?-1:leafNodes.front();
    string s1= getNodeCanoincalForm(v1,subCan);
    string s2= ~v2? getNodeCanoincalForm(v2,subCan):"";
    if(v2==-1)return s1;
    subCan[v1].push_back(s2);
    subCan[v2].push_back(s1);
    return min(getNodeCanoincalForm(v1,subCan), getNodeCanoincalForm(v2,subCan));
}
