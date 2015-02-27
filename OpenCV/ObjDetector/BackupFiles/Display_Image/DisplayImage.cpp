#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"



using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
	Mat M(2,2, CV_8UC3, Scalar(0,0,255));
	cout<<"M = "<<endl<<" "<<M<<endl<<endl;
        return -1;
    }

    Mat image;
    image = imread( argv[1], 0 );
    
	
	
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    int threshval = 120;		
    Mat bw = threshval < 128 ? (image < threshval) : (image > threshval);
    Mat labelImage(image.size(), CV_32S);		
    int nLabels = connectedComponents(bw, labelImage, 8);
    cout<<nLabels;		

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}
