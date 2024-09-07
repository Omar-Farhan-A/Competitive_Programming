template<typename T=int>
class Segment_Tree {
private:
    vector<T> seg;
    vector<int>a;
    void build(int idx,int lx,int rx,int l,int r){
        if(lx>r or rx<l)return;
        if(lx==rx){
            seg[idx]=a[lx-1];
            return;
        }
        int m=(lx+rx)>>1;
        build(idx<<1,lx,m,l,r);
        build(idx<<1|1,m+1,rx,l,r);
        apply(idx);
    }
    T merge(T x, T y){
        return x + y;
    }
    void apply(int idx...){
        seg[idx]= merge(seg[idx<<1],seg[idx<<1|1]);
    }
    void update(int idx,int lx,int rx,int i,T val...){
        if(lx==rx){
            seg[idx]=val;
            return;
        }
        int m=(lx+rx)>>1;
        if(i<=m)
            update(idx<<1,lx,m,i,val);
        else
            update(idx<<1|1,m+1,rx,i,val);
        apply(idx);
    }
    T query(int idx,int lx,int rx,int l,int r){
        if(lx>r||rx<l)return 0;
        if(lx>=l&&rx<=r){
            return seg[idx];
        }
        int mid=(lx+rx)>>1;
        return merge(query(idx<<1,lx,mid,l,r), query(idx<<1|1,mid+1,rx,l,r));
    }
public:
    int siz;
    Segment_Tree(int n,vector<int>&v...){
        siz=1;
        while (siz<=n)siz<<=1;
        seg.resize(siz<<1);
        this->a=v;
        build(1,1,siz,1,n);
    }
    T query(int l,int r){
        return query(1,1,siz,l,r);
    }
    void update(int idx,T val){
        update(1,1,siz,idx,val);
    }
};
