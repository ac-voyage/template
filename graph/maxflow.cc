/* Max Flow Problem, by Abreto<m@abreto.net> */

#include <bits/stdc++.h>
using namespace std;

#define MAXV    (100000)
#define MAXE    (1000000)
struct edge
{
    static int N;
    int v, w;
    edge *n;
    edge(void):v(0),w(0),n(NULL){}
    edge(int vv, int ww, edge *nn):v(vv),w(ww),n(nn){}
};
int nE;
edge E[MAXE];
edge *front[MAXV];
void add_edge(int u, int v, int w)
{
    int ne = ++nE;
    E[ne] = edge(v, w, u[front]);
    u[front] = &(E[ne]);
}
edge *find_edge(int u, int v)
{
    for(edge *e = u[front];e != NULL;e = e->n)
        if(e->v == v)
            return e;
    return NULL;
}
void grant_e(int u, int v, int w)
{
    edge *e = find_edge(u, v);
    if(NULL == e) add_edge(u,v,w);
    else e->w += w;
}

int vis[MAXV];
int path[MAXV];
int dfs(int u, int t)
{
    vis[u] = 1;
    if(u == t) return 1;
    for(edge *e = u[front];e != NULL;e = e->n)
    {
        int v = e->v;
        if(!vis[v] && e->w && dfs(v,t))
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
        int minf = find_edge(s,path[s])->w;
        for(i = path[s];i != t;i = path[i])
            minf = min(minf, find_edge(i,path[i])->w);
        for(i = s;i != t;i = path[i])
        {
            grant_e(i, path[i], -minf);
            grant_e(path[i], i, minf);
        }
        flow += minf;
    }
    return flow;
}

/* Dinic */
#define N 1000
#define INF 100000000

struct Edge
{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};

struct Dinic
{
    int n,m,s,t;//结点数，边数（包括反向弧），源点编号，汇点编号
    vector<Edge>edges;//边表，dges[e]和dges[e^1]互为反向弧
    vector<int>G[N];//邻接表，G[i][j]表示结点i的第j条边在e数组中的编号
    bool vis[N]; //BFS的使用
    int d[N]; //从起点到i的距离
    int cur[N]; //当前弧下标

    void addedge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        int  m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool bfs()
    {
        memset(vis,0,sizeof(vis));
        queue<int>Q;
        Q.push(s);
        d[s]=0;
        vis[s]=1;
        while(!Q.empty())
        {
            int x=Q.front();Q.pop();
            for(int i=0;i<G[x].size();i++)
            {
                Edge&e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow)//只考虑残量网络中的弧
                {
                    vis[e.to]=1;
                    d[e.to]=d[x]+1;
                    Q.push(e.to);
                }
            }

        }
        return vis[t];
    }

    int dfs(int x,int a)//x表示当前结点，a表示目前为止的最小残量
    {
        if(x==t||a==0)return a;//a等于0时及时退出，此时相当于断路了
        int flow=0,f;
        for(int&i=cur[x];i<G[x].size();i++)//从上次考虑的弧开始，注意要使用引用，同时修改cur[x]
        {
            Edge&e=edges[G[x][i]];//e是一条边
            if(d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0)
            {
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(!a)break;//a等于0及时退出，当a!=0,说明当前节点还存在另一个曾广路分支。

            }
        }
        return flow;
    }

    int Maxflow(int s,int t)//主过程
    {
        this->s=s,this->t=t;
        int flow=0;
        while(bfs())//不停地用bfs构造分层网络，然后用dfs沿着阻塞流增广
        {
            memset(cur,0,sizeof(cur));
            flow+=dfs(s,INF);
        }
        return flow;
    }
};

/* ISAP */
struct Edge{  
    int from,to,cap,flow;  
};  
const int maxn=650;  
const int INF=0x3f3f3f3f;  
struct ISAP{  
    int n,m,s,t;//结点数，边数（包括反向弧），源点编号，汇点编号  
    vector<Edge>edges;  
    vector<int>G[maxn];  
    bool vis[maxn];  
    int d[maxn];  
    int cur[maxn];  
    int p[maxn];  
    int num[maxn];  
    void AddEdge(int from,int to,int cap){  
        edges.push_back((Edge){from,to,cap,0});  
        edges.push_back((Edge){to,from,0,0});  
        m=edges.size();  
        G[from].push_back(m-2);  
        G[to].push_back(m-1);  
    }  
    bool RevBFS(){  
        memset(vis,0,sizeof(vis));  
        queue<int>Q;  
        Q.push(t);  
        d[t]=0;  
        vis[t]=1;  
        while(!Q.empty()){  
            int x=Q.front();Q.pop();  
            for(int i=0;i<G[x].size();i++){  
                Edge &e =edges[G[x][i]^1];  
                if(!vis[e.from]&&e.cap>e.flow){  
                    vis[e.from]=1;  
                    d[e.from]=d[x]+1;  
                    Q.push(e.from);  
                }  
            }  
        }  
        return vis[s];  
    }  
    int Augment(){  
        int x=t, a=INF;  
        while(x!=s){  
            Edge &e = edges[p[x]];  
            a= min(a,e.cap-e.flow);  
            x=edges[p[x]].from;  
        }  
        x=t;  
        while(x!=s){  
            edges[p[x]].flow+=a;  
            edges[p[x]^1].flow-=a;  
            x=edges[p[x]].from;  
        }  
        return a;  
    }  
    int Maxflow(int s,int t,int n){  
        this->s=s,this->t=t,this->n=n;  
        int flow=0;  
        RevBFS();  
        memset(num,0,sizeof(num));  
        for(int i=0;i<n;i++){  
            num[d[i]]++;  
        }  
        int x=s;  
        memset(cur,0,sizeof(cur));  
        while(d[s]<n){  
            if(x==t){  
                flow+=Augment();  
                x=s;  
            }  
            int ok=0;  
            for(int i=cur[x];i<G[x].size();i++){  
                Edge &e =edges[G[x][i]];  
                if(e.cap>e.flow&&d[x]==d[e.to]+1){  
                    ok=1;  
                    p[e.to]=G[x][i];  
                    cur[x]=i;  
                    x=e.to;  
                    break;  
                }  
            }  
            if(!ok){  
                int m=n-1;  
                for(int i=0;i<G[x].size();i++){  
                    Edge &e =edges[G[x][i]];  
                    if(e.cap>e.flow)  
                        m=min(m,d[e.to]);  
                }  
                if(--num[d[x]]==0)  
                    break;  
                num[d[x]=m+1]++;  
                cur[x]=0;  
                if(x!=s)  
                    x=edges[p[x]].from;  
            }  
        }  
        return flow;  
    }  
};  
int main(){  
    int n,m,a,b,c,res;  
    while(scanf("%d%d",&m,&n)!=EOF){  
        ISAP tmp;  
        for(int i=0;i<m;i++){  
            scanf("%d%d%d",&a,&b,&c);  
            tmp.AddEdge(a,b,c);  
        }  
        res=tmp.Maxflow(1,n,n);  
        printf("%d\n",res);  
    }  
    return 0;  
}
