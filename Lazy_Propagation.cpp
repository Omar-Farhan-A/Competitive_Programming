template < typename T = int, const int Base = 0 > struct Lazy_Propagation {
    struct Node {
        T val, update;
        bool is_lazy;
        Node(T V = 0) : val(V), update(0), is_lazy(false) {}
        Node operator = (const T &other){
            this -> val = other;
            return *this;
        }
    };
    int size;
    T query_default, init_default;
    vector < Node > Tree;
#define LEFT (idx << 1)
#define RIGHT ((idx << 1) | 1)
    void intial(int n){
        size = 1;
        query_default = 0, init_default = 0;
        while(size <= n) size *= 2;
        Tree = vector < Node > (2 * size, Node(init_default));
    }

    Lazy_Propagation(int n){
        intial(n);
    }

    Lazy_Propagation(int n, const vector < T > &v){
        intial(n);
        build(v);
    }

    // the function that will be used to update the Tree
    T Lazy_operation(T a, T b){
        return a + b;
    }

    // the function that will be used to query on the Tree
    Node Tree_operation(const Node& a, const Node& b){
        return Node(a.val + b.val);
    }

    // push Lazy value to children in Lazy
    void propagate(int idx, int lx, int rx){
        if(!Tree[idx].is_lazy) return;
        Tree[idx].val = Lazy_operation(Tree[idx].val, (rx - lx + 1) * Tree[idx].update);
        if(lx != rx){
            Tree[LEFT].update = Lazy_operation(Tree[LEFT].update, Tree[idx].update);
            Tree[RIGHT].update = Lazy_operation(Tree[RIGHT].update, Tree[idx].update);
            Tree[LEFT].is_lazy = Tree[RIGHT].is_lazy = true;
        }
        Tree[idx].update = init_default, Tree[idx].is_lazy = false;
    }

    void update_lazy(int idx, T v){
        Tree[idx].update = Lazy_operation(Tree[idx].update, v);
        Tree[idx].is_lazy = true;
    }

    // build the Tree with given vector
    void build(const vector < T >& nums, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(Base ? lx >= sz(nums) : lx > sz(nums)) return;
        if(rx == lx) Tree[idx] = nums[lx - !Base];
        else {
            int mx = (rx + lx) / 2;
            build(nums, LEFT, lx, mx), build(nums, RIGHT, mx + 1, rx);
            propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
            Tree[idx] = Tree_operation(Tree[LEFT], Tree[RIGHT]);
        }
    }

    // build the Tree with initial value
    void build(const T initial_value, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(rx == lx) Tree[idx] = initial_value;
        else {
            int mx = (rx + lx) / 2;
            build(initial_value, LEFT, lx, mx), build(initial_value, RIGHT, mx + 1, rx);
            propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
            Tree[idx] = Tree_operation(Tree[LEFT], Tree[RIGHT]);
        }
    }

    // build the Tree with initial value
    void build(const T initial_value){
        build(initial_value, 1, 1, size);
    }

    void build(const vector < T >& nums){
        build(nums, 1, 1, size);
    }

    void update(int l, int r, T v, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return update_lazy(idx, v);
        if(lx > r || rx < l) return;
        int mx = (lx + rx) / 2;
        update(l, r, v, LEFT, lx, mx), update(l, r, v, RIGHT, mx + 1, rx);
        propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
        Tree[idx] = Tree_operation(Tree[LEFT], Tree[RIGHT]);
    }

    void update(int l, int r, T v){
        update(l, r, v, 1, 1, size);
    }
    Node query(int l, int r, int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx >= l && rx <= r) return Tree[idx];
        if(lx > r || rx < l) return query_default;
        int mx = (rx + lx) / 2;
        propagate(LEFT, lx, mx), propagate(RIGHT, mx + 1, rx);
        return Tree_operation(query(l, r, LEFT, lx, mx), query(l, r, RIGHT, mx + 1, rx));
    }

    T query(int l, int r){
        return query(l, r, 1, 1, size).val;
    }
    void print(int idx, int lx, int rx){
        propagate(idx, lx, rx);
        if(lx == rx) cout << Tree[idx].val << ' ';
        else {
            int mx = (lx + rx) / 2;
            print(LEFT, lx, mx), print(RIGHT, mx + 1, rx);
        }
    }
    void print(){
        print(1, 1, size);
        cout << '\n';
    }
#undef LEFT
#undef RIGHT
};