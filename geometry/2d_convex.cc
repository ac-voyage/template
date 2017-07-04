/* 2D Convex Hull, by Abreto <m@abreto.net>. */
#include "2d_base.hh"
#include <algorithm>

using namespace std;

point_t O;

void convex_hull_graham(vp& convex, vp src)
{
    O = src[0];
    for(auto pt : src)
        if( pt.x < O.x || (pt.x == O.x && pt.y < O.y))
            O = pt;
    /* sort */
}
