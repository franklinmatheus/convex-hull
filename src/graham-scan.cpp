#include "convexhull.h"

namespace ConvexHull {

    // global access to P0
    ConvexHull::Point p0;

    int distance(ConvexHull::Point &_p1, ConvexHull::Point &_p2) {
        return (_p1._x - _p2._x)*(_p1._x - _p2._x) + (_p1._y - _p2._y)*(_p1._y - _p2._y);
    }

    int crossProduct(ConvexHull::Point &_p1, ConvexHull::Point &_p2, ConvexHull::Point &_p3) {
        return (_p2._x - _p1._x)*(_p3._y - _p1._y) - (_p2._y - _p1._y)*(_p3._x - _p1._x);
    }

    ConvexHull::Orientation orientation(ConvexHull::Point _p1, ConvexHull::Point _p2, ConvexHull::Point _p3) {
        int P = crossProduct(_p1, _p2, _p3);

        if (P == 0) return ConvexHull::COLLINEAR;
        else if (P < 0) return ConvexHull::COUNTER_CLOCKWISE;
        else return ConvexHull::CLOCKWISE;
    }

    /**
     * Compare function to be used in sort.
     * The comparison is based on the polar angle between vector(p0,p1) and vector(p0,p2).
    */
    bool compare(ConvexHull::Point _p1, ConvexHull::Point _p2) {
        ConvexHull::Orientation z_orientation = orientation(p0, _p1, _p2);

        if (z_orientation == ConvexHull::COLLINEAR) {
            if (distance(p0, _p1) >= distance(p0, _p2)) return false;
            else return true;
        }
        else if (z_orientation == ConvexHull::CLOCKWISE) return false;
        else return true;
    }

    int bottomMostIndex(std::vector<ConvexHull::Point> &_points, int &_n) {
        int indexBottomMost = 0;
        
        for (int i = 1; i < _n; ++i)
            if ((_points[i]._y < _points[indexBottomMost]._y) || 
                (_points[i]._y == _points[indexBottomMost]._y && _points[i]._x < _points[indexBottomMost]._x)) {
                    indexBottomMost = i;
                }
        
        return indexBottomMost;
    }

    /**
     * Removes the collinear points with p0 and keeps the farthest
     * return (m): new vector size after the removal of the points
     */
    int removeClosestCollinearPoints(std::vector<ConvexHull::Point> &_points, int &_n) {
        int m = 1; // p0 already exists
        
        for (int i = m; i < _n; ++i) {
            while(i < _n-1 && orientation(p0, _points[i], _points[i+1]) == ConvexHull::COLLINEAR) {
                i++;
            }
            _points[m] = _points[i];
            m++;
        }
        return m;
    }

    ConvexHull::Point nextToTop(std::stack<ConvexHull::Point> &_S) {
        ConvexHull::Point temp = _S.top();
        _S.pop();
        ConvexHull::Point top = _S.top();
        _S.push(temp);
        return top;
    }

    std::stack<ConvexHull::Point> grahamScan(std::vector<ConvexHull::Point> &_points, int &_n) {
        // 1: O(n)
        int indexP0 = bottomMostIndex(_points, _n);
        Point aux = _points[0];
        _points[0] = _points[indexP0];
        _points[indexP0] = aux;
        p0 = _points[0];
        
        // 2: O(nlogn)
        sort(next(_points.begin()), _points.end(), compare);
        int m = removeClosestCollinearPoints(_points, _n);
        
        std::stack<Point> S; // 3
        if (m < 3) return S;

        S.push(p0); // 4        
        S.push(_points[1]); // 5
        if (m >= 2) S.push(_points[2]); // 6

        for (int i = 3; i < m; ++i) { // 7
            while (S.size() > 1 && orientation(nextToTop(S), S.top(), _points[i]) != ConvexHull::COUNTER_CLOCKWISE) // 8
                S.pop(); // 9
            S.push(_points[i]); // 10
        }

        return S; // 11
    }
}