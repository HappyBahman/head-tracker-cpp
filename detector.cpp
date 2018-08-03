//
// Created by Bahman on 6/29/2018.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>

#include "PointType.h"

using namespace std;
using namespace cv;


#define focal_len 984.375

int capture(PointType centers[], Mat frame){
    int filterSize = 5;
    IplConvKernel *convKernel = cvCreateStructuringElementEx(filterSize, filterSize, (filterSize - 1) / 2, (filterSize - 1) / 2, CV_SHAPE_RECT, NULL);

    VideoCapture cap(4);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    Mat planes[3];
    split(frame, planes);
    imshow("this is you, smile! :)", frame);

    Mat yellow = (planes[2] + planes[1])/2 - planes[0];
    yellow = yellow > 150;

    Mat ell = getStructuringElement(MORPH_ELLIPSE, Size(5,5));
    Mat opened_yellow;
    morphologyEx(yellow, opened_yellow, MORPH_OPEN, ell);

    Mat el1 = getStructuringElement(MORPH_ELLIPSE, Size(2,2));
    morphologyEx(opened_yellow, opened_yellow, MORPH_ERODE, el1);
    Mat el2 = getStructuringElement(MORPH_ELLIPSE, Size(12,12));
    morphologyEx(opened_yellow, opened_yellow, MORPH_DILATE, el2);





//    no need for opening
//    Mat ell = getStructuringElement(MORPH_ELLIPSE, Size(10,10));
//    Mat opened_yellow;
//    yellow = yellow > 0;
//    morphologyEx(yellow, opened_yellow, MORPH_OPEN, ell);

//    for detecting white areas, not needed anymore, kept in comment just in case
//    Mat gray;
//    cvtColor( frame, gray, CV_BGR2GRAY );
//    Mat ell_th = getStructuringElement(MORPH_ELLIPSE, Size(35,35));
//    Mat th;
//    Mat opened_white_th;
//    morphologyEx(gray, th, MORPH_TOPHAT, ell_th);
//    Mat white_th = th > 100;
//    white_th = white_th - yellow;
//    white_th = white_th > 0;
//    morphologyEx(white_th, opened_white_th, MORPH_OPEN, ell);

//    Mat blue = planes[0] - planes[2];
//    blue = blue > 30;
//    Mat opened_blue;
//    morphologyEx(blue, opened_blue, MORPH_OPEN, ell);
//
//
//    imshow("final blue", opened_blue);


//    ("blue", opened_blue);

    Mat yellow_centroids;
    Mat yellow_image_labeled;
    Mat yellow_stats;

    imshow("yellow", opened_yellow);

    int yellow_label_n = connectedComponentsWithStats(opened_yellow, yellow_image_labeled, yellow_stats, yellow_centroids);

    if (yellow_label_n < 4){
        cout<<"not enough markers found"<<endl;
        return 0;
    }
    if(yellow_label_n > 4){
        Mat el1 = getStructuringElement(MORPH_ELLIPSE, Size(2,2));
        morphologyEx(opened_yellow, opened_yellow, MORPH_ERODE, el1);
        Mat el2 = getStructuringElement(MORPH_ELLIPSE, Size(12,12));
        morphologyEx(opened_yellow, opened_yellow, MORPH_DILATE, el2);
        yellow_label_n = connectedComponentsWithStats(opened_yellow, yellow_image_labeled, yellow_stats, yellow_centroids);
    }
    if(yellow_label_n != 4){
        cout<<"marker numbers don't match  "<<yellow_label_n<<endl;
        return 0;
    }
    for(int i=0;i<yellow_label_n - 1;i++){
        centers[i].x = yellow_centroids.at<double>(i + 1,0);
        centers[i].y = yellow_centroids.at<double>(i + 1,1);
        centers[i].z = focal_len;

//        cout<<"yellow "<<centers[i + yellow_label_n - 1].x<<"  "<<centers[i + yellow_label_n - 1].y<<endl;
    }


//    Mat blue_centroids;
//    Mat blue_image_labeled;
//    Mat blue_stats;
//    int blue_label_n = connectedComponentsWithStats(opened_blue, blue_image_labeled, blue_stats, blue_centroids);
//    for(int i=0;i<blue_label_n - 1;i++){
//        centers[i + yellow_label_n - 1].x = blue_centroids.at<double>(i + 1,0);
//        centers[i + yellow_label_n - 1].y = blue_centroids.at<double>(i + 1,1);
//        centers[i].z = focal_len;
//
////        cout<<"blue "<<centers[i + yellow_label_n - 1].x<<"  "<<centers[i + yellow_label_n - 1].y<<endl;
//    }


//        put A, B and C in correct order:
//        A = far yellow, B= middle yellow, C = blue

//    if(abs(centers[0].x - centers[2].x) < abs(centers[1].x - centers[2].x)){
//        PointType temp = centers[0];
//        centers[0] = centers[1];
//        centers[1] = temp;
//    }

//      rightmost marker = biggest x = C
//      highest marker = A
//      middle marker = B
    if(centers[1].x < centers[0].x and centers[1].x < centers[2].x){
        PointType temp = centers[0];
        centers[0] = centers[1];
        centers[1] = temp;
    }else if(centers[2].x < centers[0].x and centers[2].x < centers[1].x){
        PointType temp = centers[0];
        centers[0] = centers[2];
        centers[2] = temp;
    }
    if (centers[1].y < centers[2].y){
        PointType temp = centers[1];
        centers[1] = centers[2];
        centers[2] = temp;
    }

//    cout<<centers[0].x<<" "<<centers[0].y<<" "<<centers[1].x<<" "<<centers[1].y<<" "<<centers[2].x<<" "<<centers[2].y<<endl;

    // the camera will be closed
    return 1;
}


