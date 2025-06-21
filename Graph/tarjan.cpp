vector< vector<int> > adj, components;
vector<int> inStack, lowLink,compNum, inDeg;
stack<int> stk;
int timer;
void tarjan(int u) {
    lowLink[u]=inDeg[u]=++timer,inStack[u]=1;
    stk.push(u);
    for(auto &i:adj[u]){
        if(!inDeg[i]){
        tarjan(i);
        lowLink[u]=min(lowLink[u],lowLink[i]);
        }
        else if(inStack[i]){
        lowLink[u]=min(lowLink[u],inDeg[i]);
        }
    }
    if(inDeg[u]==lowLink[u]){
        components.push_back(vector<int>());
        int x=-1;
        while (x!=u)
        {
            x=stk.top(),stk.pop(),inStack[x]=0;
            components.back().push_back(x);
            compNum[x]=components.size();
        }
    }
}
