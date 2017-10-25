
int top = 0;
for( int i=1; i<=n; i++ )
{
    if( ap[i] > dp[top] ){ // 如果大于 "模拟栈" 的栈顶元素直接 入栈 长度加 1  
        top++;
        dp[top] = ap[i];
        continue; 
    }
    int m = ap[i];
    // lower_bound 前闭后开 返回不小于 m 的最小值的位置 
    pos = lower_bound(dp,dp+top,m)-dp; // 注意减去dp 
    if( dp[pos] > ap[i])
    dp[pos] = ap[i];
}
