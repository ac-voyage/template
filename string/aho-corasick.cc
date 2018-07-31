/* Aho-Corasick automaton algorithm, by Abreto<m@abreto.net>. */

#define MAXN	500500
#define NALPHA	26
#define FIRSTA	'a'

/* pointer version => { */
struct vtx
{
	vtx *nxt[NALPHA];
	vtx *fail;
	int end;
}vtxs[MAXN];
int nvtxs;
void myclr(void)
{
	nvtxs = 0;
}
vtx *new_vtx(void)
{
	vtx *ret = vtxs+(nvtxs++);
	for(int i = 0;i < NALPHA;i++)
		ret->nxt[i] = NULL;
	ret->fail = NULL;
	ret->end = 0;
	return ret;
}
void myins(vtx *root, char const *s)
{
	for( ; *s ; s++ )
	{
		int of = (*s) - FIRSTA;
		if ( NULL == root->nxt[of] )
		{
			root->nxt[of] = new_vtx();
		}
		root = root->nxt[of];
	}
	root->end++;
}
void build_ac(vtx *root)
{
	queue<vtx *> q;
	q.push(root);
	while(!q.empty())
	{
		vtx *p = q.front(); q.pop();
		for(int i = 0;i < NALPHA;i++)
		{
			if( NULL == p->nxt[i] ) continue;
			if( root == p ) p->nxt[i]->fail = root;
			else
			{
				vtx *t = p->fail;
				while ( t && NULL == t->nxt[i] )
				{
					t = t->fail;
				}
				if (t) p->nxt[i]->fail = t->nxt[i];
				else p->nxt[i]->fail = root;
			}
			/* version[1] { */
			p->nxt[i]->end += p->nxt[i]->fail->end;	/* update this sum, add its existing prefix to this. */
			/* } */
			q.push(p->nxt[i]);
		}
	}
}
int qry(vtx *root, char const *s)
{
	vtx *p = root;
	int cnt = 0;
	for( ; *s ; s++ )
	{
		int of = (*s) - FIRSTA;
		while( p != root && NULL == p->nxt[of] )
		{
			p = p->fail;
		}
		if (p->nxt[of]) p = p->nxt[of];
		cnt += p->end;	// correct when version[1] exists.
		// if `version[1]` not exists, you need to add all ends from this vertex up.
		//for( vtx *t = p ; t ; t = t->fail )
		//	cnt += t->end;
	}
	return cnt;
}
/* } */

/* -- usage (of pointer version) -- */
#include <bits/stdc++.h>
using namespace std;

char S[1000100];
char pat[64];

int main(void)
{
	int T, N;
	vtx *root = NULL;
	scanf("%d", &T);
	while(T--)
	{
		myclr();
		root = new_vtx();
		scanf("%s", S);
		scanf("%d", &N);
		while(N--)
		{
			scanf("%s", pat);
			myins(root, pat);
		}
		build_ac(root);
		printf("%d\n", qry(root, S));
	}
	return 0;
}
