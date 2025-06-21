vector< vector<int> > adj;
vector<int> lowLink, inDeg;
int timer;
void tarjan(int u,int p) {
 lowLink[u]=inDeg[u]=++timer;
 for(auto &i:adj[u]){
     if(!inDeg[i]){
         tarjan(i,u);
         lowLink[u]=min(lowLink[u],lowLink[i]);
         if(lowLink[i]==inDeg[i]){
             // it's a bridge between u,i
         }
     }
     else if(i!=p){
         lowLink[u]=min(lowLink[u],inDeg[i]);
     }
 }
}
