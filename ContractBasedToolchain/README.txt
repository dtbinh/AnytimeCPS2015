Folder Setup
*******************************************
-ROOT/
	-trainImg/	: Folder containing all training images
	-trainLabel/	: Folder containing corresponding training labels as specified in the kitti dataset
	-testImg/	: Folder containing all test images
	-testLabel/	: Folder containing corresponding testing labels as specified in the kitti dataset 
	-negativeFolder/	: Folder containing all negative instances for training
	-devkit/	: toolkit (must be added to matlab path)
	-classifiers/ 	: 	Directory containing all the .xml classifiers/models
	-results/	:	Results after testing (quality, time) for each parameter vector stored here. 
		results.txt		: 	classifier	| quality	| time
		classifier_#.txt	: testImg	| quality	| quality_1	| quality_2	| time
	params_train.txt	: user specified parameters for training classifiers
	train.sh	: bash script for starting the training process
	train.m	: main matlab file, which gets called from train.sh
	genPosInstances.m	: generates positive instances MATLAB struct for training
	genClassifiers.m	: generates user specified classifiers

	params_test.txt		:	parameters to enter for testing 
	test.py		:	main python file which computes quality and time for every parameter vector on the images stored in testImg
	test.sh		: bash script for starting the testing
	plotHist.m		: matlab file to read results and plot histograms
********************************************

INSTRUCTIONS
********************************************
1. cd to ROOT folder
2. Create a symbolic link to MATLAB in the ROOT folder
	ln -s <path to MATLAB executable> matlab
	eg. ln -s /usr/local/MATLAB/R2014a/bin/matlab matlab
3. Enter required training parameters in params_train.txt
4. Run ./train.sh
5. The classifiers/models will be stored as .xml files in classifiers/
6. Enter required testing parameters in params_test.txt
7. Run ./test.sh
8. Results stored in results/
9. Use plotHist.m to plot histograms
********************************************
