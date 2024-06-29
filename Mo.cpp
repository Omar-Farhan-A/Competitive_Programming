// 1-based Mo-algorithm
const int SQ=450,Q=2e5+7;
struct query{
    int l,r,q_idx,block_idx;
    query(){}
    query(int L, int R, int Q_idx)
    {
        l= L , r= R , q_idx=Q_idx, block_idx= L / SQ;
    }
    bool operator<(const query&y)const{
        if(block_idx!=y.block_idx)
        {
            return block_idx<y.block_idx;
        }
        return r<y.r;
    }
};
int q_ans[Q],q;
ll ans;
query queries[Q];
void add(int idx)
{
    // what you need to add
}
void remove(int idx)
{
    // what you need to remove
}
void MO_process()
{
    sort(queries,queries+q);
    int l=1,r=0;
    for(int i=0;i<q;i++)
    {
        while(r<queries[i].r)add(++r);
        while(r>queries[i].r)remove(r--);
        while(l<queries[i].l)remove(l++);
        while(l>queries[i].l)add(--l);
        q_ans[queries[i].q_idx]=ans;
    }
}
