/* Graph Theory Base, by Abreto<m@abreto.net>. */
#include <set>

using namespace std;

#ifndef NULL
#define NULL (0)
#endif

template <int MAXN = 1000000, class V = int, class E = int>
struct graph
{
    struct edge{int v;E d;edge(int vv,E dd):v(vv),d(dd){}};
    struct edgeless{bool operator()(const edge& x,const edge& y)const{return (x.v)<(y.v);}};

    V wgt[MAXN+1];
    multiset<edge,edgeless> vtx[MAXN+1];

    void grant_w(int u, V d) {wgt[u]+=d;}
    void add_edge(int u, int v, E d = E()) {vtx[u].insert(edge(v,d));}
    void add_biedge(int u, int v, E d = E()) {add_edge(u,v,d);add_edge(v,u,d);}
    edge* find_edge(int u, int v) {auto it = vtx[u].find(edge(v,E()));if(it!=vtx[u].end())return &(*it);else return NULL;}
    void grant_e(int u, int v, E d) {edge *e=find_edge(u,v);if(NULL==e)add_edge(u,v,d);else e->d+=d;}
};
