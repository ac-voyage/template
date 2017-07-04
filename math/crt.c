/* Chinese Remainder Theorem, by Abreto<m@abreto.net>. */
#include "euler.c"

#define MAXN    64

typedef long long int ll;

ll quickpow(ll a, ll b, ll mod)
{
    ll ret = 1, base = a;
    while(b > 0)
    {
        if(b & 1) ret = (ret * base) % mod;
        base = (base * base) % mod;
        b >>= 1;
    }
    return ret;
}

ll N;
ll a[MAXN], m[MAXN]; /* a and m is indexed from 0. */
ll x, M;

void naive_crt(void)
{
    int i = 0;
    ll Mi[MAXN], nMi[MAXN];
    ll t[MAXN];

    M = 1;
    for(i = 0;i < N;++i)
        M *= a[i];
    for(i = 0;i < N;++i)
        Mi[i] = M / a[i];
    get_euler();
    for(i = 0;i < N;++i)
        nMi[i] = quickpow(Mi[i], phi[a[i]]-1, a[i]);
    for(i = 0;i < N;++i)
        t[i] = ((a[i] * Mi[i]) % M) * nMi[i] % M;
    for(i = 0;i < N;++i)
        x = (x + t[i]) % M;
}
