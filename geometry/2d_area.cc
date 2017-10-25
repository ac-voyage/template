#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

//#define inf 1000000000000
#define M 8
#define LL long long
#define eps 1e-12
#define PI acos(-1.0)
using namespace std;
struct node
{
    double x,y;
    node(){}
    node(double xx,double yy)
    {
        x=xx;
        y=yy;
    }
    node operator -(node s)
    {
        return node(x-s.x,y-s.y);
    }
    node operator +(node s)
    {
        return node(x+s.x,y+s.y);
    }
    double operator *(node s)
    {
        return x*s.x+y*s.y;
    }
    double operator ^(node s)
    {
        return x*s.y-y*s.x;
    }
};
double max(double a,double b)
{
    return a>b?a:b;
}
double min(double a,double b)
{
    return a<b?a:b;
}
double len(node a)
{
    return sqrt(a*a);
}
double dis(node a,node b)//两点之间的距离
{
    return len(b-a);
}
double cross(node a,node b,node c)//叉乘
{
    return (b-a)^(c-a);
}
double dot(node a,node b,node c)//点成
{
    return (b-a)*(c-a);
}
int judge(node a,node b,node c)//判断c是否在ab线段上（前提是c在直线ab上）
{
    if(c.x>=min(a.x,b.x)
       &&c.x<=max(a.x,b.x)
       &&c.y>=min(a.y,b.y)
       &&c.y<=max(a.y,b.y))
        return 1;
    return 0;
}
double area(node b,node c,double r)
{
    node a(0.0,0.0);
    if(dis(b,c)<eps)
        return 0.0;
    double h=fabs(cross(a,b,c))/dis(b,c);
    if(dis(a,b)>r-eps&&dis(a,c)>r-eps)//两个端点都在圆的外面则分为两种情况
    {
        double angle=acos(dot(a,b,c)/dis(a,b)/dis(a,c));
        if(h>r-eps)
        {
            return 0.5*r*r*angle;
        }
        else if(dot(b,a,c)>0&&dot(c,a,b)>0)
        {
            double angle1=2*acos(h/r);
            return 0.5*r*r*fabs(angle-angle1)+0.5*r*r*sin(angle1);
        }
        else
        {
            return 0.5*r*r*angle;
        }
    }
    else if(dis(a,b)<r+eps&&dis(a,c)<r+eps)//两个端点都在圆内的情况
    {
        return 0.5*fabs(cross(a,b,c));
    }
    else//一个端点在圆上一个端点在圆内的情况
    {
        if(dis(a,b)>dis(a,c))//默认b在圆内
        {
            swap(b,c);
        }
        if(fabs(dis(a,b))<eps)//ab距离为0直接返回0
        {
            return 0.0;
        }
        if(dot(b,a,c)<eps)
        {
            double angle1=acos(h/dis(a,b));
            double angle2=acos(h/r)-angle1;
            double angle3=acos(h/dis(a,c))-acos(h/r);
            return 0.5*dis(a,b)*r*sin(angle2)+0.5*r*r*angle3;
 
        }
        else
        {
            double angle1=acos(h/dis(a,b));
            double angle2=acos(h/r);
            double angle3=acos(h/dis(a,c))-angle2;
            return 0.5*r*dis(a,b)*sin(angle1+angle2)+0.5*r*r*angle3;
        }
    }
}

node A, B, C;
int R;

bool compar(node &p1, node &p2)
{
    return (p1^p2)>eps;
}

double f(double x, double y)
{
    node O(x,y);
    node p[8];
    p[0] = A-O; p[1] = B-O; p[2] = C-O;
    sort(p, p+3, compar);
    p[3] = p[0];
    O=node(0,0);
    double sum=0;
    /* <!-- 求面积交部分 */
    for(int i=0;i<3;i++)    /* 按顺或逆时针顺序最后取绝对值就好 */
    {
        int j=i+1;
        double s=area(p[i],p[j],(double)R);
        if(cross(O,p[i],p[j])>0)
            sum+=s;
        else
            sum-=s;
    }
    if(sum < -eps) sum = -sum;
    /* --> */
    return sum;
}

double trifind(double x, double y1, double y2)
{
    double l = y1, r = y2;
    while(r-l>eps)
    {
        double mid = (l+r)/2.0;
        double mmid = (mid+r)/2.0;
        if( f(x,mmid) > f(x,mid)+eps )
            l = mid;
        else
            r = mmid;
    }
    return f(x,l);
}

double findmin(double x1, double x2, double y1, double y2)
{
    double l = x1, r = x2;
    while(r-l>eps)
    {
        double mid = (l+r)/2.0;
        double mmid = (mid+r)/2.0;
        if( trifind(mmid,y1,y2) > trifind(mid,y1,y2)+eps )
            l = mid;
        else
            r = mmid;
    }
    return trifind(l,y1,y2);
}

double ans(int a, int b, int c, int r)
{
    A = node(0,0);
    B = node((double)c,0);
    R = r;
    double da = a, db = b, dc = c;
    double cosa = (db*db+dc*dc-da*da)/(2.0*db*dc);
    double alpha = acos(cosa);
    C = node(db*cosa, db*sin(alpha));
    return findmin(0.0, c, 0.0, db*sin(alpha));
}

int main(void)
{
    int a = 0, b = 0, c = 0, r = 0;
    while(EOF != scanf("%d%d%d%d",&a,&b,&c,&r) && (a||b||c||r))
        printf("%.8lf\n", ans(a,b,c,r));
    return 0;
}
