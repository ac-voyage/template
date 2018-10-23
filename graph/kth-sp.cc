/**
 * poj
 * Problem#2449
 * Accepted
 * Time: 250ms
 * Memory: 9252k
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cctype>
#include <cmath>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
using namespace std;
typedef bool boolean;

typedef class Edge {
    public:
        int end;
        int next;
        int w;
        
        Edge(int end = 0, int next = -1, int w = 0):end(end), next(next), w(w) {        }
}Edge;

const int N = 1e3, M = 1e5;

typedef class MapManager {
    public:
        int cnt;
        int h[N + 5];
        Edge edge[M + 5];
        
        MapManager() {        }
        MapManager(int n):cnt(-1) {
//            h = new int[(n + 1)];
//            edge = new Edge[(m + 1)];
            memset(h, -1, sizeof(int) * (n + 1));
        }
        
        inline void addEdge(int u, int v, int w) {
            edge[++cnt] = (Edge(v, h[u], w));
//            h[u] = (signed)edge.size() - 1;
            h[u] = cnt; 
        }
        
        inline int start(int node) {    return h[node];        }
        
        Edge& operator [] (int pos) {
            return edge[pos];
        }
}MapManager;
#define m_endpos -1

int n, m;
MapManager g;
MapManager rg;
int s, t, k;
int ds[N + 5];

inline void init() {
    scanf("%d%d", &n, &m);
    memset(g.h, -1, sizeof(int) * (n + 1));
    memset(rg.h, -1, sizeof(int) * (n + 1));
    for(int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g.addEdge(u, v, w);
        rg.addEdge(v, u, w);
    }
    scanf("%d%d%d", &s, &t, &k);
//    ds = new int[(n + 1)];
}

#define g rg
#define f ds
#define que que1
boolean vis[N + 5];
queue<int> que;
boolean spfa(int s, int t) {
    memset(f, 0x7f, sizeof(int) * (n + 1));
    memset(vis, false, sizeof(boolean) * (n + 1));
    que.push(s);
    f[s] = 0;
    while(!que.empty()) {
        int e = que.front();
        que.pop();
        vis[e] = false;
        for(int i = g.start(e); i != m_endpos; i = g[i].next) {
            int& eu = g[i].end;
//            cout << e << " " << eu << " " << i <<endl;
            if(f[e] + g[i].w < f[eu]) {
                f[eu] = f[e] + g[i].w;
                if(!vis[eu]) {
                    que.push(eu);
                    vis[eu] = true;
                }
            }
        }
    }
    return (f[t] != 0x7f7f7f7f);
}
#undef g
#undef f
#undef que

typedef class Status {
    public:
        int node;
        int dis;
        int priority;
        
        Status(int node = 0, int dis = 0):node(node), dis(dis), priority(h()) {        }
        
        int h() {
            return dis + ds[node];
        }
        
        boolean operator < (Status b) const {
            return priority > b.priority;
        }
}Status;

int label[N + 5];
priority_queue<Status> que;
int bfs(int s, int t) {
    if(s == t)    k++;
//    label = new int[(n + 1)];
    memset(label, 0, sizeof(int) * (n + 1));
    que.push(Status(s, 0));
    while(!que.empty()) {
        Status e = que.top();
        que.pop();
        label[e.node]++;
        if(e.node == t && label[e.node] == k)
            return e.dis;
        for(int i = g.start(e.node); i != m_endpos; i = g[i].next) {
            if(label[g[i].end] < k) 
                que.push(Status(g[i].end, e.dis + g[i].w));
        } 
    }
    return -1;
}

inline void solve() {
    if(!spfa(t, s)) {
        puts("-1");
        return;
    }
    printf("%d", bfs(s, t));
}

int main() {
    init();
    solve();
    return 0;
}