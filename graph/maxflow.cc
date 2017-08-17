/* Max Flow Problem, by Abreto<m@abreto.net> */

#define MAXV    (100000)
#define MAXE    (1000000)
struct edge
{
    static int N;
    int v, w;
    edge *n;
    edge(void):v(0),w(0),n(NULL){}
    edge(int vv, int ww, edge *nn):v(vv),w(ww),n(nn){}
};
int nE;
edge E[MAXE];
edge *front[MAXV];
void add_edge(int u, int v, int w)
{
    int ne = ++nE;
    E[ne] = edge(v, w, u[front]);
    u[front] = &(E[ne]);
}
edge *find_edge(int u, int v)
{
    for(edge *e = u[front];e != NULL;e = e->n)
        if(e->v == v)
            return e;
    return NULL;
}
void grant_e(int u, int v, int w)
{
    edge *e = find_edge(u, v);
    if(NULL == e) add_edge(u,v,w);
    else e->w += w;
}

int vis[MAXV];
int path[MAXV];
int dfs(int u, int t)
{
    vis[u] = 1;
    if(u == t) return 1;
    for(edge *e = u[front];e != NULL;e = e->n)
    {
        int v = e->v;
        if(!vis[v] && e->w && dfs(v,t))
        {
            path[u] = v;
            return 1;
        }
    }
    return 0;
}
int find_path(int s, int t)
{
    memset(vis, 0, sizeof(vis));
    return dfs(s,t);
}
int max_flow(int s, int t)
{
    int flow = 0;
    while(find_path(s,t))
    {
        int i = 0;
        int minf = find_edge(s,path[s])->w;
        for(i = path[s];i != t;i = path[i])
            minf = min(minf, find_edge(i,path[i])->w);
        for(i = s;i != t;i = path[i])
        {
            grant_e(i, path[i], -minf);
            grant_e(path[i], i, minf);
        }
        flow += minf;
    }
    return flow;
}
