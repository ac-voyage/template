#include <bits/stdc++.h>

using namespace std;

namespace two_sat
{
    const int maxn = 100000;
    const int maxm = 1000000;
    struct edge
    {
        int v; edge *n;
        edge(void):v(0),n(NULL){}
        edge(int vv, edge *nn):v(vv),n(nn){}
    };
    typedef edge *ep;
    int n; int nE;
    edge E[maxm];
    ep front[maxn];
    void add_edge(int u, int v)
    {
        int ne = ++nE;
        E[ne] = edge(v, u[front]);
        u[front] = &(E[ne]);
    }
    /* (x = xval or y = yval), indexed from 0 */
    void add_clause(int x, int xv, int y, int yv)
    {
        x = x*2 + xv; y = y*2 + yv;
        add_edge(x^1, y); add_edge(y^1, x);
    }

    char mark[maxn<<1];
    int S[maxn<<1], c;
    void init(int N)
    {
        n = N;
        for(int i = 0;i < n*2;++i)
        {
            i[front] = NULL;
            i[mark] = 0;
        }
        nE = 0;
    }

    int dfs(int x)
    {
        if(mark[x^1]) return 0;
        if(mark[x]) return 1;
        mark[x] = 1;
        S[c++] = x;
        for(ep e = x[front];e;e = e->n)
            if(!dfs(e->v)) return 0;
        return 1;
    }

    int solve(void)
    {
        for(int i = 0;i < n*2;i += 2)
            if(!mark[i] && !mark[i+1])
            {
                c = 0;
                if(!dfs(i))
                {
                    while(c > 0) mark[S[--c]] = 0;
                    if(!dfs(i+1)) return 0;
                }
            }
        return 1;
    }
}
