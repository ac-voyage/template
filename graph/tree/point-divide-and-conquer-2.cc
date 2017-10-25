/* 2016 ACM/ICPC Asia Regional Dalian. Problem , by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

/* offset in [1,k] */
#define GET(i,offset)   (((i)>>((offset)-1))&1)
#define SET(i,offset)   ((i)|(1<<((offset)-1)))
#define REV(i,offset)   ((i)^(1<<((offset)-1)))

#define MAXN    (50005)
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
int label[MAXV];    /* each kind */
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v, u[front]);
    u[front] = &(E[ne]);
}

int n, k;
ll ans;
int all_kind;

int ndel;
int del[MAXV];
namespace findroot
{
    int ALL;
    ll nfind;
    ll vis[MAXV];
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
            if((del[v] != ndel) && (vis[v] != nfind) && (v != fa))
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

namespace workspace
{
    ll cnt[1024];
    int dp[MAXV];
    void dfs(int u, int fa)
    {
        dp[u] = dp[fa] | label[u];
        cnt[dp[u]] ++;
        /* dig into children */
        for(edge *e = u[front];e;e = e->n)
        {
            int v = e->v;
            if((del[v] != ndel) && (v != fa))
            {
                dfs(v, u);
            }
        }
    }
    inline void clear(void)
    {
        for(int i = 1;i <= all_kind;++i)
            cnt[i] = 0;
    }
    inline void work(int u)
    {
        dp[u] = label[u];
        cnt[dp[u]] ++;
        for(edge *e = u[front];e;e = e->n)
            if((del[e->v] != ndel))
                dfs(e->v, u);
    }
    inline void show(void)
    {
        for(int i = 0;i <= all_kind;++i)
            printf("cnt[%d] = %lld\n", i, cnt[i]);
        for(int i = 1;i <= n;++i)
            printf("dp[%d] = %d\n", i, dp[i]);
    }
};


ll count(int u, int p)
{
    ll ret = 0;
    workspace::clear();
    //printf("%d,%d  :\n", u, p);
    if(-1 == p)
    {
        for(edge *e = u[front];e;e = e->n)
            if(((del[e->v]) != ndel))
                workspace::work(e->v);
        p = label[u];
        /* single end */
        for(int i = 1;i <= all_kind;i++)
            if(all_kind == (i|p))
                ret += (workspace::cnt[i]<<1);
    } else {
        workspace::work(u);
    }
    //workspace::show();
    for(int i = 1;i <= all_kind;++i)
        if( workspace::cnt[i] > 0 )
            for(int j = 1;j <= all_kind;++j)
                if(all_kind == (i|p|j))
                    ret += workspace::cnt[i] * workspace::cnt[j];
    //printf("%lld\n", ret);
    return ret;
}

void handle(int u)
{
    //printf("proccessing %d\n", u);
    del[u] = ndel; /* delete current root. */
    ans += count(u, -1);
    /* do something */
    for(edge *e = u[front];e;e = e->n)
    {
        int v = e->v;
        if(del[v] != ndel)
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

void clear(void)
{
    int i;
    ans = 0;
    nE = 0;
    for(i = 0;i <= n;++i)
    {
        front[i] = NULL;
    }
    //findroot::nfind = 0;
    ndel++;
}

void mozhu(void)
{
    int i = 0;
    int li;
    for(i = 1;i <= n;++i)
    {
        scanf("%d", &li);
        label[i] = 1<<(li-1);
    }
    for(i = 1;i < n;++i)
    {
        int ai, bi;
        scanf("%d %d", &ai, &bi);
        add_edge(ai, bi); add_edge(bi, ai);
    }
    all_kind = (1<<k)-1;
    proc();
    if(1 == k) ans += n;
    printf("%lld\n", ans);
}

int main(void)
{
    while( EOF != scanf("%d%d", &n, &k) )
    {
        clear();
        mozhu();
    }
    return 0;
}
