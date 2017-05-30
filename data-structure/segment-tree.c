/* Segment tree (Interval tree, range tree), by Abreto <m@abreto.net>. */

#define MAXN    1000001

typedef struct
{
    int l,r;
    /* Data field */
}node_t;

node_t merge(node_t n1, node_t n2)
{
    node_t ans;
    ans.l = n1.l; ans.r = n2.r;
    /* merge n1 and n2 to ans. */
    return ans;
}

typedef struct
{
  int marked; /* Optional */
  /* lazy mark. */
}lazy_t;

int A[MAXN];
node_t nodes[MAXN<<2];
lazy_t marks[MAXN<<2];

void maintain_leaf(int o, int idx)
{
    nodes[o].l = nodes[o].r = idx;
    /* Operations to single elements ... */
}
void maintain(int o)
{
    nodes[o] = merge(nodes[o<<1], nodes[o<<1|1]);
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

/* Set A[p]=v. Usage: modify(p, v, 1, 1, n); */
void modify(int p, int v, int o, int l, int r)
{
    if( r - l < 2 )
    {
        maintain_leaf(o, v);
    } else {
        int mid = (l+r)/2;
        if( p <= mid ) modify(p, v, o*2, l, mid);
        else modify(p, v, o*2+1, mid, r);
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
        marks[o].marked = 0;
    }
}
