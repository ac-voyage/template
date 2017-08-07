/* Fenwick Tree (Binary Indexed Tree), by Abreto <m@abreto.net>. */
#include <cstring>

using namespace std;

template <class T = int, int MAXN = 100001>
struct fenwick
{
    static inline int lowbit(int x) {return (x&(-x));}
    int N;
    T f[MAXN]; /* 1=based. */
    fenwick(void):N(MAXN){init();}
    fenwick(int n):N(n){init();}
    void init(void) {memset(f,0,sizeof(f));}
    void upd(int i, T dx)
    {
        while(i <= N)
        {
            f[i] += dx;
            i += lowbit(i);
        }
    }
    T sum(int i)
    {
        T ret = 0;
        while(i)
        {
            ret += f[i];
            i -= lowbit(i);
        }
        return ret;
    }
};
