Folder Setup
*******************************************
-ROOT/
	-trainImg/	: Folder containing all training images
	-trainLabel/	: Folder containing corresponding training labels as specified in the kitti dataset
	-testImg/	: Folder containing all test images
	-testLabel/	: Folder containing corresponding testing labels as specified in the kitti dataset 
	-negativeFolder/	: Folder containing all negative instances for training
	-devkit/	: toolkit (must be added to matlab path)
	params.txt	: user specified parameters for training classifiers
	train.sh	: bash script for starting the training process
	train.m	: main matlab file, which gets called from train.sh
	genPosInstances.m	: generates positive instances MATLAB struct for training
	genClassifiers.m	: generates user specified classifiers
********************************************

INSTRUCTIONS
********************************************
1. cd to ROOT folder
2. Create a symbolic link to MATLAB in the ROOT folder
	ln -s <path to MATLAB executable> matlab
	eg. ln -s /usr/local/MATLAB/R2014a/bin/matlab matlab
3. Run ./train.sh
********************************************
