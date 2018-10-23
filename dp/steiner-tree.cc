#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int limit = 1050;
const int INF = 1e9;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}
#define MP(i,j) make_pair(i,j)
#define se second
#define fi first
#define Pair pair<int,int>
int N, M, tot = 0;
int a[12][12], f[12][12][limit];
int xx[5] = {-1, +1, 0, 0};
int yy[5] = {0, 0, -1, +1};
int vis[12][12];
struct PRE {
    int x, y, S;
}Pre[12][12][limit];
queue<Pair>q;
void SPFA(int cur) {
    while(q.size() != 0) {
        Pair p = q.front();q.pop();
        vis[p.fi][p.se] = 0;
        for(int i = 0; i <4; i++) {
            int wx = p.fi + xx[i], wy = p.se + yy[i];
            if(wx < 1 || wx > N || wy < 1 || wy > M) continue;
            if(f[wx][wy][cur] > f[p.fi][p.se][cur] + a[wx][wy]) {
                f[wx][wy][cur] = f[p.fi][p.se][cur] + a[wx][wy];
                Pre[wx][wy][cur] = (PRE){p.fi, p.se, cur};
                if(!vis[wx][wy])
                    vis[wx][wy] = 1, q.push(MP(wx,wy));
            }
        }
    }
}
void dfs(int x, int y, int now) {
    vis[x][y] = 1;
    PRE tmp = Pre[x][y][now];
    if(tmp.x == 0 && tmp.y == 0) return;
    dfs(tmp.x, tmp.y, tmp.S);
    if(tmp.x == x && tmp.y == y) dfs(tmp.x, tmp.y, now - tmp.S);
}
int main() {
    //freopen("a.in", "r", stdin);
    N = read(); M = read();
    memset(f, 0x3f, sizeof(f));
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= M; j++) {
            a[i][j] = read();
            if(a[i][j] == 0)
                f[i][j][1 << tot] = 0, tot++;
        }
    int limit = (1 << tot) - 1;
    for(int sta = 0; sta <= limit; sta++) {
        for(int i = 1; i<= N; i++)
            for(int j = 1; j <= M;j++) {
                for(int s = sta; s; s = (s - 1) & sta) {
                    if(f[i][j][s] + f[i][j][sta - s] - a[i][j] < f[i][j][sta])
                        f[i][j][sta] = f[i][j][s] + f[i][j][sta - s] - a[i][j],
                        Pre[i][j][sta] = (PRE){i,j,s};
                }
                if(f[i][j][sta] < INF) q.push(MP(i,j)), vis[i][j] = 1;
            }
        SPFA(sta);
    }
    int ansx, ansy, flag = 0;
    for(int i = 1; i <= N && !flag; i++)
        for(int j = 1; j <= M; j++)
            if(!a[i][j]) 
                {ansx = i, ansy = j; flag = 1; break;}
    printf("%d\n",f[ansx][ansy][limit]); 
    memset(vis, 0, sizeof(vis));
    dfs(ansx, ansy, limit);
    for(int i = 1; i <= N; i++, puts("")) {
        for(int j = 1; j <= M; j++) {
            if(a[i][j] == 0) putchar('x');
            else if(vis[i][j]) putchar('o');
            else putchar('_');            
        } 
    } 
    return 0;
}