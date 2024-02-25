vector<int>adj[N];
string treeCanoincalForm(int u,int p){
    // used when we have know the root
    vector<string>children;
    for(auto i:adj[u]){
        if(i!=p)children.push_back(treeCanoincalForm(i,u));
    }
    string curNode="(";
    std::sort(children.begin(), children.end());
    for(auto &i:children)curNode+=i;
    curNode+=")";
    return curNode;
}
