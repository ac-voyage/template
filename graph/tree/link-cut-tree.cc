/* bzoj 1036 */
/* 树链剖分 */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    30030
#define MAXM    (MAXN<<1)
struct edge
{
    int v;
    edge *n;
    edge(void){}
    edge(int vv, edge *nn):v(vv),n(nn){}
};
typedef edge *ep;
int nE;
edge E[MAXM];
ep front[MAXN];
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v, u[front]);
    u[front] = &(E[ne]);
}

int n;
int fa[MAXN], son[MAXN], sz[MAXN], dep[MAXN];
int top[MAXN];
int id[MAXN]; int tot;

void calc(int u, int uf)
{
    dep[u] = dep[uf] + 1;
    fa[u] = uf;
    sz[u] = 1;
    son[u] = -1;
    for(ep e = u[front];e;e = e->n)
    {
        if(e->v != uf)
        {
            calc(e->v, u);
            sz[u] += sz[e->v];
            if( -1 == son[u] || sz[son[u]] < sz[e->v] )
                son[u] = e->v;
        }
    }
}
void link(int u, int f)
{
    id[u] = (++tot);
    top[u] = f;
    if(son[u] > 0)
    {
        link(son[u], f);
    }
    for(ep e = u[front];e;e = e->n)
    {
        if(e->v != fa[u] && e->v != son[u])
        {
            link(e->v, e->v);
        }
    }
}

/* 其实是树链剖分 */
void make_link_cut_tree(void)
{
    calc(1, 0);
    link(1, 1);
}

int w[MAXN];
int sum[MAXN<<2], mx[MAXN<<2];

void maintain(int o, int l, int r)
{
    sum[o] = sum[o<<1] + sum[o<<1|1];
    mx[o] = max(mx[o<<1], mx[o<<1|1]);
}
void build(int o = 1, int l = 1, int r = n)
{
    if(r == l)
    {
        sum[o] = w[l];
        mx[o] = w[l];
    } else {
        int mid = l+r>>1;
        build(o<<1, l, mid);
        build(o<<1|1, mid+1, r);
        maintain(o, l, r);
    }
}
void update(int p, int x, int o = 1, int l = 1, int r = n)
{
    if(p <= l && r <= p)
    {
        sum[o] = x;
        mx[o] = x;
    } else {
        int mid = l+r>>1;
        if(p <= mid) update(p,x,o<<1,l,mid);
        else update(p,x,o<<1|1,mid+1,r);
        maintain(o,l,r);
    }
}
int qs(int L, int R, int o = 1, int l = 1, int r = n)
{
    if(R < l || r < L) return 0;
    else if (L <= l && r <= R)
    {
        return sum[o];
    } else {
        int mid = l+r>>1;
        return qs(L,R,o<<1,l,mid)+qs(L,R,o<<1|1,mid+1,r);
    }
}
int qm(int L, int R, int o = 1, int l = 1, int r = n)
{
    if(L <= l && r <= R)
    {
        return mx[o];
    } else {
        int mid = l+r>>1;
        if(R <= mid) return qm(L, R, o<<1, l, mid);
        else if ( L > mid ) return qm(L, R, o<<1|1, mid+1, r);
        else return max(qm(L, R, o<<1, l, mid),qm(L, R, o<<1|1, mid+1, r));
    }
}

void change(int u, int t)
{
    update(id[u], t);
}
int qmax(int u, int v)
{
    int ret = -1000000000;
    while(top[u] != top[v])
    {
        if( dep[top[u]] > dep[top[v]] )
        {
            /* jump u */
            ret = max(ret, qm(id[top[u]], id[u]));
            u = fa[top[u]];
        } else {
            ret = max(ret, qm(id[top[v]], id[v]));
            v = fa[top[v]];
        }
    }
    ret = max(ret, qm(min(id[u],id[v]),max(id[u],id[v])));
    return ret;
}
int qsum(int u, int v)
{
    int ret = 0;
    while(top[u] != top[v])
    {
        if( dep[top[u]] > dep[top[v]] )
        {
            /* jump u */
            ret += qs(id[top[u]], id[u]);
            u = fa[top[u]];
        } else {
            ret += qs(id[top[v]], id[v]);
            v = fa[top[v]];
        }
    }
    ret += qs(min(id[u],id[v]),max(id[u],id[v]));
    return ret;
}

int main(void)
{
    int i;
    scanf("%d", &n);
    for(i = 1;i < n;++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    make_link_cut_tree();
    for(i = 1;i <= n;++i)
    {
        scanf("%d", &(w[id[i]]));
    }
    build();
    scanf("%d", &i);
    while(i--)
    {
        char command[8];
        int a, b;
        scanf("%s %d %d", command, &a, &b);
        if('C' == command[0]) change(a, b);
        else if ('M' == command[1]) printf("%d\n", qmax(a, b));
        else if ('S' == command[1]) printf("%d\n", qsum(a, b));
    }
    return 0;
}
