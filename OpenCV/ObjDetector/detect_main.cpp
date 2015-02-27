#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <dirent.h>
#include <string.h>
#include "opencv2/ml.hpp"

using namespace cv;
using namespace std;
using namespace cv::ml;


int main(int, char**)
{

//general opts
bool training_on = 1;


//learning params for pixel classifier

int displayImage = 1; //show images for debug if needed
int nClusters = 2; //number of clusters for gmm
int countB =0, countF=0; //count back and foreground (red and not)

Vec3b color; //3-d vec to store pixs of image


//stuff to read from dir
DIR *dir; //for directory of images 

string dirName_ITP = "Images/Train/Pics/"; 
string dirName_ITM = "Images/Train/Masks/mask."; //mask dir + prefix of mask images

dir = opendir(dirName_ITP.c_str()); //open where train pics are


struct dirent *ent;


// read images from dir and get pixels of interest/not of interest

if(training_on)
 {
 if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) //while training image dir not empty
        {
             
    	    string imgPath(dirName_ITP + ent->d_name);   // image name for train
    	    string maskPath(dirName_ITM + ent->d_name); //mask for this image
            Mat img = imread(imgPath);
            Mat mask = imread(maskPath);
            /* printing for debug
            cout<<endl<<endl<<"found one  "<<imgPath<<endl<<maskPath<<endl;
            
            cout<<img.size()<<" "<<img.rows<<" "<<img.cols<<endl;
            */
            
            
            // extract pixel info
            
            
            
        }
        closedir (dir);
    } else {
        cout<<"not present"<<endl;
    }    
 }



}
