#include <bits/stdc++.h>

using namespace std;

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
