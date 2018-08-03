#include <iostream>
#include <math.h>
#include <limits>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <algorithm>
#include <unistd.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <zconf.h>
#include<math.h>
#include <thread>


#include "detector.h"
#include "PointType.h"
#include "graphics.h"

#include <ctime>

using namespace std;
using namespace cv;


struct Vctr {
    double x;
    double y;
    double z;
    //    operator PointType() const {
    //        PointType p;
    //        p.x = this->x;
    //        p.y = this->y;
    //        p.z = this->z;
    //    }
    Vctr operator/(double f){
        x = x / f;
        y = y / f;
        z = z / f;
        return *this;
    }

    Vctr operator*(double f){
        Vctr v;
        v.x = this->x * f;
        v.y = this->y * f;
        v.z = this->z * f;
        return v;
    }

    Vctr operator+(Vctr v){
        Vctr u;
        u.x = this->x + v.x;
        u.y = this->y + v.y;
        u.z = this->z + v.z;
        return u;
    }
};



#define focal_len 984.375
//#define focal_len 412.
#define MARKERS_NUM 3
#define STEP 0.1
#define LARGE_NUM 9e300



//double f = 984.375;
PointType XYZ[MARKERS_NUM];
PointType ABC_points[MARKERS_NUM];
PointType Origin;

double a[MARKERS_NUM];

double a_history[MARKERS_NUM];
double a_place_holder[MARKERS_NUM];
Vctr q_place_holder[MARKERS_NUM];
clock_t bad_res_begin;
bool bad_res = false;

bool has_estimation = false;
double eye[MARKERS_NUM][MARKERS_NUM] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
};
Vctr results;
VideoCapture cap(4);


//GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
//GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
//GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
//        {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
//        {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
//GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
//        {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
//        {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
//GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
//
//void drawBox(void)
//{
//    int i;
//
//    for (i = 0; i < 6; i++) {
//        glBegin(GL_QUADS);
//        glNormal3fv(&n[i][0]);
//        glVertex3fv(&v[faces[i][0]][0]);
//        glVertex3fv(&v[faces[i][1]][0]);
//        glVertex3fv(&v[faces[i][2]][0]);
//        glVertex3fv(&v[faces[i][3]][0]);
//        glEnd();
//    }
//}
//
//void display(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    drawBox();
//    glutSwapBuffers();
//}
//
//void init(void)
//{
//    /* Setup cube vertex data. */
//    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
//    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
//    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
//    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
//    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
//    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
//
//    /* Enable a single OpenGL light. */
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);
//
//    /* Use depth buffering for hidden surface elimination. */
//    glEnable(GL_DEPTH_TEST);
//
//    /* Setup the view of the cube. */
//    glMatrixMode(GL_PROJECTION);
//    gluPerspective( /* field of view in degree */ 40.0,
//            /* aspect ratio */ 1.0,
//            /* Z near */ 1.0, /* Z far */ 10.0);
//    glMatrixMode(GL_MODELVIEW);
//    gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
//              0.0, 0.0, 0.0,      /* center is at (0,0,0) */
//              0.0, 1.0, 0.);      /* up is in positive Y direction */
//
//    /* Adjust cube position to be asthetic angle. */
//    glTranslatef(0.0, 0.0, -1.0);
//    glRotatef(60, 1.0, 0.0, 0.0);
//    glRotatef(-20, 0.0, 0.0, 1.0);
//}





void find_centers(Mat image, PointType centers[]){
    Mat image_gray;
    Mat image_thresh;
    Mat image_labeled;
    if (!image.data){
        cout<<"could not open the image"<<endl;
        exit(0);
    }
    cvtColor( image, image_gray, CV_BGR2GRAY );
    threshold( image_gray, image_thresh, 150, 255,0);

    Mat img_bw = image_thresh > 150;
    imshow("the markers: ", img_bw);
    Mat stats;
    Mat centroids;
    int label_n = connectedComponentsWithStats(img_bw, image_labeled,stats,centroids);
    if (label_n < 3){
        cout<<"not enough marks detected"<<endl;
    }
    for(int i=0;i<3;i++){
        centers[i].x = centroids.at<double>(i + 1,0);
        centers[i].y = centroids.at<double>(i + 1,1);
        centers[i].z = focal_len;
//        cout<<centers[i].x<<" "<<centers[i].y<<endl;
    }
    return;
}

void adjustABC(PointType centers[], double u, double v){
    centers[0].x -= u;
    centers[0].y *= -1;
    centers[0].y += v;

    centers[1].x -= u;
    centers[1].y *= -1;
    centers[1].y += v;

    centers[2].x -= u;
    centers[2].y *= -1;
    centers[2].y += v;
    return;
}


double first_estimation(PointType centers[], PointType points[]){
    double lad_i = sqrt(pow((centers[0].x - centers[1].x), 2) + pow((centers[0].y - centers[1].y), 2) + pow((centers[0].z - centers[1].z), 2));
    double lad_xyz = sqrt(pow((points[0].x - points[1].x), 2) + pow((points[0].y - points[1].y), 2) + pow((points[0].z - points[1].z), 2));
    return lad_xyz * focal_len / lad_i;
}


double eucleadian_dist(PointType a, PointType b){
    double res;
    res = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
    return res;
}

double dot_prod(Vctr v, Vctr u){
    double a = (v.x * u.x) + (v.y * u.y) + (v.z * u.z);
    return a;
}

void update_jac(double jac[][MARKERS_NUM], double a[], double t[][MARKERS_NUM]){
    //  todo recheck this :
    jac[0][0] = 2 * a[0] - 2 * a[1] * t[0][1];
    jac[0][1] = 2 * a[1] - 2 * t[0][1] * a[0];
    jac[0][2] = 0;
    jac[1][0] = 2 * a[0] - 2 * t[0][2] * a[2];
    jac[1][1] = 0;
    jac[1][2] = 2 * a[2] - 2 * a[0] * t[0][2];
    jac[2][0] = 0;
    jac[2][1] = 2 * a[1] - 2 * a[2] * t[1][2];
    jac[2][2] = 2 * a[2] - 2 * t[1][2] * a[1];
}

void update_f(double f[][1], double a[], double d[][MARKERS_NUM], double t[][MARKERS_NUM]){
    //  todo recheck this :
    f[0][0] = a[0] * a[0] - 2 * a[0] * a[1] * t[0][1] + a[1] * a[1] - d[0][1] * d[0][1];
    f[1][0] = a[0] * a[0] - 2 * a[0] * a[2] * t[0][2] + a[2] * a[2] - d[0][2] * d[0][2];
    f[2][0] = a[1] * a[1] - 2 * a[1] * a[2] * t[1][2] + a[2] * a[2] - d[1][2] * d[1][2];
}

void transpose(double matrixA[][MARKERS_NUM], double T[][MARKERS_NUM], int n, int m){
    for (int i = 0; i<n; i++){
        for (int j = 0; j<m; j++){
            T[i][j] = matrixA[j][i];
        }
    }
}

void matrix_prod(double matrixA[][MARKERS_NUM], double matrixB[][MARKERS_NUM], double matrixC[][MARKERS_NUM], int l, int n, int m){
    for (int i = 0; i<l; i++){
        for (int j = 0; j<n; j++){
            matrixC[i][j] = 0;
            for (int k = 0; k<m; k++){
                matrixC[i][j] = matrixC[i][j] + (matrixA[i][k] * matrixB[k][j]);
            }
        }
    }
}

void matrix_prod_3X1(double matrixA[][MARKERS_NUM], double matrixB[][1], double matrixC[][1], int l, int n, int m){
    for (int i = 0; i<l; i++){
        for (int j = 0; j<n; j++){
            matrixC[i][j] = 0;
            for (int k = 0; k<m; k++){
                matrixC[i][j] = matrixC[i][j] + (matrixA[i][k] * matrixB[k][j]);
            }
        }
    }
}

void inverse(double M[][MARKERS_NUM], double I[][MARKERS_NUM]){
    double det = M[0][0] * (M[1][1]*M[2][2] - M[1][2]*M[2][1]);
    det -= M[0][1] * (M[1][0]*M[2][2] - M[1][2]*M[2][0]);
    det += M[0][2] * (M[1][0]*M[2][1] - M[1][1]*M[2][0]);
    I[0][0] = (M[1][1]*M[2][2] - M[1][2]*M[2][1])/det;
    I[0][1] = (M[0][2]*M[2][1] - M[0][1]*M[2][2])/det;
    I[0][2] = (M[0][1]*M[1][2] - M[0][2]*M[1][1])/det;

    I[1][0] = (M[1][2]*M[2][0] - M[1][0]*M[2][2])/det;
    I[1][1] = (M[0][0]*M[2][2] - M[0][2]*M[2][0])/det;
    I[1][2] = (M[0][2]*M[1][0] - M[0][0]*M[1][2])/det;

    I[2][0] = (M[1][0]*M[2][1] - M[1][1]*M[2][0])/det;
    I[2][1] = (M[0][1]*M[2][0] - M[0][0]*M[2][1])/det;
    I[2][2] = (M[0][0]*M[1][1] - M[0][1]*M[1][0])/det;


}

double min_abs(double arr[][1]){
    double min = std::numeric_limits<double>::infinity();
    for(int i=0;i<MARKERS_NUM;i++){
        if (arr[i][0] < min){
            min = abs(arr[i][0]);
        }
    }
    return min;
}

double max_3(double arr[][1]){
    double max = -1 * std::numeric_limits<double>::infinity();
    for(int i=0;i<MARKERS_NUM;i++){
        if (arr[i][0] > max){
            max = abs(arr[i][0]);
        }
    }
    return max;
}

int calc_delta(double jac[][MARKERS_NUM], double func[][1], double lambda, double result[][1]){
    double jj[MARKERS_NUM][MARKERS_NUM];
    double jj_inv[MARKERS_NUM][MARKERS_NUM];
    double jac_T[MARKERS_NUM][MARKERS_NUM];
    //todo do we need this?
    transpose(jac, jac_T, MARKERS_NUM, MARKERS_NUM);
    matrix_prod(jac_T, jac, jj, MARKERS_NUM, MARKERS_NUM, MARKERS_NUM);
    for (int i =0;i<MARKERS_NUM;i++){
        for(int j=0;j<MARKERS_NUM;j++){
            jj[i][j] += eye[i][j] * lambda;
        }
    }
    inverse(jj, jj_inv);
    double jjj[MARKERS_NUM][MARKERS_NUM];
    matrix_prod(jj_inv, jac_T, jjj, MARKERS_NUM, MARKERS_NUM, MARKERS_NUM);
    matrix_prod_3X1(jjj, func, result, MARKERS_NUM, 1, MARKERS_NUM);
    return result[0][0];
}


void find_abc(PointType points[]) {
    double dist[3] = {
            eucleadian_dist(points[0],points[1]),
            eucleadian_dist(points[0],points[2]),
            eucleadian_dist(points[1],points[2]),
    };
    double *max = max_element(dist,dist + 3);
    int I = max - &dist[0];
    switch(I){
        case 0:
            if(dist[1] > dist[2]){
                return;
            }else{
                PointType temp = points[0];
                points[0] = points[1];
                points[1] = temp;
            }
        case 1:
            if(dist[0] > dist[2]){
                PointType temp = points[2];
                points[2] = points[1];
                points[1] = temp;
            }else{
                PointType temp = points[0];
                points[0] = points[2];
                points[2] = points[1];
                points[1] = temp;
            }
        case 2:
            if(dist[0] > dist[1]){
                PointType temp = points[0];
                points[0] = points[1];
                points[1] = points[2];
                points[2] = temp;
            }else{
                PointType temp = points[0];
                points[0] = points[2];
                points[2] = temp;
            }

    }}

void init_setting() {

    Origin.x = 0;
    Origin.y = 0;
    Origin.z = 0;
// 13 8
    double a = 40;
    double b = 70;
    double c = 60;
    double p = (a + b + c)/2;
    double s = sqrt(p * (p-a) * (p-b) * (p-c));
    double h = (s * 2)/a;
    double x = cos(asin(h/b));
    XYZ[0].x = 0;
    XYZ[0].y = 0;
    XYZ[0].z = 0;

    XYZ[1].x = a;
    XYZ[1].y = 0;
    XYZ[1].z = 0;

    XYZ[2].x = x;
    XYZ[2].y = h;
    XYZ[2].z = 0;

}

void stat_calib(Mat frame){
//    cout<<"stat_calib"<<endl;
    init_setting();
    // pre-processing:

    double d[MARKERS_NUM][MARKERS_NUM];
    for (int i = 0; i < MARKERS_NUM; i++){
        for (int j = 0; j < MARKERS_NUM; j++){
            d[i][j] = eucleadian_dist(XYZ[i], XYZ[j]);
        }
    }
    Vctr q[MARKERS_NUM];

    capture(ABC_points, frame);
    adjustABC(ABC_points, 163, 123);

    if(bad_res){

    } else{
        for (int i = 0; i<MARKERS_NUM; i++){
            q[i].x = ABC_points[i].x;
            q[i].y = ABC_points[i].y;
            q[i].z = -1 * focal_len;
            double temp = sqrt(q[i].x * q[i].x + q[i].y * q[i].y + q[i].z * q[i].z);
            q[i] = q[i] / temp;

            q_place_holder[i].x = q[i].x;
            q_place_holder[i].y = q[i].y;
            q_place_holder[i].z = q[i].z;
        }
    }
    double t[MARKERS_NUM][MARKERS_NUM];
    for (int i = 0; i < MARKERS_NUM;i++){
        for (int j = 0; j<MARKERS_NUM; j++){
            t[i][j] = dot_prod(q[i], q[j]);
        }
    }

    if (!has_estimation){
        double depth = first_estimation(ABC_points, XYZ);
        //needs change if number of markers are different
        a[0] = depth;
        a[1] = depth;
        a[2] = depth;
    }
    for(int i =0;i<MARKERS_NUM; i++){
        a_history[i] = a[i];
    }
    double func[MARKERS_NUM][1] = { 10, 10, 10 };
    int itr = 0;
    double jac[MARKERS_NUM][MARKERS_NUM];
    double delta[MARKERS_NUM][1] = {{100}, {100}, {100}};
    double lambda = 10;
    double fap[3][1] = {{1000}, {1000}, {1000}};
    double da = 100;
    while (da > 1.00e-8 && itr<100000){
        update_jac(jac, a, t);
        update_f(func, a, d, t);
        calc_delta(jac, func, lambda, delta);
        da = 0;
        for (int i = 0; i<MARKERS_NUM; i++){
            da = abs(max_3(delta));
//            da = abs(max_abs(delta));
//            a[i] = a[i] + STEP * delta;
            a[i] = a[i] - delta[i][0];
        }
        itr++;
        if(min_abs(func) <min_abs(fap)){
            lambda *= 10;
        } else{
            lambda /= 10;
        }
        for (int i =0;i<MARKERS_NUM;i++){
            fap[i][0] = func[i][0];
        }
    }
    has_estimation = true;
    Vctr A[MARKERS_NUM];

    double diff = 0;
    for(int i =0;i<MARKERS_NUM; i++){
        diff += abs(a_history[i] - a[i]);
    }

    if(diff > 150){
        bad_res = true;
        bad_res_begin = clock();
        for(int i =0;i<MARKERS_NUM; i++){
            a_place_holder[i] = a_history[i];
        }
        cout<<"diff? : "<<diff<<endl;
    }

    if(bad_res){
        cout<<"bad res"<<endl;
        for(int i =0;i<MARKERS_NUM; i++){
            A[i] = q_place_holder[i] * a_place_holder[i];
        }

        for(int i =0;i<MARKERS_NUM; i++){
            diff += abs(a[i] - a_place_holder[i]);
        }
        if(diff < 150){
            bad_res = false;
        }
        clock_t now = clock();
        double elapsed_secs = double(now - bad_res_begin) / CLOCKS_PER_SEC;
        if (elapsed_secs > 3){
            bad_res = false;
        }
    }
    else{
        for(int i =0;i<MARKERS_NUM; i++){
            A[i] = q[i] * a[i];
        }
    }
    results = (A[0] + A[1] + A[2])/(double)3;
    cout<<"results : "<<results.x<<" "<<results.y<<" "<<results.z<<endl;

//    cout<<results.x<<" "<<results.y<<" "<<results.z<<endl;
//    cout<<"static calib ended"<<endl;
}

Vctr camera_location;

void renderScene(void) {
    // Clear Color and Depth Buffers

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

//    todo
//    make camera look at the origin with angle
    // Set the camera

//    camera_location = (camera_location + results)/2;
    camera_location = results;
    cout<<camera_location.x<<" "<<camera_location.y<<" "<<camera_location.z<<" "<<endl;

//    gluLookAt(	camera_location.x / (-10), camera_location.y / (10 * 5), camera_location.z / (-1 * 10 * 8),
    gluLookAt(camera_location.x / (- 20), camera_location.y / (20), camera_location.z/(-30),
              0.0f, 0.0f,  0.0f,
              0.0f, 1.0f,  0.0f);

//    drawBox();
    glTranslatef(1.5f, 0.0f, 0.0f);  // Move right and into the screen
    draw_box();
    glTranslatef(-1.5f, 0.0f, 0.0f);  // Move left and into the screen
    draw_pyra();
    glutSwapBuffers();
    usleep(50000);

}

//void start_gl(int argc, char **argv){
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutCreateWindow("red 3D lighted cube");
//    glutDisplayFunc(display);
//    init();
//    glutIdleFunc(renderScene);
//    glutMainLoop();
//}



/* Main function: GLUT runs as a console application starting at main() */
int start_gl(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("scene");          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutIdleFunc(renderScene);
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}


int main(int argc, char **argv){
    results.y = -50;
    results.z = -200;
    camera_location.x = 60;
    camera_location.y = -50;
    camera_location.z = -200;
//    // open the default camera, use something different from 0 otherwise;
//    // Check VideoCapture documentation.
    std::thread gl_thread(start_gl,argc, argv);
    if(!cap.open(0)) {
        cout << "no frame" << endl;
        return 0;
    }
    for(;;){
        Mat frame;
        cap >> frame;
        if( frame.empty() ) break; // end of video stream
        stat_calib(frame);
//        imshow("this is you, smile! :)", frame);
        if( waitKey(10) == 'x' ) break; // stop capturing by pressing ESC
        usleep(50000);
    }

    //    main_graphics_function(argc, argv);

    // the camera will be closed
    return 0;
}






