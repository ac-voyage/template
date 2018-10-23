#include<bits/stdc++.h>
#define ll long long
const int N=262144;
const ll MOD=50000000001507329LL;//998244353 1004535809
using namespace std;
int n,m;
ll a[N],b[N],x[N],y[N];
ll wn[25];
ll Mul(ll x,ll y)//乘法超ll用快速乘，主函数也需要用
{
    ll ans=(x*y-(ll)((long double)x/MOD*y+1e-8)*MOD);
    return ans<0?ans+MOD:ans;
}
ll Qpow(ll a,ll b,ll M)
{
    ll ans=1;a%=M;
    while(b)
    {
        if(b&1) ans=Mul(ans,a);
        a=Mul(a,a);
        b>>=1;
    }
    return ans;
}
void Getwn()//主函数预处理getwn()
{
    for(int i=0;i<25;i++)
    {
        wn[i]=Qpow(3,(MOD-1)/(1<<i),MOD);
    }
}
void NTT(ll *x,int n,int rev)
{
    int i,j,k,ds;
    ll w,u,v;
    for(i=1,j=n>>1,k=n>>1;i<n-1;i++,k=n>>1)
    {
        if(i<j) swap(x[i],x[j]);
        while(j>=k) j-=k,k>>=1;
        if(j<k) j+=k;
    }
    for(i=2,ds=1;i<=n;i<<=1,ds++)
    {
        for(j=0;j<n;j+=i)
        {
            w=1;
            for(k=j;k<j+i/2;k++)
            {
                u=x[k];
                v=Mul(w,x[k+i/2]);
                x[k]=(u+v)%MOD;
                x[k+i/2]=(u-v+MOD)%MOD;
                w=Mul(w,wn[ds]);
            }
        }
    }
    if(rev==-1)
    {
        for(i=1;i<n/2;i++) swap(x[i],x[n-i]);
        w=Qpow(n,MOD-2,MOD);
        for(i=0;i<n;i++) x[i]=Mul(x[i],w);
    }
}
int main()
{
    Getwn();
    while(~scanf("%d%d",&n,&m))
    {
        for(int i=0;i<n;i++)scanf("%lld",&a[i]);
        for(int i=0;i<m;i++)scanf("%lld",&b[i]);
        int len=1,s=n+m;
        while(len<s)len<<=1;
        for(int i=n;i<len;i++)a[i]=0;
        for(int i=m;i<len;i++)b[i]=0;
        NTT(a,len,1);NTT(b,len,1);
        for(int i=0;i<len;i++)a[i]=Mul(a[i],b[i]);
        NTT(a,len,-1);
        for(int i=0;i<=s;i++)printf("%lld ",a[i]);puts("");
    }
}

// -----------------------------------------------------------------------------
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<complex>
using namespace std;
typedef long long LL;
const LL MOD=998244353,g=3,gi=332748118;
const LL N=1000005;
LL n,m;
LL a[N],b[N];
LL pow (LL x,LL y)
{
    if (y==1) return x;
    LL lalal=pow(x,y>>1);
    lalal=lalal*lalal%MOD;
    if (y&1) lalal=lalal*x%MOD;
    return lalal;
}
void ntt (LL *a,LL n,LL o)
{
    if (n==1) return ;
    LL k=(n>>1);
    LL w=1,wn=pow(o==1?g:gi,(MOD-1)/n),a0[k],a1[k];
    for (LL u=0;u<k;u++)
    {
        LL i=u*2;
        a0[u]=a[i];
        a1[u]=a[i+1];
    }
    ntt(a0,k,o);ntt(a1,k,o);
    for (LL u=0;u<k;u++)
    {
        a[u]=a0[u]+w*a1[u]%MOD;
        a[u]=(a[u]%MOD+MOD)%MOD;
        a[u+k]=a0[u]-w*a1[u];
        a[u+k]=(a[u+k]%MOD+MOD)%MOD;
        w=w*wn%MOD;
    }
}
void ntt(LL *a,LL n,LL op)
{
    for (LL u=0;u<n;u++) bin[u]=(bin[u>>1]>>1)|((u&1)*(n>>1));
    for (LL u=0;u<n;u++) if (u<bin[u]) swap(a[u],a[bin[u]]);
    for (LL u=1;u<n;u<<=1)
    {
        LL wn=pow(op==1?g:gi,(MOD-1)/(u<<1)),w,t;
        for (LL i=0;i<n;i=i+(u<<1))
        {
            w=1;
            for (LL k=0;k<u;k++)
            {
                t=w*a[u+i+k]%MOD;
                a[u+i+k]=(a[i+k]-t+MOD)%MOD;
                a[i+k]=(a[i+k]+t)%MOD;
                w=w*wn%MOD;
            }
        }
    }
    if(op==-1)
    {
        LL Inv=pow(n,MOD-2);
        for(LL i=0;i<n;i++) a[i]=a[i]*Inv%MOD;
    }
}

int main()
{
    scanf("%I64d%I64d",&n,&m);
    for (LL u=0;u<=n;u++) scanf("%I64d",&a[u]);
    for (LL u=0;u<=m;u++) scanf("%I64d",&b[u]);
    m=m+n;n=1;while (n<=m) n<<=1;
    ntt(a,n,1);ntt(b,n,1);
    for (LL u=0;u<=n;u++) a[u]*=b[u];
    ntt(a,n,-1);
    LL inv=pow(n,MOD-2);
    for (LL u=0;u<=m;u++)   printf("%I64d ",a[u]*inv%MOD);
    return 0;
}
