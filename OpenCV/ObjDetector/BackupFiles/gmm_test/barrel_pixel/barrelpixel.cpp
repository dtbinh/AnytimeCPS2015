
/* EM to train and detect pixels belonging to a red barrel */


#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
//#include "opencv2/legacy/legacy.hpp"
//#include "opencv2/highgui/highgui.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/ml.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"


using namespace cv;
using namespace std;
using namespace cv::ml;


int main( int /*argc*/, char** /*argv*/ )
{   

// init vars


int displayImage = 1; //show images for debug if needed
int nClusters = 2; //number of clusters for gmm
int countB =0, countF=0; //count back and foreground (red and not)

Vec3b color; //3-d vec to store pixs of imahe








//read images

Mat mask = imread("images/Mask_1_3.png",0); //mask
Mat imtrain = imread("images/1.3.png"); 
Mat imtest = imread("images/1.6.png");

//cout<<endl<<(int)mask.rows<<endl; //checkout arbit mat commands here


Vec2d probFg, probBg; // probabilities to belong to red(Fg) or not(Bg)


// see max of mask 
/*
double max,min;
int maxIdx,minIdx;
minMaxIdx(mask, &min, &max, &minIdx, &maxIdx);
cout<<endl<<"max"<<max<<endl;
cout<<endl<<"min"<<min<<endl;
*/

//cout << maxIdx[0] << ", " << maxIdx[1] << ", " << maxIdx[2] << endl;

// 'twas 255, not 1




//count the number of pixels for each training data
for(int i=0; i<=mask.rows-1;i++) {
    for(int j=0; j<=mask.cols-1;j++) {
        if((int)mask.at<uchar>(i,j)==255) {
            countF++;
        } else if((int)mask.at<uchar>(i,j)==0) {
            countB++;
        }
    }
}
printf("countB %d countF %d \n", countB, countF);

// extract color info from images


Mat samplesForeground = Mat(countF,3, CV_64F);

Mat samplesBackground = Mat(countB,3, CV_64F);



// Expectation-Maximization able to resolve the GMM and to predict the probability for a pixel to belong to the GMM.
//Ptr<EM> em_foreground= EM::create(nClusters);
//EM em_background= EM(nClusters);

countB=0; //re-use
countF=0;

// fill the training data from the former image depending of the mask
for(int i=0; i<=mask.rows-1;i++) {
    for(int j=0; j<=mask.cols-1;j++) {
        if((int)mask.at<uchar>(i, j)==255) {
            color = imtrain.at<Vec3b>(i, j);
            samplesForeground.at<double>(countF,0)=color[0];
            samplesForeground.at<double>(countF,1)=color[1];
            samplesForeground.at<double>(countF,2)=color[2];
            countF++;
        } else if((int)mask.at<uchar>(i, j)==0) {
            color = imtrain.at<Vec3b>(i, j);
            samplesBackground.at<double>(countB, 0)=color[0];
            samplesBackground.at<double>(countB, 1)=color[1];
            samplesBackground.at<double>(countB, 2)=color[2];
            countB++;
        }
    }
}

cout<<endl;
printf("countB %d countF %d \n", countB, countF);


//train 'em gmms through em
cout<<endl<<"Training"<<endl;

Mat labels1;
Mat labels2;


Ptr<EM> em_foreground = EM::train( samplesForeground, noArray(), noArray(), noArray(),
            EM::Params(nClusters, EM::COV_MAT_SPHERICAL,
                       TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 3000, 0.001)));

/*Ptr<EM> em_foreground = EM::train( samplesForeground, noArray(), labels1, noArray(),
            EM::Params(nClusters, EM::COV_MAT_SPHERICAL));
*/

Ptr<EM> em_background = EM::train( samplesBackground, noArray(), labels2, noArray(),
            EM::Params(nClusters, EM::COV_MAT_SPHERICAL,
                       TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 3000, 0.001)));


//em_foreground.train(samplesForeground);
//em_background.train(samplesBackground);

// save 'em
cv::FileStorage fs("model.xml",cv::FileStorage::WRITE);
em_foreground->write(fs);


//em_foreground.write("emf.yaml");


//test it on some test image

Mat sample(1, 3, CV_64F);
Mat maskout = Mat::zeros( Size( imtest.rows, imtest.cols ), CV_8U);//CV_8UC3 );


// try every pixel of the test image and get the log likelihood
cout<<endl<<"Testing"<<endl;


double t = (double)getTickCount();

countB = 0;
countF = 0;


for(int i=0; i<=imtest.rows-1;i++) {
    for(int j=0; j<=imtest.cols-1;j++) {
	//cout<<endl<<i<<" "<<j<<endl;
        color = imtrain.at<Vec3b>(i,j);
        sample.at<double>(0)=color[0];
        sample.at<double>(1)=color[1];
        sample.at<double>(2)=color[2];
	
        probFg=em_foreground->predict2(sample, noArray());
        probBg=em_background->predict2(sample, noArray());
	
        //if(probFg[0]>0 && (probFg[0]>probBg[0])){
	if((probFg[0]>probBg[0])){
	    countF++;
	    maskout.at<char>(i,j) = 1;		   	
           // printf("probFg[0] %f probBg[0] %f \n", probFg[0], probBg[0]);
	}
	else
	{   maskout.at<char>(i,j) = 0;
	}
    }
}




t = ((double)getTickCount() - t)/getTickFrequency();
    cout<<endl<<"time taken to to predict "<<t<<endl;


cout<<endl<<"red barrel pixels detected= "<<countF<<endl;


// connected components


Mat bw = (maskout > 0); //make binary

namedWindow("Maskout", WINDOW_NORMAL);
imshow("Maskout", bw);

waitKey(0);

Mat labelImage(bw.size(), CV_32S);
Mat stats;
Mat centroids;
int object_number = 7;
cout<<endl<<"bw rows"<<bw.rows<<"bw cols"<<bw.cols;
int nLabels = connectedComponentsWithStats(bw, labelImage, stats, centroids, 8);
cout<<endl<<"nLabels"<<nLabels<<endl;
cout<<"STATS for label" <<object_number<<endl;
cout<<endl<<stats.at<int>(object_number,0)<<" "<<stats.at<int>(object_number,1)<<" "<<stats.at<int>(object_number,2)<<" "<<stats.at<int>(object_number,3)<<" "<<stats.at<int>(object_number,4)<<endl;
cout<<endl<<"stats size"<<stats.rows<<" "<<stats.cols<<endl;


//show cc img
std::vector<Vec3b> colors(nLabels);
    colors[0] = Vec3b(0, 0, 0);//background
    for(int label = 1; label < nLabels; ++label){
        colors[label] = Vec3b( (rand()&255), (rand()&255), (rand()&255) );
    }
    Mat dst(bw.size(), CV_8UC3);
    for(int r = 0; r < dst.rows; ++r){
        for(int c = 0; c < dst.cols; ++c){
            int label = labelImage.at<int>(r, c);
            Vec3b &pixel = dst.at<Vec3b>(r, c);
            pixel = colors[label];
         }
     }

    imshow( "Connected Components", dst );
    waitKey(0);  








//connectedComponentsWithStats(maskout, labels, stats, centroids, connectivity, CV_32S);

//sanity check of elements
double maxim,minim;
int maxIdx,minIdx;
minMaxIdx(maskout, &minim, &maxim, &minIdx, &maxIdx);
cout<<endl<<"max"<<maxim<<endl;
cout<<endl<<"min"<<minim<<endl;


// display images if needed

displayImage = 0;
if(displayImage)
{
namedWindow("Display Image", WINDOW_NORMAL);
imshow("Display Image", maskout);

waitKey(0);
}


 return 0;
}