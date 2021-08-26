#include "convexhull.h"

namespace ConvexHull {
    ConvexHull::Point middle;

    int quad(ConvexHull::Point _p) {
        if (_p._x >= 0 && _p._y >= 0) return 1;
        if (_p._x <= 0 && _p._y >= 0) return 2;
        if (_p._x <= 0 && _p._y <= 0) return 3;
        return 4;
    }

    bool compareBrute(ConvexHull::Point _p1, ConvexHull::Point _p2) {
        ConvexHull::Point p1 = {_p1._x - middle._x, _p1._y - middle._y};
        ConvexHull::Point p2 = {_p2._x - middle._x, _p2._y - middle._y};
        return quad(p1) != quad(p2) ? (quad(p1) < quad(p2)) : (p1._y*p2._x < p2._y*p1._x);
    }

    /**
     * Brute force algorithm adapted from geeksforgeeks.
     */
    std::vector<ConvexHull::Point> bruteForce(std::vector<ConvexHull::Point> &points, int &n) {
        std::vector<ConvexHull::Point> S;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = points[i]._x, x2 = points[j]._x;
                int y1 = points[i]._y, y2 = points[j]._y;
    
                int a1 = y1 - y2;
                int b1 = x2 - x1;
                int c1 = (x1 * y2) - (y1 * x2);
                int pos = 0, neg = 0;
                for (int k = 0; k < n; ++k) {
                    if (((a1 * points[k]._x) + (b1 * points[k]._y) + c1) <= 0) neg++;
                    if (((a1 * points[k]._x) + (b1 * points[k]._y) + c1) >= 0) pos++;
                }
                if ((unsigned)pos == points.size() || (unsigned)neg == points.size()) {
                    if (std::find(S.begin(), S.end(), points[i]) == S.end()) S.push_back(points[i]);
                    if (std::find(S.begin(), S.end(), points[j]) == S.end()) S.push_back(points[j]);
                }
            }
        }
        
        std::vector<ConvexHull::Point> hullpoints;
        
        for (auto e : S)
            hullpoints.push_back(e);
    
        middle = ConvexHull::Point{0, 0};
        int m = hullpoints.size();
        for (int i = 0; i < m; ++i) {
            middle._x += hullpoints[i]._x;
            middle._y += hullpoints[i]._y;
            hullpoints[i]._x *= m;
            hullpoints[i]._y *= m;
        }
        
        sort(hullpoints.begin(), hullpoints.end(), compareBrute);
        
        for (int i = 0; i < m; ++i)
            hullpoints[i] = {hullpoints[i]._x/m, hullpoints[i]._y/m};
    
        return hullpoints;
    }
}
