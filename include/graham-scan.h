#ifndef _GRAHAM_SCAN_H_
#define _GRAHAM_SCAN_H_

namespace ConvexHull {
    int distance(Point &_p1, Point &_p2);
    int crossProduct(ConvexHull::Point &_p1, ConvexHull::Point &_p2, ConvexHull::Point &_p3);
    ConvexHull::Orientation orientation(ConvexHull::Point _p1, ConvexHull::Point _p2, ConvexHull::Point _p3);
    bool compare(Point _p1, Point _p2);
    int bottomMostIndex(std::vector<ConvexHull::Point> &_points, int &_n);
    int removeClosestCollinearPoints(std::vector<ConvexHull::Point> &_points, int &_n);
    ConvexHull::Point nextToTop(std::stack<ConvexHull::Point> &_S);
    std::stack<ConvexHull::Point> grahamScan(std::vector<ConvexHull::Point> &_points, int &_n);
}

#endif