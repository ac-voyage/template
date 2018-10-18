//china no.1
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <cstring>
#include <queue>
#include <list>
#include <stdio.h>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <bitset>
using namespace std;
 
#define pi acos(-1)
#define PI acos(-1)
#define endl '\n'
#define srand() srand(time(0));
#define me(x,y) memset(x,y,sizeof(x));
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();it++)
#define close() ios::sync_with_stdio(0); cin.tie(0);
#define FOR(x,n,i) for(int i=x;i<=n;i++)
#define FOr(x,n,i) for(int i=x;i<n;i++)
#define W while
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define bug printf("***********\n");
#define db double
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL LINF=0x3f3f3f3f3f3f3f3fLL;
const int dx[]={-1,0,1,0,1,-1,-1,1};
const int dy[]={0,1,0,-1,-1,1,-1,1};
const int maxn=1e3+10;
const int maxx=1e6+100;
const double EPS=1e-8;
const double eps=1e-8;
const int mod=10000007;
template<class T>inline T min(T a,T b,T c) { return min(min(a,b),c);}
template<class T>inline T max(T a,T b,T c) { return max(max(a,b),c);}
template<class T>inline T min(T a,T b,T c,T d) { return min(min(a,b),min(c,d));}
template<class T>inline T max(T a,T b,T c,T d) { return max(max(a,b),max(c,d));}
template <class T>
inline bool scan_d(T &ret){char c;int sgn;if (c = getchar(), c == EOF){return 0;}
while (c != '-' && (c < '0' || c > '9')){c = getchar();}sgn = (c == '-') ? -1 : 1;ret = (c == '-') ? 0 : (c - '0');
while (c = getchar(), c >= '0' && c <= '9'){ret = ret * 10 + (c - '0');}ret *= sgn;return 1;}
 
inline bool scan_lf(double &num){char in;double Dec=0.1;bool IsN=false,IsD=false;in=getchar();if(in==EOF) return false;
while(in!='-'&&in!='.'&&(in<'0'||in>'9'))in=getchar();if(in=='-'){IsN=true;num=0;}else if(in=='.'){IsD=true;num=0;}
else num=in-'0';if(!IsD){while(in=getchar(),in>='0'&&in<='9'){num*=10;num+=in-'0';}}
if(in!='.'){if(IsN) num=-num;return true;}else{while(in=getchar(),in>='0'&&in<='9'){num+=Dec*(in-'0');Dec*=0.1;}}
if(IsN) num=-num;return true;}
 
void Out(LL a){if(a < 0) { putchar('-'); a = -a; }if(a >= 10) Out(a / 10);putchar(a % 10 + '0');}
void print(LL a){ Out(a),puts("");}
//freopen( "in.txt" , "r" , stdin );
//freopen( "data.txt" , "w" , stdout );
//cerr << "run time is " << clock() << endl;
/*struct Point
{
    double x, y;
    Point(const Point& rhs): x(rhs.x), y(rhs.y) { } //拷贝构造函数
    Point(double x = 0, double y = 0) : x(x), y(y) { }
    inline void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    inline void print()
    {
        printf("%.6lf %.6lf\n",x,y);
    }
};*/
db sqr(db x)
{
   return x*x;
}
int dcmp(double x)
{
    if(fabs(x) < EPS) return 0;
    else return x < 0 ? -1 : 1;
}
struct Circle
{
    double x, y, r, angle;
    int d;
    Circle(){}
    Circle(double xx, double yy, double ang = 0, int t = 0)
    {
        x = xx;  y = yy;  angle = ang;  d = t;
    }
    void get()
    {
        scanf("%lf%lf%lf", &x, &y, &r);
        d = 1;
    }
};
Circle cir[maxn],tp[maxn*2];
double area[maxn];
double dis(Circle a,Circle b)
{
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double cross(Circle p0,Circle p1,Circle p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}
//圆相交
int CirCrossCir(Circle p1, double r1,Circle p2, double r2,Circle &cp1,Circle &cp2)
{
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (d + eps < 0) return 0; if (d < eps) d = 0; else d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d; sq *= 2;
    cp1.x = (x - dy) / sq; cp1.y = (y + dx) / sq;
    cp2.x = (x + dy) / sq; cp2.y = (y - dx) / sq;
    if (d > eps) return 2; else return 1;
}
bool circmp(const Circle& u, const Circle& v)
{
    return dcmp(u.r - v.r) < 0;
}
bool cmp(const Circle& u, const Circle& v)
{
    if (dcmp(u.angle - v.angle)) return u.angle < v.angle;
    return u.d > v.d;
}
//0.5*r*r*(K-sin(K))
double calc(Circle cir,Circle cp1,Circle cp2)
{
    double ans = (cp2.angle - cp1.angle) * sqr(cir.r)
        - cross(cir, cp1, cp2) + cross(Circle(0, 0), cp1, cp2);
    return ans / 2;
}
 
void CirUnion(Circle cir[], int n)
{
    Circle cp1, cp2;
    sort(cir, cir + n, circmp);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dcmp(dis(cir[i], cir[j]) + cir[i].r - cir[j].r) <= 0)
                cir[i].d++;
    for (int i = 0; i < n; ++i)
    {
        int tn = 0, cnt = 0;
        for (int j = 0; j < n; ++j)
        {
            if (i == j) continue;
            if (CirCrossCir(cir[i], cir[i].r, cir[j], cir[j].r,
                cp2, cp1) < 2) continue;
            cp1.angle = atan2(cp1.y - cir[i].y, cp1.x - cir[i].x);
            cp2.angle = atan2(cp2.y - cir[i].y, cp2.x - cir[i].x);
            cp1.d = 1;    tp[tn++] = cp1;
            cp2.d = -1;   tp[tn++] = cp2;
            if (dcmp(cp1.angle - cp2.angle) > 0) cnt++;
        }
        tp[tn++] = Circle(cir[i].x - cir[i].r, cir[i].y, pi, -cnt);
        tp[tn++] = Circle(cir[i].x - cir[i].r, cir[i].y, -pi, cnt);
        sort(tp, tp + tn, cmp);
        int p, s = cir[i].d + tp[0].d;
        for (int j = 1; j < tn; ++j)
        {
            p = s;  s += tp[j].d;
            area[p] += calc(cir[i], tp[j - 1], tp[j]);
        }
    }
}
int n;
void solve()
{
    for(int i=0;i<n;i++)
        cir[i].get();
    me(area,0);
    CirUnion(cir,n);
    for(int i=1;i<=n;i++)
    {
        area[i]-=area[i+1];
        printf("[%d] = %.3f\n", i, area[i]);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
        solve();
}
