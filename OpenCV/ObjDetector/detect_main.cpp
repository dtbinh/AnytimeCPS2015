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
bool testing_on = 1;//!training_on;
int countBmax = 8474455;//for 1.3,1.7,1.8,1.9,2.0; 
int countFmax= 1125545;//;



//learning params for pixel classifier

int displayImage = 1; //show images for debug if needed
int nClusters = 3; //number of clusters for gmm
string nClust = "3";
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
		cvtColor(imtrain,imtrain,COLOR_BGR2YCrCb); //convert image
 		//printing for debug
		/*            	
		cout<<endl<<endl<<"found one  "<<imgPath<<endl<<maskPath<<endl;            
           	cout<<imtrain.size()<<" "<<imtrain.rows<<" "<<imtrain.cols<<endl;
		*/

		//count the number of pixels for each training data
		if(get_counts){ cout<<" getting counts "<<endl;
				cout<<imgPath<<" "<<maskPath<<endl;
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
		
	cout<<endl<<" found and extracted fg pixels " <<countFext<<endl;
	cout<<endl<<" found and extracted bg pixels " <<countBext<<endl;
	cout<<endl<<" should have found "<<countFmax<<" and "<<countBmax<<endl<<endl;
	
	
	//now that extraction is done, train stuff
	
	//train 'em gmms through em
	cout<<endl<<"Training"<<endl;

	Mat labels1; //dummy vars
	Mat labels2;

	if(!get_counts){ //check again if not just counting
	cout<<endl<<"EM for fg"<<endl<<samplesForeground.size();
	Ptr<EM> em_foreground = EM::train( samplesForeground, noArray(), noArray(), noArray(),
		    EM::Params(nClusters, EM::COV_MAT_SPHERICAL,
		               TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 3000, 0.001)));

	cout<<endl<<"EM for bg"<<endl;
	Ptr<EM> em_background = EM::train( samplesBackground, noArray(), labels2, noArray(),
		    EM::Params(nClusters, EM::COV_MAT_SPHERICAL,
		               TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 3000, 0.001)));


	// save 'em
	cout<<endl<<" Writing xml for EM models"<<endl<<endl;

	string f1 = "model_fg";
	string b1 = "model_bg";
	string xml = ".xml";
	string fgname(f1+nClust+xml);
	string bgname(b1+nClust+xml);	
	
	cv::FileStorage fs_fg(fgname,cv::FileStorage::WRITE);
	em_foreground->write(fs_fg);
	cv::FileStorage fs_bg(bgname,cv::FileStorage::WRITE);
	em_background->write(fs_bg);
	
	// now get object data
		

	

		} //end check and training if not counting

 } //end if training_on

if(testing_on)
 {	    cout<<endl<<"Testing ... "<<endl;				
	    
	    //threshold if needed
            //long double lnThresh = -100000000000000000000; //-1 

	    // for the image files	
    	    DIR *dir;	      
	    string dirName_ITP = "Images/Test/Pics/";	
	    string dirName_ITM = "Images/Test/Masks/mask.";
	    dir = opendir(dirName_ITP.c_str());
	    string imgName;
	    struct dirent *ent;
		
	    // storage needed for predictions
  	    Mat sample(1, 3, CV_64F);
            Mat maskout; 
	    int countB = 0;	
	    int countF = 0;	
            Vec2d probFg, probBg; 
 
            // for CC
	    Mat labelImage;//(bw.size(), CV_32S);
            Mat stats;
	    Mat centroids; 		
	    int nLabels;

	    // read saved models from xmls
	    string ff1 = "model_fg";
	    string bb1 = "model_bg";
	    string xml1 = ".xml";
	    string namefg(ff1+nClust);
	    string namebg(bb1+nClust);			
	    string fggname(ff1+nClust+xml1);
	    string bggname(bb1+nClust+xml1);	
			
	    Ptr<EM> em_fg = EM::create(); //foreground pixs	
	    cv::FileStorage fs_fg(fggname,cv::FileStorage::READ);	
	    Ptr<EM> em_bg = EM::create(); //background pixs
	    cv::FileStorage fs_bg(bggname,cv::FileStorage::READ);
			

	    if(fs_fg.isOpened()) 
		{ cout<<endl<<" Reading for fg from xml"<<endl<<fggname<<endl;		    
		em_fg->read(fs_fg[namefg]);//em_fg->read(fs_fg["model_fg"]);
		fs_fg.release();
		}
	    
            if(fs_bg.isOpened()) 
		{ cout<<endl<<" Reading for bg from xml"<<endl<<bggname<<endl;		    
		em_bg->read(fs_bg[namebg]);//em_bg->read(fs_bg["model_bg"]);
		fs_bg.release();
		}



	    if (dir != NULL) { //read test images in Test dir
		while ((ent = readdir (dir)) != NULL) { //while images in here
		     
		string imgPath(dirName_ITP + ent->d_name);   // image name for train
    	        string maskPath(dirName_ITM + ent->d_name); //mask for this image
                Mat imtest = imread(imgPath);
		
                Mat mask = imread(maskPath,0); //make sure to read in greyscale son	
		
               
		
		 if(imtest.rows!=0 && imtest.cols!=0) //do not read stuff that is not an image
		{
		  cvtColor(imtest,imtest,COLOR_BGR2YCrCb); //convert
		  cout<<endl<<endl<<"found one  "<<imgPath<<endl;
	          cout<<imtest.size()<<" "<<imtest.rows<<" "<<imtest.cols<<endl;
		
                  // do some predicting now son  					
                  maskout = Mat::zeros( Size( imtest.rows, imtest.cols ), CV_8U);//CV_8UC3 );	
		  countB = 0;
		  countF = 0;
		
		  // go over each pixel in image
			for(int i=0; i<=imtest.rows-1;i++) {
			    for(int j=0; j<=imtest.cols-1;j++) {
				//cout<<endl<<i<<" "<<j<<endl;
				color = imtest.at<Vec3b>(i,j);
				sample.at<double>(0)=color[0];
				sample.at<double>(1)=color[1];
				sample.at<double>(2)=color[2];
	
				probFg=em_fg->predict2(sample, noArray());
				probBg=em_bg->predict2(sample, noArray());
	
				
				if(probFg[0]>1*probBg[0]){
				    countF++;    
				    maskout.at<char>(i,j) = 255;		   	
				   //printf("probFg[0] %f probBg[0] %f \n", probFg[0], probBg[0]);
				}
				else
				{   maskout.at<char>(i,j) = 0;
				}
			    }
			} // done going over pixels in image
				cout<<endl<<"red barrel pixels detected= "<<countF<<endl;
				namedWindow("Maskout", WINDOW_NORMAL);
				imshow("Maskout", maskout);
				waitKey(0);

		        // CC testing now
			labelImage = Mat::zeros(Size(imtest.rows,imtest.cols), CV_32S);
			nLabels = connectedComponentsWithStats(maskout, labelImage, stats, centroids,8);	
			std::vector<Vec3b> colors(nLabels);
    			colors[0] = Vec3b(0, 0, 0);//background
			    for(int label = 1; label < nLabels; ++label){
			        colors[label] = Vec3b( (rand()&255), (rand()&255), (rand()&255) );
    				}
    			Mat dst(maskout.size(), CV_8UC3);
    for(int r = 0; r < dst.rows; ++r){
        for(int c = 0; c < dst.cols; ++c){
            int label = labelImage.at<int>(r, c);
            Vec3b &pixel = dst.at<Vec3b>(r, c);
            pixel = colors[label];
         }
     }
	namedWindow("Connected Components",WINDOW_NORMAL);
    imshow( "Connected Components", dst );
    //write label
	string fldri = "Images/Labels/label";	
        	
	string fldrnclusti(fldri+nClust);	
	string symbli = "_";
	string fldrnclustsymbli(fldrnclusti+symbli);
	string labelimgfilei(fldrnclustsymbli+ent->d_name);
	imwrite(labelimgfilei,dst);

    // write label as matrix
string fldr = "Images/Labels/xml/label";	
        	
	string fldrnclust(fldr+nClust);	
	string symbl = "_";
	string fldrnclustsymbl(fldrnclust+symbl);
	string labelimgfile(fldrnclustsymbl+ent->d_name);
	string labelimgfileext(labelimgfile+".xml");
	
	cv::FileStorage file(labelimgfileext, cv::FileStorage::WRITE);
	file<<"Matrix"<<labelImage;
	
	cout<<endl<<"Labelimg written to"<<labelimgfileext<<endl;
waitKey(0);




		} //end test for emptyness of dir obj
	      } //out of images to test now
		closedir (dir);
	    } else {
		cout<<"not present"<<endl;
	    }	


 } //end testing
return 0;
} //end main
