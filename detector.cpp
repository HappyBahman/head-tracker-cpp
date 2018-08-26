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
//    IplConvKernel *convKernel = cvCreateStructuringElementEx(filterSize, filterSize, (filterSize - 1) / 2, (filterSize - 1) / 2, CV_SHAPE_RECT, NULL);

    VideoCapture cap(4);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    Mat planes[3];
    split(frame, planes);
    imshow("this is you, smile! :)", frame);

//    Mat yellow = (planes[2] + planes[1])/2 - planes[0];
    Mat yellow = (planes[0]) - planes[2];
    Mat bg = (planes[2]) + (255 - planes[0]);
//    Mat blue = planes[0];

    imshow("blue - red", yellow);
    imshow("red - blue", bg);

//    imshow("green", planes[1]);
//    imshow("blue", planes[0]);
//    imshow("red", planes[2]);

    yellow = yellow > 50;
    bg = bg < 50;

    imshow("blue - red thr", yellow);
    imshow("red - blue thr", bg);



//    Mat ell_rect = getStructuringElement(MORPH_RECT, Size(10,10));

//    dilate(yellow,yellow, ell_rect);

    Mat el1 = getStructuringElement(MORPH_ELLIPSE, Size(2,2));
    morphologyEx(yellow, yellow, MORPH_ERODE, el1);
    Mat el2 = getStructuringElement(MORPH_ELLIPSE, Size(12,12));
    morphologyEx(yellow, yellow, MORPH_DILATE, el2);


    Mat yellow_centroids;
    Mat yellow_image_labeled;
    Mat yellow_stats;
    int yellow_label_n = connectedComponentsWithStats(yellow, yellow_image_labeled, yellow_stats, yellow_centroids);

//    for( int i = 0; i< contours.size(); i++ )
//    {
//        double area = contourArea(contours[i]);
//        double perimeter = arcLength(contours[i],true);
//        cout<<"area : "<<area<<endl;
//        cout<<"perim : "<<perimeter<<endl;
//
//    }

    if (yellow_label_n < 4){
        cout<<"not enough markers found"<<endl;
        return 0;
    }
    if(yellow_label_n > 4){
        Mat opened_yellow;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        /// Find contours
        findContours( yellow, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        /// Show in a window

        double max_compactness[3] = {-1, -1, -1};
        int max_ind[3] = {-1,-1,-1};
        int cnt_cnt = 0;

        for( int i = 0; i< contours.size(); i++ )
        {
            double area = contourArea(contours[i]);
            double perimeter = arcLength(contours[i],true);
            double compactness = area/(perimeter * perimeter);
            if(compactness > max_compactness[0]){
                cnt_cnt++;
                max_compactness[2] = max_compactness[1];
                max_ind[2] = max_ind[1];
                max_compactness[1] = max_compactness[0];
                max_ind[1] = max_ind[0];
                max_compactness[0] = compactness;
                max_ind[0] = i;
            }else if(compactness > max_compactness[1]){
                cnt_cnt++;
                max_compactness[2] = max_compactness[1];
                max_ind[2] = max_ind[1];
                max_compactness[1] = compactness;
                max_ind[1] = i;
            }else if(compactness > max_compactness[2]){
                cnt_cnt++;
                max_compactness[2] = compactness;
                max_ind[2] = i;
            }
        }

        if(cnt_cnt >= 3 ){

            Mat drawing = Mat::zeros( yellow.size(), CV_8UC1 );
            RNG rng(12345);
            for( int i = 0; i< 3; i++ )
            {
                Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
//            Scalar color = Scalar( 255, 255, 255 );
                drawContours( drawing, contours, max_ind[i], color, 2, 8, hierarchy, 0);

                double area = contourArea(contours[max_ind[i]]);
                double perimeter = arcLength(contours[max_ind[i]],true);
                double compactness = area/(perimeter * perimeter);
                cout<<compactness<<" "<<area<<" "<<" "<<perimeter<<endl;


            }
//        dilate(drawing, drawing, ell);
            Mat temp;
            Mat rec_ell = getStructuringElement(MORPH_ELLIPSE, Size(5,5));
            do{
                temp = drawing.clone();
                dilate(drawing, opened_yellow, rec_ell); // normal dilation
                min(yellow, opened_yellow, drawing); // masking operation
            }while(!countNonZero(drawing != temp) == 0);
            yellow = drawing.clone();
        }
        yellow_label_n = connectedComponentsWithStats(yellow, yellow_image_labeled, yellow_stats, yellow_centroids);
    }

//    imshow("yellow", yellow);
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


