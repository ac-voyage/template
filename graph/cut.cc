Finding cut edges
The code below works properly because the lemma above (first lemma):
h[root] = 0
par[v] = -1
dfs (v):
        d[v] = h[v]
        color[v] = gray
        for u in adj[v]:
                if color[u] == white
                        then par[u] = v and dfs(u) and d[v] = min(d[v], d[u])
                        if d[u] > h[v]
                                then the edge v-u is a cut edge
                else if u != par[v])
                        then d[v] = min(d[v], h[u])
        color[v] = black
In this code, h[v] =  height of vertex v in the DFS tree and d[v] = min(h[w] where there is at least vertex u in subtree of v in the DFS tree where there is an edge between u and w). 

Finding cut vertices
The code below works properly because the lemma above (first lemma):
h[root] = 0
par[v] = -1
dfs (v):
        d[v] = h[v]
        color[v] = gray
        for u in adj[v]:
                if color[u] == white
                        then par[u] = v and dfs(u) and d[v] = min(d[v], d[u])
                        if d[u] >= h[v] and (v != root or number_of_children(v) > 1)
                                then the edge v is a cut vertex
                else if u != par[v])
                        then d[v] = min(d[v], h[u])
        color[v] = black
In this code, h[v] =  height of vertex v in the DFS tree and d[v] = min(h[w] where there is at least vertex u in subtree of v in the DFS tree where there is an edge between u and w).
