/* Shortest Path Dijstra, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>
#include <utility>

using namespace std;
typedef set< pair<int,int> > spii;

#define MAXN    512
#define MAXV    (MAXN*MAXN)

struct egde_t
{
    int id;
    int nxt;
};
int front[MAXV];
egde_t edg[MAXV<<3];
int nedges;
void add_edge(int u, int v)
{
    int newedge = ++nedges;
    edg[newedge].id = v;
    edg[newedge].nxt = u[front];
    u[front] = newedge;
}

int d[MAXV];
int vis[MAXN];
int solid[MAXV];

int dijstra(int s, int t)
{
    int v = s[front];
    spii q;
    q.insert(make_pair(0, s));
    while(!q.empty())
    {
        auto it = q.begin();
        int u = it->second;
        int v = u[front];
        q.erase(it);
        solid[u] = 1;
        if(u == t) break;
        while(v)
        {
            int w = edg[v].id;
            if(!solid[w])
            {
                if( (0==d[w]) || (d[u] + 1 < d[w]) )
                {
                    q.erase(make_pair(d[w],w));
                    d[w] = d[u] + 1;
                    q.insert(make_pair(d[w],w));
                }
            }
            v = edg[v].nxt;
        }
    }
    return d[t];
}
