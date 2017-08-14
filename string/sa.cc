/* Suffix Array, copied. */

#define MAXN    (200010)
namespace mzry_sa
{
    int wx[MAXN],wy[MAXN],*x,*y,wss[MAXN],wv[MAXN];

    bool dacmp(int *r,int n,int a,int b,int l) {
        return a+l<n && b+l<n && r[a]==r[b]&&r[a+l]==r[b+l];
    }
    void da(int str[],int sa[],int rank[],int height[],int n,int m) {
        int *s = str;
        int *x=wx,*y=wy,*t,p;
        int i,j;
        for(i=0; i<m; i++)wss[i]=0;
        for(i=0; i<n; i++)wss[x[i]=s[i]]++;
        for(i=1; i<m; i++)wss[i]+=wss[i-1];
        for(i=n-1; i>=0; i--)sa[--wss[x[i]]]=i;
        for(j=1,p=1; p<n && j<n; j*=2,m=p) {
            for(i=n-j,p=0; i<n; i++)y[p++]=i;
            for(i=0; i<n; i++)if(sa[i]-j>=0)y[p++]=sa[i]-j;
            for(i=0; i<n; i++)wv[i]=x[y[i]];
            for(i=0; i<m; i++)wss[i]=0;
            for(i=0; i<n; i++)wss[wv[i]]++;
            for(i=1; i<m; i++)wss[i]+=wss[i-1];
            for(i=n-1; i>=0; i--)sa[--wss[wv[i]]]=y[i];
            for(t=x,x=y,y=t,p=1,i=1,x[sa[0]]=0; i<n; i++)
            x[sa[i]]=dacmp(y,n,sa[i-1],sa[i],j)?p-1:p++;
        }
        for(int i=0; i<n; i++) rank[sa[i]]=i;
        for(int i=0,j=0,k=0; i<n; height[rank[i++]]=k)
            if(rank[i]>0)
            for(k?k--:0,j=sa[rank[i]-1];
                i+k < n && j+k < n && str[i+k]==str[j+k];
                k++);
    }
}

/*
Suffix array O(n lg^2 n)
LCP table O(n)
*/
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

namespace SuffixArray
{
	const int MAXN = 1 << 21;
	char * S;
	int N, gap;
	int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

	bool sufCmp(int i, int j)
	{
		if (pos[i] != pos[j])
			return pos[i] < pos[j];
		i += gap;
		j += gap;
		return (i < N && j < N) ? pos[i] < pos[j] : i > j;
	}

	void buildSA()
	{
		N = strlen(S);
		REP(i, N) sa[i] = i, pos[i] = S[i];
		for (gap = 1;; gap <<= 1)
		{
			sort(sa, sa + N, sufCmp);
			REP(i, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
			REP(i, N) pos[sa[i]] = tmp[i];
			if (tmp[N - 1] == N - 1) break;
		}
	}

	void buildLCP()
	{
		for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1)
		{
			for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
			++k;
			lcp[pos[i]] = k;
			if (k)--k;
		}
	}
} // end namespace SuffixArray

namespace HashSuffixArray
{
	const int
		MAXN = 1 << 21;

	typedef unsigned long long hash;

	const hash BASE = 137;

	int N;
	char * S;
	int sa[MAXN];
	hash h[MAXN], hPow[MAXN];

	#define getHash(lo, size) (h[lo] - h[(lo) + (size)] * hPow[size])

	inline bool sufCmp(int i, int j)
	{
		int lo = 1, hi = min(N - i, N - j);
		while (lo <= hi)
		{
			int mid = (lo + hi) >> 1;
			if (getHash(i, mid) == getHash(j, mid))
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		return S[i + hi] < S[j + hi];
	}

	void buildSA()
	{
		N = strlen(S);
		hPow[0] = 1;
		for (int i = 1; i <= N; ++i)
			hPow[i] = hPow[i - 1] * BASE;
		h[N] = 0;
		for (int i = N - 1; i >= 0; --i)
			h[i] = h[i + 1] * BASE + S[i], sa[i] = i;

		stable_sort(sa, sa + N, sufCmp);
	}

} // end namespace HashSuffixArray

namespace lrj_sa
{
	const int MAXN = 1000;
	char s[MAXN];	/* 原始字符数组（最后一个字符应必须是0，而前面的字符必须非0） */
	int sa[MAXN], t[MAXN], t2[MAXN], c[MAXN], n;	/* n seems to be the length of s. */
	/* every charactor is in [0,m-1] */
	void build_sa(int m)
	{
		int i, *x = t, *y = t2;
		for(i = 0;i < m;++i) c[i] = 0;
		for(i = 0;i < n;i++) c[x[i]=s[i]]++;
		for(i = 1;i < m;++i) c[i] += c[i-1];
		for(i = n-1;i >= 0;--i) sa[--c[x[i]]] = i;
		for(int k = 1;k <= n;k <<= 1)
		{
			int p = 0;
			for(i = n-k;i < n;++i) y[p++] = i;
			for(i = 0;i < n;++i) if(sa[i] >= k) y[p++] = sa[i]-k;
			for(i = 0;i < m;i++) c[i] = 0;
			for(i = 0;i < n;i++) c[x[y[i]]]++;
			for(i = 0;i < m;++i) c[i]+=c[i-1];
			for(i = n-1;i >= 0;--i) sa[--c[x[y[i]]]] = y[i];
			swap(x,y);
			p = 1; x[sa[0]] = 0;
			for(i = 1;i < n;++i)
				x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1:p++;
			if(p >= n) break;
			m = p;
		}
	}
	int rank[MAXN], height[MAXN];
	void get_height(void)
	{
		int i,j,k = 0;
		for(i = 0;i < n;++i) rank[sa[i]] = i;
		for(i = 0;i < n;++i)
		{
			if(k) k--;
			j = sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]] = k;
		}
	}
} // end namespace lrj_sa
