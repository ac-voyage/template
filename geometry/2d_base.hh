/* 2D Geometry Base, by Abreto <m@abreto.net>. */

#include <vector>
#include <cmath>

using namespace std;

#define EPS (1e-8)
bool fe(double a, double b){return ((a-b>=-EPS)&&(a-b<=EPS));}
bool fl(double a, double b){return (a-b<-EPS);}
bool fle(double a, double b){return (a-b<=EPS);}

typedef double T;
struct point
{
    T x, y;
    point():x(0),y(0){}
    point(T xx, T yy):x(xx),y(yy){}
    T mag2(void){return (x*x+y*y);}
    T det(point b){return (x*b.y-y*b.x);}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    friend bool operator==(point a, point b){return fe(a.x,b.x)&&fe(a.y,b.y);}
};

typedef vector< point > vp;
