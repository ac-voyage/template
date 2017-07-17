/* 2D Convex Hull, by Abreto <m@abreto.net>. */
#include "2d_base.hh"
#include <cmath>
#include <algorithm>

using namespace std;

point O;

bool comp_angle(point_t a, point_t b)
{
    double t = (a-O).X(b-O);
    if(fe(t,0.0)) return fl((b-O).mag2(),(a-O).mag2());
    else return fl(0.0,t);
}

void convex_hull_graham(vp& convex, vp src)
{
    int i = 0, top = 0;
    O = src[0];
    for(auto pt : src)
        if( pt.x < O.x || (pt.x == O.x && pt.y < O.y))
            O = pt;
    sort(src.begin(), src.end(), comp_angle);
    convex.push_back(src[0]); convex.push_back(src[1]);
    top = 1;
    for(i = 2;i < src.size();++i)
    {
        while(top>1 && fle((convex[top]-convex[top-1]).X(src[i]-convex[top]),0.0))
        {
            convex.pop_back(); --top;
        }
        convex.push_back(src[i]); ++top;
    }
}
