/* Shortest Path Fast Algorithm, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

#define MAXN    128

struct edge
{
    int v;
    int w;
    int n;
};
edge edg[MAXN<<1];
int nedg;
int indegree[MAXN];
int front[MAXN];
int find_edge(int u, int v)
{
    int e = u[front];
    while(e)
    {
        if(edg[e].v == v) return e;
        e = edg[e].n;
    }
    return 0;
}
void add_edge(int u, int v, int w)
{
    int e = find_edge(u,v);
    if(0==e)
    {
        int newnode = ++nedg;
        edg[newnode].v = v;
        edg[newnode].w = w;
        edg[newnode].n = u[front];
        u[front] = newnode;
        indegree[v]++;
    } else {
        edg[e].w = (w < edg[e].w)?w:(edg[e].w);
    }
}

int n;

char inq[MAXN];
int vis[MAXN];
int d[MAXN];
int spfa(int s) /* return 1 if fuhuan exists. */
{
    queue<int> q;
    memset(inq, 0, sizeof(inq));
    memset(d, -1, sizeof(d));
    memset(vis, 0, sizeof(vis));
    d[s] = 0; inq[s] = 1;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        printf("proc %d..\n", u);
        inq[u] = 0;
        if(vis[u]++ > n)
            return 1;
        for(int e = front[u];e;e = edg[e].n)
        {
            int v = edg[e].v, w = edg[e].w;
            if( -1==d[v] || d[u] + w < d[v] )
            {
                d[v] = d[u] + w;
                if(!inq[v])
                {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return 0;
}
