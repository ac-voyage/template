/* Tree::Point divide and conquer, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define MAXN    (100001)
#define MAXV    (MAXN+1)
#define MAXE    (MAXN<<1)
struct edge
{
    int v;
    edge *n;
    edge(void):v(0),n(NULL){}
    edge(int vv,edge *nn):v(vv),n(nn){}
};
int nE;
edge E[MAXE];
edge *front[MAXV];
int label[MAXV];    /* 0 for '(', 1 for ')' */
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v, u[front]);
    u[front] = &(E[ne]);
}

int n;
ll ans;

char del[MAXV];
namespace findroot
{
    int ALL;
    int nfind;
    int vis[MAXV];
    int size[MAXV];
    int f[MAXV];
    int root;
    void __find(int u, int fa)
    {
        vis[u] = nfind;
        size[u] = 1;
        f[u] = 0;
        for(edge *e=u[front];e;e = e->n)
        {
            int v = e->v;
            if((!del[v]) && (vis[v] != nfind) && (v != fa))
            {
                __find(v, u);
                size[u] += size[v];
                if(f[u] < size[v])  f[u] = size[v];
            }
        }
        if(f[u] < ALL - size[u])  f[u] = ALL - size[u];
        if(f[u] < f[root])  root = u;
    }
    int find(int u, int all)
    {
        ++nfind;
        ALL = all;
        f[root = 0] = MAXV;
        __find(u,0);
        return root;
    }
}

namespace workspaces
{
    int maxdep;
    int dep[MAXV];
    ll cntin[MAXV], cntout[MAXV];
    int in[2][MAXV];    /* 0 for '(', 1 for ')' */
    int out[2][MAXV];
    void getdeep(int u, int fa)
    {
        dep[u] = dep[fa] + 1;
        if(dep[u] > maxdep) maxdep = dep[u];
        for(edge *e = u[front];e;e = e->n)
            if((!del[e->v]) && (fa != e->v))
                getdeep(e->v, u);
    }
    void dfs(int u, int fa)
    {
        { /* out from root */
            out[0][u] = out[0][fa];
            out[1][u] = out[1][fa];
            if(0 == label[u])   /* meet '(' */
            {
                out[0][u]++;
            } else {    /* meet ')' */
                if(out[0][u]) out[0][u]--;
                else out[1][u]++;
            }
            if(out[0][u] == 0)
                cntout[out[1][u]]++;
        }
        { /* in to root */
            in[0][u] = in[0][fa]; in[1][u] = in[1][fa];
            if(0 == label[u])   /* meet '(' */
            {
                if(in[1][u]) in[1][u]--;
                else in[0][u]++;
            } else {    /* meet ')' */
                in[1][u]++;
            }
            if(0 == in[1][u])
                cntin[in[0][u]]++;
        }
/* do something */
        for(edge *e = u[front];e;e = e->n)
        {
            int v = e->v;
            if((!del[v]) && (v != fa))
            {
                dfs(v, u);
            }
        }
    }
    inline void init_maxdep(void) {maxdep = 0;}
    inline void update_maxdep(int u)
    {
        dep[u] = 1;
        if(dep[u] > maxdep) maxdep = dep[u];
        for(edge *e = u[front];e;e = e->n)
            if((!del[e->v]))
                getdeep(e->v, u);
    }
    inline void clear(void)
    {
        for(int i = 0;i <= maxdep+1;++i)
            cntin[i] = cntout[i] = 0;
    }
    inline void work(int u)
    {
        in[0][u] = in[1][u] = out[0][u] = out[1][u] = 0;
        in[label[u]][u] = out[label[u]][u] = 1;
        if(out[0][u] == 0) cntout[out[1][u]]++;
        if(0 == in[1][u]) cntin[in[0][u]]++;
        /* update in and out if neccessary */
        for(edge *e = u[front];e;e = e->n)
            if(!(del[e->v]))
                dfs(e->v, u);
    }
};

ll count(int u, int p)
{
    ll ret = 0;
    workspace::init_maxdep();
    workspace::update_maxdep(u);
    workspace::clear();
    if(-1 == p)
    {
        for(edge *e = u[front];e;e = e->n)
            if((!(del[e->v])))
                workspace::work(e->v);
        p = label[u];
        /* single end */
        if(0 == p) ret = workspace::cntout[1];
        else ret = workspace::cntin[1];
    } else {
        workspace::work(u);
    }
    if(0 == p)  /* p is '(' */
    {
        for(int i = 0;i < workspace::maxdep;++i)    /* concatenation */
            ret += workspace::cntin[i] * workspace::cntout[i+1];
    } else {    /* p is ')' */
        for(int i = 0;i < workspace::maxdep;++i)    /* concatenation */
            ret += workspace::cntin[i+1] * workspace::cntout[i];
    }
    return ret;
}

void handle(int u)
{
    del[u] = 1; /* delete current root. */
    ans += count(u, -1);
    /* do something */
    for(edge *e = u[front];e;e = e->n)
    {
        int v = e->v;
        if(!del[v])
        {
            ans -= count(v, label[u]);
            /* do something */
            int r = findroot::find(v, findroot::size[v]);
            handle(r);
        }
    }
}

void proc(void)
{
    int r = findroot::find(1,n);
    handle(r);
}

char ls[MAXV+1];
int main(void)
{
    int i = 0;
    scanf("%d", &n);
    scanf("%s", ls);
    for(i = 0;i < n;++i)
        label[i+1] = ls[i] - '(';
    for(i = 1;i < n;++i)
    {
        int ai, bi;
        scanf("%d %d", &ai, &bi);
        add_edge(ai, bi); add_edge(bi, ai);
    }
    proc();
    printf("%lld\n", ans);
    return 0;
}
