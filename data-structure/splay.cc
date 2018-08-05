/* HDU 3487 - Play with Chain, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    300300

int n, m;

#define LC(p)   ch[p][0]
#define RC(p)   ch[p][1]
#define TARGET(p)	LC(RC(p))

int nodes;
int val[MAXN], ch[MAXN][2], fa[MAXN], sz[MAXN];
int rev[MAXN];

inline int new_node(int v, int f)
{
    int p = (++nodes);
    val[p] = v; fa[p] = f;
    ch[p][0] = ch[p][1] = rev[p] = 0;
    sz[p] = 1;
    return p;
}
inline void maintain(int p)
{
    if (p) { sz[p] = sz[LC(p)] + sz[RC(p)] + 1; }
}
inline void make_child(int f, int d, int p)	/* make p the d-th ch of f */
{
	ch[f][d] = p;
	if(p) fa[p] = f;
}
inline void myrev(int p)
{
	if (p)
	{
	    rev[p] ^= 1;
	    swap(LC(p), RC(p));
	}
}
inline void pushdown(int p)
{
    if(p && rev[p])
    {
        if(LC(p)) myrev(LC(p));
        if(RC(p)) myrev(RC(p));
        rev[p] = 0;
    }
}
int build(int f = 0, int l = 0, int r = n+1)
{
	if(r < l) return 0;
    if(l == r) return new_node(l, f);
    int mid = l+r>>1;
    int p = new_node(mid, f);
    LC(p) = build(p, l, mid-1);
    RC(p) = build(p, mid+1, r);
	maintain(p);
    return p;
}
inline int which(int p)    /* return 1 if p is a right child or 0 if p is a left child. */
{
    return (RC(fa[p]) == p);
}
inline int rotate(int p)   /* rotate p to its father. [!] make sure p is not global root. */
{
    int f = fa[p], ff = fa[f];
	if(0 == f) return p;	/* p is global root */
	pushdown(f); pushdown(p);
    int d = which(p), df = which(f);
	make_child(f, d, ch[p][d^1]);
	make_child(p, d^1, f);
	maintain(f); maintain(p);
	fa[p] = ff;
	if(ff) ch[ff][df] = p;
	return p;
}
inline int splay(int p, int fr)	/* splay p to the son of fr, return p. */
{
	pushdown(p);
	while(fa[p] != fr)
	{
		int f = fa[p], dp = which(p);
		if(fa[f] == fr)
		{
			return rotate(p);
		} else {
			int df = which(f);
			if(dp == df)
			{
				rotate(f);
			} else {
				rotate(p);
			}
			rotate(p);
		}
	}
	return p;
}
inline int get_k_th(int root, int k)
{
	int p = root;
	int rank;
	while(k != (rank = (sz[LC(p)] + 1)))
	{
		pushdown(p);
		if(k < rank) p = LC(p);
		else {k -= rank; p = RC(p);}
	}
	return splay(p, fa[root]);
}
inline int merge(int left, int right)
{
	pushdown(left);
	if(RC(left)) left = get_k_th(left, sz[left]);
	RC(left) = right;	maintain(left);
	fa[right] = left;
	return left;
}
inline int split(int root, int d)	/* split ch[root][d], return the root of splited out. */
{
	pushdown(root);
	int child = ch[root][d];
	ch[root][d] = 0; maintain(root);
	fa[child] = 0;
	return child;
}
inline int concat(int root, int d, int p)	/* make p be ch[root][d], return root */
{
	pushdown(root);
	ch[root][d] = p; fa[p] = root;
	maintain(root);
	return root;
}

void myclear(void)
{
    nodes = 0;
}

int ans[MAXN];
void inorder(int p, int &pos)
{
	if(0 == p) return;
	pushdown(p);
	inorder(LC(p), pos);
	if( (0 < val[p]) && (val[p] < n+1) ) ans[pos++] = val[p];
	inorder(RC(p), pos);
}

void handle()
{
    int i;
    int root;
    myclear();
    root = build(0);
    while(m--)
    {
        char command[8];
        int a, b, c; int tar;
        scanf("%s%d%d", command, &a, &b);
        if('C' == command[0])
        {
            scanf("%d", &c);
			root = get_k_th(root, a);
			RC(root) = get_k_th(RC(root), b-a+2);
			tar = split(RC(root), 0); maintain(root);
			root = get_k_th(root, c+1);
			RC(root) = get_k_th(RC(root), 1);
			RC(root) = concat(RC(root), 0, tar); maintain(root);
        } else {
            root = get_k_th(root, a);
			RC(root) = get_k_th(RC(root), b-a+2);
			myrev(TARGET(root));
        }
    }
	int pos = 0;
	inorder(root, pos);
	for(i = 0;i < n;i++) printf("%s%d", i ? " ":"", ans[i]); puts("");
}

int main(void)
{
    while( scanf("%d%d", &n, &m) && (n > 0) && (m > 0) )
        handle();
    return 0;
}
