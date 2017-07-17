/* Quick Pow, by Abreto<m@abreto.net>. */

int qpow(int a, int b, int mod)
{
    int ret = 1, base = a;
    while(b){if(b&1)ret=(ret*base)%mod;base=(base*base)%mod;b>>=1;}
    return ret;
}
