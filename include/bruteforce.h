#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

namespace ConvexHull {
    int quad(ConvexHull::Point _p);
    bool compareBrute(ConvexHull::Point _p1, ConvexHull::Point _q1);
    std::vector<ConvexHull::Point> bruteForce(std::vector<ConvexHull::Point> &points, int &n);
}

#endif