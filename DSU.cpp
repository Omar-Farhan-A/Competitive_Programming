int Parent[N],size[N];
int getRoot(int u){
    if(u == Parent[u])return u;
    return Parent[u]= getRoot(Parent[u]);
}
bool sameSet(int u,int v){
    return getRoot(u)== getRoot(v);
}
void merge(int u,int v){
    u= getRoot(u);
    v= getRoot(v);
    if(u==v)
        return;
    Parent[u]=v;
    size[v]+=size[u];
}
void ini(){
    for(int i=1;i<N;i++)Parent[i]=i;
}