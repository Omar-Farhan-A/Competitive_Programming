vector<int>seg(4 * N);
vector<int>nums;
int merge(int a,int  b){
    return a + b;
}
void build(int idx,int lx,int rx){
    if(lx==rx){
        seg[idx]= nums[lx - 1];
        return;
    }
    int mid=(lx+rx)>>1;
    build(2*idx,lx,mid);
    build(2*idx+1,mid+1,rx);
    seg[idx]=merge(seg[2 * idx], seg[2 * idx + 1]);
}
int query(int idx,int lx,int rx,int l,int r){
    if(lx>=l&&rx<=r){
        return seg[idx];
    }
    int mid=(lx+rx)>>1;
    if(l<=mid&&r>mid) {
        return merge(query(idx * 2, lx, mid, l, r), query(idx * 2+1, mid + 1, rx, l, r));
    }
    else if(r<=mid){
        return query(idx * 2, lx, mid, l, r);
    }
    else {
        return query(idx * 2+1, mid + 1, rx, l, r);
    }
}
void update(int idx,int lx,int rx,int i,int v){
    if(lx>i||rx<i)return;
    if(lx==rx){
        seg[idx]=v;
        return;
    }
    int mid=(lx+rx)>>1;
    update(2*idx,lx,mid,i,v);
    update(2*idx+1,mid+1,rx,i,v);
    seg[idx]= merge(seg[2 * idx], seg[2 * idx + 1]);
}
