#define ll long long
#define isON(n, k) (((n) >> (k)) & 1)
#define sz(x) int(x.size())
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update> ;
template<class T> using  ordered_multiset= tree<pair<T, T>, null_type, less<pair<T, T>>, rb_tree_tag, tree_order_statistics_node_update>;
const int N=1e5+7,OO=0x3f3f3f3f,M=1e3+5,MOD=1e9+7;
int dx[]={1,0, -1,0,1,1,-1,-1};
int dy[]={0,1, 0,-1,1,-1,1,-1};//
template < typename T = int > using Pair = pair < T, T >;
template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x: v) in >> x;
    return in;
}
template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) {
    for (const T &x: v) out << x<<' ' ;
    return out;
}
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
