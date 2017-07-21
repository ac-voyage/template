/* Euler path, by Abreto<m@abreto.net>. */
#define MAXV    (1024)
#define MAXE    (MAXV*MAXV)

typedef struct
{
    int id;
    int nxt;
    int del;
}egde_t;
int front[MAXV];
egde_t edg[MAXE];
int d[MAXV];
int ind[MAXV], outd[MAXV];
int nedges;
void add_edge(int u, int v)
{
    int newedge = ++nedges;
    edg[newedge].id = v;
    edg[newedge].nxt = u[front];
    edg[newedge].del = 0;
    u[front] = newedge;
    outd[u]++; ind[v]++;
    d[u]++; d[v]++;
}
void del_edge(int u, int v)
{
    int e = 0;
    for(e=u[front];e;e=edg[e].nxt)
        if(edg[e].id==v)
        {
            edg[e].del = 1;
            outd[u]--; ind[v]--;
            d[u]--; d[v]--;
            return;
        }
}

int path[MAXV];
int l;

void add2path(int u)
{
    path[l++] = u;
}

/* Directed graph */
void euler(int x)
{
    if(outd[x])
    {
        int e = 0;
        for(e=x[front];e;e=edg[e].nxt)
            if(!edg[e].del)
            {
                int v = edg[e].id;
                del_edge(x,v);
                euler(v);
            }
    }
    add2path(x);
}

/* Undirected graph */
void euler(int x)
{
    if(d[x])
    {
        int e = 0;
        for(e=x[front];e;e=edg[e].nxt)
            if(!edg[e].del)
            {
                int v = edg[e].id;
                del_edge(x,v); del_edge(v,x);
                euler(v);
            }
    }
    add2path(x);
}
