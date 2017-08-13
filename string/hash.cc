/* Common hash for any substrings. */

typedef unsigned long long int llu;
#define MAXN 1000000
int n;
char s[MAXN];
llu H[MAXN], xP[MAXN], P = 99991ll;
void init(void)
{
    int i = 0;
    xP[0] = 1ll;
    for(i = 1;i < MAXN;++i) xP[i] = xP[i-1] * P;
    H[n] = 0;
    for(i = n-1;i >= 0;--i) H[i] = H[i+1]*P + s[i];
}
#define HASH(i,l)   (H[i] - H[i+l]*xP[l])
