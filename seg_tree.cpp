struct seg_tree{
    struct node{
        int l, r, val, lazy = -1;
    };
    vector<node> tree;
    int n;
    int dbInd = 0;
    void build(int v){
        if(v >= n){
            tree[v].l = tree[r] = dbInd; dbInd++;
        }else{
            build(v*2); build(v*2+1);
            tree[v].l = tree[v*2].l;
            tree[v].r = tree[v*2+1].r;
        }
    }
    seg_tree(int dd){
        n = dd;
        tree.resize(2 * n + 1);
        build(1);
    }
    void apply(int v){
        if(tree[v].lazy == -1){
            return ;
        }
        tree[v].val = (tree[v].r - tree[v].l + 1) * tree[v].lazy;
        if(v >= n){
            
        }else{
            tree[v*2].lazy = tree[v].lazy;
            tree[v*2+1].lazy = tree[v].lazy;
        }
        tree[v].lazy = -1;
    }
    void change(int v, int l, int r, int x){
        apply(v);
        if(l <= tree[v].l && tree[v].r <= r){
            tree[v].lazy = x;
            apply();
        }else if(r < tree[v].l || tree[v].r < l){
            return ;
        }else{
            change(v*2, l, r, x);
            change(v*2+1, l, r, x);
            tree[v].val = tree[v*2].val + tree[v*2+1].val;
        }
    }
    int find(int v, int l, int r){
        apply(v);
        if(l <= tree[v].l && tree[v].r <= r){
            return tree[v].val;
        }else if(r < tree[v].l || tree[v].r < l){
            return 0;
        }else{
            return find(v*2, l, r) + find(v*2+1, l, r);
        }       
    }
};
