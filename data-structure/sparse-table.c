/* RMQ with Sparse Table, by Abreto <m@abreto.net>. */

int min(int a, int b)
{
    return (a<b)?a:b;
}

#define MAXN    100001
#define MAXLOG  32

int N;
int A[MAXN];    /* indexed from 0. */
int st[MAXN][MAXLOG];

void st_init()
{
    int i = 0, j = 0, t = 0;
    for(i = 0;i < N;++i) st[i][0] = A[i];
    for(j = 1;(t=(1<<j)) <= N;++j)
        for(i = 0;(i+t-1) < N;++i)
            st[i][j] = min(st[i][j-1], st[i+(t>>1)][j-1]);
            /* st(i,j) = min(st(i,j-1), st(i+2^(j-1),j-1)). */
}

int st_query(int l, int r)
{
    int k = 0;
    while((1<<(k+1)) <= (r-l+1)) k++;
    return min(st[l][k], st[r-(1<<k)+1][k]);
}
