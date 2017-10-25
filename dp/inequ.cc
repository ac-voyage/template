/*
 * 四边形不等式
 * 
 * 如果 dp(i,j) 满足 dp(i,j)<=dp(i,j+1)<=dp(i+1,j+1)
 * 那么决策 s(i,j) 满足 s(i,j)<=s(i,j+1)<=s(i+1,j+1)
 * 可以变形为:
 *      s(i-1,j) <= s(i,j) <= s(i,j+1)  // i增j减 
 *  或
 *      s(i,j-1) <= s(i,j) <= s(i+1,j)  // 区间长度L增
 */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    1024
#define inf     (0x3fffffff)

int n, m;
int v[MAXN];
int s[MAXN];
int w[MAXN][MAXN];
int dp[MAXN][MAXN];
int c[MAXN][MAXN];

int wa(void)
{
    int i, j, k;
    for(i = 1;i <= n;++i)
    {
        scanf("%d", v+i);
        s[i] = v[i] + s[i-1];
    }
    for(i = 1;i <= n;++i)
    {
        w[i][i] = 0;
        for(j = i+1;j <= n;++j)
            w[i][j] = w[i][j-1] + v[j] * (s[j-1] - s[i-1]);
    }
    /* doing dp */
    for(i = 1;i <= n;++i)
    {
        dp[i][0] = w[1][i];
        c[i][0] = 1; c[i][i] = i-1;
        for(j = i-1;j > 0;j--)
        {
            dp[i][j] = inf;
            for(k = c[i-1][j];k <= c[i][j+1];++k)
                if(dp[k][j-1]+w[k+1][i] <= dp[i][j])
                {
                    dp[i][j] = dp[k][j-1] + w[k+1][i];
                    c[i][j] = k;
                }
        }
    }
    /* dp done */
    return dp[n][m];
}

int main(void)
{
    while(EOF != scanf("%d%d", &n, &m) && n && m)
    {
        printf("%d\n", wa());
    }
    return 0;
}
