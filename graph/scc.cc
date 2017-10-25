/* Kosaraju */
#define MAXN    10010
#define MAXM    100010
struct edge
{
    int v; edge *n;
    edge(void):v(0),n(NULL){}
    edge(int vv, edge *nn):v(vv),n(nn){}
};
int nE;
edge E[MAXM<<1];
edge *ori[MAXN];
edge *inv[MAXN];
void add_edge(edge *front[], int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v, u[front]);
    u[front] = &(E[ne]);
}
void connect(int u, int v)
{
    add_edge(ori, u, v);
    add_edge(inv, v, u);
}

int vis[MAXN];
int vst[MAXN];
void first_dfs(int u, int &sig)
{
    vis[u] = 1;
    for(edge *e = u[ori];e;e = e->n)
        if(!vis[e->v])
            first_dfs(e->v, sig);
    vst[++sig] = u;
}
int mark[MAXN];
void second_dfs(int u, int sig)
{
    vis[u] = 1;
    mark[u] = sig;
    for(edge *e = u[inv];e;e = e->n)
        if(!vis[e->v])
            second_dfs(e->v, sig);
}

int N, M;

int kosaraju(void)
{
    int i;
    int sig = 0;
    for(i = 0;i <= N;++i) vis[i] = 0;
    for(i = 1;i <= N;++i)
    {
        if(!vis[i])
            first_dfs(i, sig);
    }
    sig = 1; for(i = 0;i <= N;++i) vis[i] = 0;
    for(i = N;i > 0;--i)
    {
        if(!vis[vst[i]])
            second_dfs(vst[i], sig++);
    }
    for(i = 1;i <= N;++i)
        if(mark[i] != 1)
            return 0;
    return 1;
}


void clear(void)
{
    nE = 0;
    for(int i = 0;i <= N;++i)
    {
        ori[i] = inv[i] = NULL;
    }
}

/* Tarjan */
#define MAXN    10010
#define MAXM    100010
struct edge
{
    int v; edge *n;
    edge(void):v(0),n(NULL){}
    edge(int vv, edge *nn):v(vv),n(nn){}
};
typedef edge *ep;
int nE;
edge E[MAXM];
edge *front[MAXN];
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v, u[front]);
    u[front] = &(E[ne]);
}

int mark[MAXN];
int dfn[MAXN], low[MAXN];
int stk[MAXN]; int stk_top;

void tardfs(int u, int stamp, int &scc)
{
    mark[u] = 1;
    dfn[u] = low[u] = stamp;
    stk[stk_top++] = u;
    for(ep e = u[front];e;e = e->n)
    {
        if(0 == mark[e->v]) tardfs(e->v, ++stamp, scc);
        if(1 == mark[e->v]) low[u] = min(low[u], low[e->v]);
    }
    if(dfn[u] == low[u])
    {
        ++scc;
        do {
            low[stk[stk_top-1]] = scc;
            mark[stk[stk_top-1]] = 2;
        } while(stk[(stk_top--)-1] != u);
    }
}

int tarjan(int n)
{
    int scc = 0, lay = 1;
    for(int i = 1;i <= n;++i)
        if(0 == mark[i])
            tardfs(i, lay, scc);
    return scc;
}

int N, M;

void clear(void)
{
    nE = 0;
    for(int i = 0;i <= N;++i)
    {
        i[front] = NULL;
        mark[i] = low[i] = 0;
    }
    stk_top = 0;
}

/* Garbow */
#define MAXN    10010
#define MAXM    100010

struct edge
{
    int v; edge *n;
    edge(void):v(0),n(NULL){}
    edge(int vv, edge *nn):v(vv),n(nn){}
};
typedef edge *ep;

int nE;
edge E[MAXM];
edge *front[MAXN];
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v, u[front]);
    u[front] = &(E[ne]);
}

int stk1[MAXN], stk1t;
int stk2[MAXN], stk2t;
int low[MAXN], belg[MAXN];

void garbowdfs(int u, int lay, int &scc)
{
    stk1[++stk1t] = u; stk2[++stk2t] = u;
    low[u] = ++lay;
    for(ep e=u[front];e;e = e->n)
    {
        if(!low[e->v]) garbowdfs(e->v, lay, scc);
        else if (0 == belg[e->v])
            while(low[stk2[stk2t]] > low[e->v])
                --stk2t;
    }
    if(stk2[stk2t] == u)
    {
        stk2t--;
        scc++;
        do {
            belg[stk1[stk1t]] = scc;
        }while(stk1[stk1t--] != u);
    }
}

int grabow(int n)
{
    int i;
    int scc = 0, lay = 0;
    for(i = 0;i <= n;++i)
    {
        belg[i] = low[i] = 0;
    }
    for(i = 1;i <= n;++i)
        if(0 == low[i])
            garbowdfs(i, lay, scc);
    return scc;
}

int N, M;

void clear(void)
{
    nE = 0;
    for(int i = 0;i <= N;++i)
    {
        front[i] = NULL;
    }
}
