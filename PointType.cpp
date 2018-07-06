//
// Created by Bahman on 7/2/2018.
//


struct PointType {
    double x;
    double y;
    double z;
    //    operator Vctr() const {
    //        Vctr p;
    //        p.x = this->x;
    //        p.y = this->y;
    //        p.z = this->z;
    //    }
    PointType operator/(double f){
        x = x / f;
        y = y / f;
        z = z / f;
        return *this;
    }

};
