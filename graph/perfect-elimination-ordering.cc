/**
 * BZOJ 1006
 * [HNOI2008] 神奇的国度
 * 最大势法求完美消除序列
 * by Abreto<m@abreto.net>.
 **/
#include <cassert>
#include <cstdio>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
typedef vi::iterator vii;
#define pb push_back
#define MAXN 10100
#define MAXM 1000100

int n;
vi g[MAXN];
int ans;

struct node_t
{
    int v;
    node_t *nxt;
}node[MAXM << 2];
int used;
node_t *new_node(void)
{
    return node + (used ++);
}

node_t *f[MAXN];  /* head */
void lkto(int pos, int item)
{
    node_t *t = new_node();
    t->v = item; t->nxt = f[pos];
    f[pos] = t;
}

int usedby[MAXN];
int color[MAXN];
bitset<MAXN> added;
int label[MAXN], max_label;
void mcs(void)
{
    for (int i = 1; i <= n; i++) lkto(0, i);
    for (int i = n; i > 0; i--)
    {
        node_t *cur = f[max_label];
        assert(cur != NULL);
        while (added.test(cur->v))    /* already added */
        {
            cur = cur->nxt;
            while (NULL == cur)
                cur = f[ --max_label ];
        }
        f[ max_label ] = cur->nxt;
        while (max_label && NULL == f[max_label]) max_label--;
        int u = cur->v;
        added.set(u);
        /* the i-th is u */
        for (vii it = g[u].begin(); it != g[u].end(); it++)
        {
            int v = *it;
            if (!added.test(v))
            {
                label[v] ++;
                max_label = max(max_label, label[v]);
                lkto(label[v], v);
            }

            usedby[color[v]] = i;
        }
        for (int j = 1; j <= n; j++)
            if (usedby[j] != i)
            {
                color[u] = j;
                break;
            }
        ans = max(ans, color[u]);
    }
}

int main(void)
{
    int m;
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int ai, bi;
        scanf("%d%d", &ai, &bi);
        g[ai].pb(bi); g[bi].pb(ai);
    }
    mcs();
    printf("%d\n", ans);
    return 0;
}