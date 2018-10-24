int f[1<<M][N];
queue<int> q;
bool in[N];

void spfa(int S)
{
    while (!q.empty())
    {
        int now=q.front(); q.pop();
        in[now]=0;
        for (int i=st[now];i;i=way[i].nxt)
        {
            int y=way[i].y;
            if (f[S][y]>f[S][now]+val[y])
            {
                f[S][y]=f[S][now]+val[y];
                if (!in[y]) q.push(y),in[y]=1;
            }
        }
    }
}

void work()
{
    int cnt=0;
    memset(f,0x7f,sizeof(f));

    for (int i=1;i<=n;i++)
        if (!val[i]) f[1<<cnt][i]=0,cnt++;
    for (int S=1;S<(1<<cnt);S++)
    {
        for (s=(S-1)&S;s;s=(s-1)&S) 
            for (int i=1;i<=n;i++)
                f[S][i]=min(f[S][i],f[s][i]+f[S^s][i]-val[i]);
        for (int i=1;i<=n;i++)
            if (f[S][i]<INF&&!in[i])
                q.push(i),in[i]=1;
        spfa(S);
    }

    int ans=INF;
    for (int i=1;i<=n;i++) ans=min(ans,f[(1<<cnt)-1][i]);
    printf("%d\n",ans);
}
// --------------------- 
// 作者：Coco_T_ 
// 来源：CSDN 
// 原文：https://blog.csdn.net/wu_tongtong/article/details/78992913 
// 版权声明：本文为博主原创文章，转载请附上博文链接！