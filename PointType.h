//
// Created by Bahman on 7/2/2018.
//

#ifndef SOMETHING_POINTTYPE_H
#define SOMETHING_POINTTYPE_H

struct PointType {
    double x;
    double y;
    double z;
    PointType operator/(double f);
};



#endif //SOMETHING_POINTTYPE_H
