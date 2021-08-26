#ifndef _POINT_H_
#define _POINT_H_

namespace ConvexHull {
    struct Point {
        int _x;
        int _y;
        bool operator==(const Point &rhs) 
            const { 
                return this->_x == rhs._x && this->_y == rhs._y ;
            }
    };

    typedef enum {
        COLLINEAR,
        COUNTER_CLOCKWISE,
        CLOCKWISE
    } Orientation;
}

#endif