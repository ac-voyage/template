
/* find root(重心) */

void findroot(int u, int fa) {
	int i;
	size[u] = 1;
	f[u] = 0;
	for (i = last[u]; i; i = e[i][2]) {
		if (!vis[e[i][0]] && e[i][0] != fa) {
			findroot(e[i][0], u);
			size[u] += size[e[i][0]];
			if (f[u] < size[e[i][0]])
				f[u] = size[e[i][0]];	
		}
	}
	if (f[u] < ALL - size[u])
		f[u] = ALL - size[u];
	if (f[u] < f[root]) root = u;
}

/* --- da --- */

int dep[MAXN+1];
int ancestor[MAXN+1][MAXLGN];
int minw[MAXN+1][MAXLGN];

void dfs(int u, int fa)
{
    ancestor[u][0] = fa; dep[u] = dep[fa] + 1;
    for(int e = u[front];e;e = E[e].n)
    {
        int v = E[e].v, w = E[e].w;
        if(v != fa)
        {
            minw[v][0] = w;
            dfs(v, u);
        }
    }
}

void init_system(void)
{
    int i = 0, w = 0;
    int t = 0;
    dep[0] = -1;
    dfs(1,0);
    for(w = 1;(t=(1<<w)) < N;++w)
        for(i = 1;i <= N;++i) if( dep[i] >= t )
        {
            ancestor[i][w] = ancestor[ancestor[i][w-1]][w-1];
            minw[i][w] = min(minw[i][w-1], minw[ancestor[i][w-1]][w-1]);
        }
}

int query(int a, int b)
{
    if(dep[a] < dep[b]) return query(b,a);
    else    /* now dep[s] > dep[t] */
    {
        int i = 0;
        int maxbit = MAXLGN-1;
        int ret = INF;
        //while((1<<maxbit) <= dep[a]) maxbit++;
        /* first up a to same dep with b. */
        for(i = maxbit;i >= 0;i--)
            if(dep[a] - (1<<i) >= dep[b])
            {
                ret = min(ret, minw[a][i]);
                a = ancestor[a][i];
            }
        if(a == b) return ret;
        for(i = maxbit;i >= 0;i--)
            if(dep[a] - (1<<i) >= 0 && ancestor[a][i] != ancestor[b][i])
            {
                ret = min(ret, min(minw[a][i], minw[b][i]));
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
        ret = min(ret, min(minw[a][0], minw[b][0]));
        return ret;
    }
}
