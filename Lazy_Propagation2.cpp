template<typename T=int>
class Lazy_propagate {
private:
    struct Node{
        T val,lazy;
        bool isLazy;
        Node(T v=0){
            val=v;
            lazy=0;
            isLazy=0;
        }
    };
    vector<Node> seg;
    vector<int>a;
    void build(int idx,int lx,int rx,int l,int r){
        if(lx>r or rx<l)return;
        if(lx==rx){
            seg[idx]= Node(a[lx-1]);
            return;
        }
        int m=(lx+rx)>>1;
        build(idx<<1,lx,m,l,r);
        build(idx<<1|1,m+1,rx,l,r);
        apply(idx);
    }
    void propagate(int idx,int lx,int rx){
        if(!seg[idx].isLazy)return;
        seg[idx].val+=(rx-lx+1)*seg[idx].lazy;
        if(lx!=rx){
            seg[idx<<1].lazy+=seg[idx].lazy;
            seg[idx<<1|1].lazy+=seg[idx].lazy;
            seg[idx<<1].isLazy=seg[idx<<1|1].isLazy=1;
        }
        seg[idx].isLazy=seg[idx].lazy=0;
    }
    T merge(T x, T y){
        return x + y;
    }
    void apply(int idx...){
        seg[idx].val= merge(seg[idx<<1].val,seg[idx<<1|1].val);
    }
    void update(int idx,int lx,int rx,int l,int r,T val...){
        propagate(idx,lx,rx);
         if(lx>r||rx<l)return ;
        if(lx>=l&&rx<=r){
            seg[idx].lazy+=val;
            seg[idx].isLazy=1;
            propagate(idx,lx,rx);
            return;
        }
        int m=(lx+rx)>>1;
        update(idx<<1,lx,m,l,r,val);
        update(idx<<1|1,m+1,rx,l,r,val);
        apply(idx);
    }
    T query(int idx,int lx,int rx,int l,int r){
         propagate(idx,lx,rx);
        if(lx>r||rx<l)return 0;
        if(lx>=l&&rx<=r){
            return seg[idx].val;
        }
        int mid=(lx+rx)>>1;
        return merge(query(idx<<1,lx,mid,l,r), query(idx<<1|1,mid+1,rx,l,r));
    }
public:
    int siz;
    Lazy_propagate(int n, vector<int>&v...){
        siz=1;
        while (siz<=n)siz<<=1;
        seg.resize(siz<<1);
        this->a=v;
        build(1,1,siz,1,n);
    }
    T query(int l,int r){
        return query(1,1,siz,l,r);
    }
    void update(int l,int r,T val){
        update(1,1,siz,l,r,val);
    }
};
