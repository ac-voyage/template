/* Max Flow Problem, by Abreto<m@abreto.net> */
#include <cstring>
#include "graph.hh"

template <int MAXN = 1000000, class V = int, class E = int>
struct graph
{
    int vis[MAXN];
    int path[MAXN];
    int dfs(int u, int t)
    {
        vis[u] = 1;
        if(u == t) return 1;
        for(auto e:vtx[u])
        {
            int v = e.v;
            if(!vis[v] && e.d && dfs(v,t))
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
            int minf = find_edge(s,path[s])->d;
            for(i = path[s];i != t;i = path[i])
                minf = min(minf, find_edge(i,path[i])->d);
            for(i = s;i != t;i = path[i])
            {
                grant_e(i, path[i], -minf);
                grant_e(path[i], i, minf);
            }
            flow += minf;
        }
        return flow;
    }
};
