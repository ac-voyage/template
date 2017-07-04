/* 2D Geometry Base, by Abreto <m@abreto.net>. */

#include <vector>
#include <cmath>

using namespace std;

#define EPS (1e-8)

bool fless(double a, double b)
{
    return ((a-b) < -EPS);
}

struct point_t
{
    int x, y;

    point_t(void):x(0),y(0){}
    point_t(int xx, int yy):x(xx),y(yy){}

    friend point_t operator-(point_t a, point_t b)
    {
        return point_t(a.x-b.x, a.y-b.y);
    }
};
typedef point_t vector_t;

/* a x b */
int det(vector_t a, vector_t b)
{
    return a.x * b.y - a.y * b.x;
}

double mag(vector_t a)
{
    return sqrt((double)a.x*a.x+a.y*(double)a.y);
}

typedef vector<point_t> vp;
