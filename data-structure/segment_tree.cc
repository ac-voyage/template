/* Segment tree (Interval tree, range tree), by Abreto <m@abreto.net>. */

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            /* merge n1 and n2 to ans. */
            return ans;
        }

        /* Data field */
        int l,r;
    }nodes[(STMAX+1)<<2];

    struct lazy_t
    {
        int marked; /* Optional */
        /* lazy mark. */

        lazy_t(void){clear();}
        void clear(void){marked=0;}
    }marks[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        /* Operations to single elements ... */
    }
    inline void maintain(int o)
    {
        nodes[o] = node_t::merge(nodes[o<<1], nodes[o<<1|1]);
    }

    /* Usage: build(1,1,n); */
    void build(int o, int l, int r) /* [l,r] */
    {
        if( r <= l )
        {
            maintain_leaf(o, l);
        } else {
            int mid = l+r>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    /* Modify all elements in [l,r] */
    void mark(lazy_t act, int o)
    {
        /* do something .. */
        marks[o].marked = 1;
    }

    /* Pass cached updates. */
    void pushdown(int o)
    {
        if( marks[o].marked )
        {
            mark(marks[o], o<<1);
            mark(marks[o], o<<1|1);
            marks[o].clear();
        }
    }

    /* Do act on all elements in [L,R] */
    void upd(int L, int R, lazy_t act, int o, int l, int r)
    {
        if( L <= l && r <= R )
        {
            mark(act, o);
        } else if (L <= R) {
            int mid = (l+r)>>1;
            pushdown(o);
            if( L <= mid ) upd(L, R, act, o<<1, l, mid);
            if( R > mid ) upd(L, R, act, o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    node_t qry(int L, int R, int o, int l, int r)
    {
        if(L <= l && r <= R)
            return nodes[o];
        else if (L <= R)
        {
            int mid = (l+r)>>1;
            pushdown(o);
            if(R <= mid) return qry(L,R,o<<1,l,mid);
            if(L > mid) return qry(L,R,o<<1|1,mid+1,r);
            return node_t::merge(qry(L,R,o<<1,l,mid),qry(L,R,o<<1|1,mid+1,r));
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    build(int n){N = n; build(1,1,N);}
    void update(int L, int R, lazy_t act) {upd(L,R,act,1,1,N);}
    node_t query(int L, int R) {return qry(L,R,1,1,N);}
};
