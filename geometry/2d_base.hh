/* 2D Geometry Base, by Abreto <m@abreto.net>. */

#include <vector>

using namespace std;

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

typedef vector<point_t> vp;
