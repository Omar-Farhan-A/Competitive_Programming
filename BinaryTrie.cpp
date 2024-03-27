struct BinaryTrie{
        struct Node{
            Node *child[2];
            int fre[2];
            Node(){
                child[0]=child[1]=0;
                fre[0]=fre[1]=0;
            }
        };
        Node *root =new Node();
        void insert(int x){
            Node *cur=root;
            for(int i=30;i>=0;i--){
               bool idx=(x>>i)&1;
               if(cur->child[idx]==0)cur->child[idx]=new Node();
                cur->fre[idx]++;
                cur=cur->child[idx];
            }
        }
        void del(int n,int i,Node *cur){
            if(i==-1)return;
            bool idx=(n>>i)&1;
            del(n,i-1,cur->child[idx]);
            cur->fre[idx]--;
            if(cur->fre[idx]==0)
            {
                delete cur->child[idx];
                cur->child[idx]=0;
            }
        }
        int query(int x){
            int ret=0;
            Node *cur=root;
            for(int i=30;i>=0;i--){
                int idx=(x>>i)&1;
                if(cur->child[idx^1]==0){
                    cur=cur->child[idx];
                }
                else {
                    ret|=(1<<i);
                    cur=cur->child[idx^1];
                }
            }
            return ret;
        }
    };
