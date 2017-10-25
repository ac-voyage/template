/* type 1: */
/* bzoj 1010 */
#include <bits/stdc++.h>

using namespace std;
typedef long double ll;
#define MAXN    50050
#define eps     (1e-8)

int N;
ll L;
ll S[MAXN];
ll f[MAXN];
ll dp[MAXN];

inline ll k(int j)
{
   return (-2.0) * (f[j] + L);
}
inline ll b(int j)
{
   return dp[j] + f[j]*f[j] + 2ll*f[j]*L;
}
inline ll g(int j, int i)
{
   return k(j) * f[i] + b(j);
}

/* check if l1 & l3 <= l2 */
inline int check(int l1, int l2, int l3)
{
   /*ll left = b(l3)*k(l1)+b(l1)*k(l2)+b(l2)*k(l3);
   ll right = b(l1)*k(l3)+b(l3)*k(l2)+b(l2)*k(l1);*/
   ll left = b(l3)*k(l1)-b(l1)*k(l3);
   ll right = k(l2)*(b(l3)-b(l1))+b(l2)*(k(l1)-k(l3));
   return (left <= right);
}

int Q[MAXN], ql, qr;

int main(void)
{
   int i;
   scanf("%d%Lf", &N, &L); L += 1.0;
   for(i = 1;i <= N;++i)
   {
       scanf("%Lf", S+i);
       S[i] += S[i-1];
       f[i] = S[i] + (double)i;
   }
   Q[qr++] = 0;
   for(i = 1;i <= N;++i)
   {
       /* <!-- STARED */
       for(;ql+1 < qr && g(Q[ql],i) >= g(Q[ql+1],i);ql++);
       dp[i] = g(Q[ql], i) + f[i]*f[i] + L*L; //printf("%d: %lld,%lld\n", i, dp[i], dp[i]-f[i]*f[i]);
       for(;ql+1 < qr && check(Q[qr-2], Q[qr-1], i);qr--);
       Q[qr++] = i;
       /* --> */
   }
   printf("%lld\n", (long long int)round(dp[N]));
   return 0;
}
