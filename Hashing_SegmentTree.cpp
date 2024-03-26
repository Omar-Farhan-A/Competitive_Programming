vector<ll>pw1(N),pw2(N);
vector<Pair<ll>>pre(N);
ll mod1=1e9+7,mod2=2e9+11,base1=31,base2=37,inv1,inv2;
ll fpow(ll x,ll y,ll mod){
    ll prod = x,ans = 1;
    while(y){
        if(y&1)ans*=prod,ans%=mod;
        prod*=prod;
        prod%=mod;
        y>>=1;
    }
    return ans;
}
void init(){
    inv1=fpow(base1,mod1-2,mod1);
    inv2=fpow(base2,mod2-2,mod2);
    pw1[0]=pw2[0]=1;
    for(int i=1;i<N;i++){
        pw1[i]=(pw1[i-1]*base1)%mod1;
        pw2[i]=(pw2[i-1]*base2)%mod2;
    }

}
struct Hashing_SegmentTree{
    struct Node{
        ll pre1,suf1,pre2,suf2;
        int siz;
        Node(char c='a'){
            pre1=suf1=c-'a'+1;
            pre2=suf2=c-'a'+1;
            siz=1;
        }
    };
    vector<Node>seg;
    int siz=1;
    Hashing_SegmentTree(int n){
        while (siz<=n)siz*=2;
        seg=vector<Node>(2*siz);
    }
    Node merge(Node a,Node b){
        Node ret;
        ret.pre1=(a.pre1*pw1[b.siz]+b.pre1)%mod1;
        ret.pre2=(a.pre2*pw2[b.siz]+b.pre2)%mod2;
        ret.suf1=(b.suf1*pw1[a.siz]+a.suf1)%mod1;
        ret.suf2=(b.suf2*pw2[a.siz]+a.suf2)%mod2;
        ret.siz=a.siz+b.siz;
        return ret;
    }
    void update(int idx,int lx,int rx,int i,char c){
        if(lx>i||rx<i)return;
        if(lx==rx){
            seg[idx]=Node(c);
            return;
        }
        int mid=(lx+rx)>>1;
        update(2*idx,lx,mid,i,c);
        update(2*idx+1,mid+1,rx,i,c);
        seg[idx]= merge(seg[2*idx],seg[2*idx+1]);
    }
    Node query(int idx,int lx,int rx,int l,int r){
        if(lx>=l&&rx<=r){
            return seg[idx];
        }
        int mid=(lx+rx)>>1;
        if(l<=mid&&r>mid){
            return merge(query(2*idx,lx,mid,l,r),query(2*idx+1,mid+1,rx,l,r));
        }
        else if(r<=mid){
            return query(2*idx,lx,mid,l,r);
        }
        else return query(2*idx+1,mid+1,rx,l,r);
    }
    void update(int i,char c){
        update(1,1,siz,i,c);
    }
    pair<ll,ll> query(int l,int r){
        Node cur=query(1,1,siz,l,r);
        return {cur.pre1,cur.pre2};
    }
    bool  is_Palindrom(int l,int r){
        Node cur=query(1,1,siz,l,r);
        pair <ll,ll> a{cur.pre1,cur.pre2};
        pair<ll,ll> b={cur.suf1,cur.suf2};
        return a==b;
    }
};
