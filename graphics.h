//
// Created by Bahman on 7/18/2018.
//

#ifndef SOMETHING_GRAPHICS_H
#define SOMETHING_GRAPHICS_H

#include <opencv2/core/mat.hpp>
#include "PointType.h"

using namespace std;
using namespace cv;

void display();
void reshape(GLsizei width, GLsizei height);
void initGL();
void draw_box(PointType origin);
void draw_pyra();

#endif //SOMETHING_GRAPHICS_H
