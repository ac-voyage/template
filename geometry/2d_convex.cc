/* 2D Convex Hull, by Abreto <m@abreto.net>. */
#include "2d_base.hh"
#include <cmath>
#include <algorithm>

using namespace std;

point_t O;

bool comp_angle(point_t a, point_t b)
{
    int t = det(a-O, b-O);
    if(0 == t) return fless(mag(a-O),mag(b-O));
    else return (t>0);
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
        while(1)
        {
            if(top < 1)
            {
                convex.push_back(src[i]); top++;
                break;
            } else {
                if(det(convex[top]-convex[top-1], src[i]-convex[top]) > 0)
                {
                    convex.push_back(src[i]); top++;
                    break;
                } else {
                    convex.pop_back(); top--;
                }
            }
        }
}
