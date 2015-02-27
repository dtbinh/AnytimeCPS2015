#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include </usr/local/include/opencv2/core/core.hpp>
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv_modules.hpp>

using namespace cv;
%using namespace std;

int main(int argc, char** argv )
{
  
Mat mask = imread("mask.tiff", 0);
Mat formerImage = imread("ImageFormer.tiff");
Mat currentImage = imread("ImageCurrent.tiff");

// number of cluster in the GMM 
int nClusters = 5;

int countB=0, countF=0;

Vec3b color;

Vec2d probFg, probBg; // probabilities to belong to the foreground or background from GMMs

//count the number of pixels for each training data
for(int c=0; c<=40;c++) {
    for(int l=0; l<=40;l++) {
        if(mask.at<BYTE>(l, c)==255) {
            countF++;
        } else if(mask.at<BYTE>(l, c)==0) {
            countB++;
        }
    }
}
printf("countB %d countF %d \n", countB, countF);

Mat samplesForeground = Mat(countF,3, CV_64F);

Mat samplesBackground = Mat(countB,3, CV_64F);


// Expectation-Maximization able to resolve the GMM and to predict the probability for a pixel to belong to the GMM.
EM em_foreground= EM(nClusters);
EM em_background= EM(nClusters);

countB=0;
countF=0;


// fill the training data from the former image depending of the mask
for(int c=0; c<=40;c++) {
    for(int l=0; l<=40;l++) {
        if(mask.at<BYTE>(l, c)==255) {
            color = formerImage.at<Vec3b>(l, c);
            samplesForeground.at<double>(countF,0)=color[0];
            samplesForeground.at<double>(countF,1)=color[1];
            samplesForeground.at<double>(countF,2)=color[2];
            countF++;
        } else if(mask.at<BYTE>(l, c)==0) {
            color = formerImage.at<Vec3b>(l, c);
            samplesBackground.at<double>(countB, 0)=color[0];
            samplesBackground.at<double>(countB, 1)=color[1];
            samplesBackground.at<double>(countB, 2)=color[2];
            countB++;
        }
    }
}

printf("countB %d countF %d \n", countB, countF);
em_foreground.train(samplesForeground);
em_background.train(samplesBackground);

Mat sample(1, 3, CV_64F);

// try every pixel of the current image and get the log likelihood
for(int c=0; c<=40;c++) {
    for(int l=0; l<=40;l++) {
        color = currentImage.at<Vec3b>(l,c);
        sample.at<double>(0)=color[0];
        sample.at<double>(1)=color[1];
        sample.at<double>(2)=color[2];
        probFg=em_foreground.predict(sample);
        probBg=em_background.predict(sample);
        if(probFg[0]>0 || probBg[0]>0)
            printf("probFg[0] %f probBg[0] %f \n", probFg[0], probBg[0]);
    }
}


    waitKey(0);

    return 0;
}
