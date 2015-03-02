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
bool training_on = 0;
bool get_counts = 0; //manually do this and the next numbers
bool testing_on = !training_on;
int countBmax = 8474455;//75145797; 
int countFmax= 1125545;//1654203;



//learning params for pixel classifier

int displayImage = 1; //show images for debug if needed
int nClusters = 2; //number of clusters for gmm
int countB =0, countF=0; //count back and foreground (red and not)
int countBext = 0, countFext = 0; //while extracting color info

Vec3b color; //3-d vec to store pixs of image
Vec2d probFg, probBg; // probabilities to belong to red(Fg) or not(Bg)

Mat samplesForeground = Mat(countFmax,3, CV_64F); //samples of classes
Mat samplesBackground = Mat(countBmax,3, CV_64F);

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
            Mat imtrain = imread(imgPath);
            Mat mask = imread(maskPath,0); //make sure to read in greyscale son
             
            
            
            
            
            // extract pixel info
	    if(imtrain.rows!=0 && imtrain.cols!=0) //do not read stuff that is not an image
		{

 		//printing for debug
		/*            	
		cout<<endl<<endl<<"found one  "<<imgPath<<endl<<maskPath<<endl;            
           	cout<<imtrain.size()<<" "<<imtrain.rows<<" "<<imtrain.cols<<endl;
		*/

		//count the number of pixels for each training data
		if(get_counts){ cout<<" getting counts "<<endl;
		for(int i=0; i<=mask.rows-1;i++) {
    			for(int j=0; j<=mask.cols-1;j++) {
       				 if((int)mask.at<uchar>(i,j)==255) {
            				countF++;
        				} else if((int)mask.at<uchar>(i,j)==0) {
            					countB++;
        					}
    					}
				} //end for all rows and cols
			      
		printf("countB %d countF %d \n", countB, countF); //print number of pix in classes
		} //end if(get_counts)
		else // if count of classes is known, get to work
		 { cout<<"extracting color info"<<endl;
		// extract color info from images
					
		
		

		// fill the training data from the former image depending of the mask
		for(int i=0; i<=mask.rows-1;i++) {
		    for(int j=0; j<=mask.cols-1;j++) {
			if((int)mask.at<uchar>(i, j)==255) { //if fg
			    color = imtrain.at<Vec3b>(i, j);
			    samplesForeground.at<double>(countF,0)=color[0];
			    samplesForeground.at<double>(countF,1)=color[1];
			    samplesForeground.at<double>(countF,2)=color[2];
			    countFext++;
			} else if((int)mask.at<uchar>(i, j)==0) { //if bg
			    color = imtrain.at<Vec3b>(i, j);
			    samplesBackground.at<double>(countB, 0)=color[0];
			    samplesBackground.at<double>(countB, 1)=color[1];
			    samplesBackground.at<double>(countB, 2)=color[2];
			    countBext++;
			}
		    }
		  } //end extraction of color




		 } //end else if(get_counts)
		}	//end check for emptiness of image
           
            
        } //end while training dir not empty
        closedir (dir);
    } else {
        cout<<"not present"<<endl;
    }    
	//sanity check and printing
	/*	
	cout<<endl<<" found and extracted fg pixels " <<countFext<<endl;
	cout<<endl<<" found and extracted bg pixels " <<countBext<<endl;
	cout<<endl<<" should have found "<<countFmax<<" and "<<countBmax<<endl<<endl;
	*/
	
	//now that extraction is done, train stuff
	
	//train 'em gmms through em
	cout<<endl<<"Training"<<endl;

	Mat labels1; //dummy vars
	Mat labels2;

	if(!get_counts){ //check again if not just counting
	cout<<endl<<"EM for fg"<<endl;
	Ptr<EM> em_foreground = EM::train( samplesForeground, noArray(), noArray(), noArray(),
		    EM::Params(nClusters, EM::COV_MAT_SPHERICAL,
		               TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 3000, 0.001)));

	cout<<endl<<"EM for bg"<<endl;
	Ptr<EM> em_background = EM::train( samplesBackground, noArray(), labels2, noArray(),
		    EM::Params(nClusters, EM::COV_MAT_SPHERICAL,
		               TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 3000, 0.001)));


	// save 'em
	cout<<endl<<" Writing xml for EM models"<<endl<<endl;
	cv::FileStorage fs("model.xml",cv::FileStorage::WRITE);
	em_foreground->write(fs);
	
		

	

		} //end check and training if not counting

 } //end if training_on

if(testing_on)
 {	    				
	    DIR *dir;	      
	    string dirName_ITP = "Images/Test/Pics/";	
	    string dirName_ITM = "Images/Test/Masks/mask.";
	    dir = opendir(dirName_ITP.c_str());
	    string imgName;
	    struct dirent *ent;

	    


	    if (dir != NULL) { //read test images in Test dir
		while ((ent = readdir (dir)) != NULL) {
		     
		string imgPath(dirName_ITP + ent->d_name);   // image name for train
    	        string maskPath(dirName_ITM + ent->d_name); //mask for this image
                Mat imtest = imread(imgPath);
                Mat mask = imread(maskPath,0); //make sure to read in greyscale son	
		
               cout<<endl<<endl<<"found one  "<<imgPath<<endl;
	       cout<<imtest.size()<<" "<<imtest.rows<<" "<<imtest.cols<<endl;
		}
		closedir (dir);
	    } else {
		cout<<"not present"<<endl;
	    }	


 } //end testing
return 0;
} //end main
