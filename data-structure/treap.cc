#include <bits/stdc++.h>

using namespace std;

#define MAXN	(2560000)

int __treap_mem[MAXN];
void init_treap_mem(void)
{
	for( int i = 1 ; i < MAXN ; i++ )
		__treap_mem[i-1] = i;
}
int alloc_address(void)
{
	int ret = __treap_mem[0];
	__treap_mem[0] = __treap_mem[ret];
	return ret;
}
void free_address(int p)
{
	__treap_mem[p] = __treap_mem[0];
	__treap_mem[0] = p;
}

typedef int key_t;
typedef int val_t;
struct treap
{
	key_t x;
	val_t v;
	int r;		/* random priority */
	int eq, s;	/* number of equal ones, size of subtree (include root itself) */
	treap *fa;	/* point to its father */
	treap *ch[2];	/* 0 for left child, 1 for right child. */

	treap(void);
	inline void maintain(void);	/* update `s` */
	inline void set_child(int d, treap *child);
	inline int which(void);	/* determine which child this is of its father */
	inline int cmp(key_t ox);	/* determine which child to insert ox */
	treap *rotate(void);	/* rotate this to its father, return this */
}treap_nodes[MAXN];

treap *new_treap(key_t x, val_t v, treap *f)
{
	treap *ret = treap_nodes + alloc_address();
	ret->x = x; ret->v = v;
	ret->eq = ret->s = 1;
	ret->fa = f;
	ret->ch[0] = ret->ch[1] = NULL;
}
void free_treap(treap *p)
{
	free_address( p - treap_nodes );
}
void treap_clear(void)
{
	init_treap_mem();
}

treap::treap(void)
{
	r = rand();
	eq = s = 0;
	fa = ch[0] = ch[1] = NULL;
}
inline void treap::maintain(void)
{
	s = eq;
	for( int i = 0 ; i < 2 ; i++ )
		if( ch[i] )
			s += ch[i]->s;
}
inline void treap::set_child(int d, treap *child)
{
	ch[d] = child;
	maintain();
	if( child ) child->fa = this;
}
inline int treap::which(void)
{
	if( NULL == fa ) return -1;	/* this is not a child */
	else return ( fa->ch[1] == this );
}
inline int treap::cmp(key_t ox)
{
	if( ox == x ) return -1;	/* equal */
	else return ( ox > x );		/* left less, right more */
}
treap *treap::rotate(void)
{
	if ( NULL == fa ) return this;	/* no father, already global root. */
	int d = which();
	fa->set_child(d, ch[d^1]);
	set_child(d^1, fa);
	return this;
}

// --- deprecated |
typedef int T;

struct node
{
	T v;	/* value of this node */
	int r;	/* random priority */
	int eq;	/* the number of equal things */
	int s;	/* the size of subtree rooted at this */
	node *ch[2];	/* 0 for left child, 1 for right child. */	
	node(void)
	{
		r = rand();
		ch[0] = ch[1] = NULL;
	}
	/* return where to insert x */
	int cmp(T x)
	{
		if(v == x) return -1;
		else return (x < v) ? 0 : 1;
	}
	/* return 1 if this node is prior to other */
	int pri(node *o)
	{
		return (r > (o->r));
	}
	/* maintain the `s` field */
	void maintain(void)
	{
		s = eq;
		if(NULL != ch[0]) s += ch[0]->s;
		if(NULL != ch[1]) s += ch[1]->s;
	}
};

/* move o to ch[d] of o->ch[d^1] */
void rotate(node *&o, int d)
{
	node *k = o->ch[d^1];
	o->ch[d^1] = k->ch[d];	o->maintain();
	k->ch[d] = o;	k->maintain();
	o = k;
}
