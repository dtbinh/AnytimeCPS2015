import numpy as np
import sys
#sys.path.append('/home/dhruva/Documents/Tools/opencv/build/lib')
import cv2
import time
import os
import glob
import math

"""
Vehicles = ['Car', 'Van', 'Truck', 'Tram']
Consider only if
   - height of bounding box > 40px
   - occlusion 0
   - truncation < 0.15
"""
epsilon = 1e-10

def areConditionsMet(object):
    if (float(object[7]) - float(object[5]) > 40 and float(object[1]) < 0.15 and int(float(object[2])) == 0):
        return True
    return False


'''
Given the filename label, returns the ground truth: vehicleTrue and dontCare list
'''


def getGroundTruth(fileName):
    vehicleLabels = ['Car', 'Van', 'Truck', 'Tram']
    vehicleTrue = []
    dontCare = []
    for object in open(fileName):
        # print object
        label = object.split(None, 1)[0]
        object = object.split()
        bbox = map(float, object[4:8])
        bbox[2] = bbox[2] - bbox[0]  # change to width
        bbox[3] = bbox[3] - bbox[1]  # change to height
        if label in vehicleLabels:
            # append to vehicleTrue list if certain conditions are met
            if (areConditionsMet(object)):
                vehicleTrue.append(bbox)
            # else append to don't care list
            else:
                dontCare.append(bbox)
        elif label == 'DontCare':
            dontCare.append(bbox)

    # convert to float
    # vehicleTrue = [map(float,e) for e in vehicleTrue]
    # dontCare = [map(float,e) for e in dontCare]
    return vehicleTrue, dontCare

def parseParams(params):
    paramsInt = []
    for param in params:
        if param[0]=='0':
            param[0] = 1.1
        else:
            param[0] = float(param[0])

        param[1:] = map(int, param[1:])
        if param[1]==0:
            param[1] = 4
        
        paramsInt.append(param)

    return paramsInt

'''
returns overlapping area between two rectangles.
'''


def areaOverlap(actualBbox, predictedBbox):
    ax, ay, aw, ah = actualBbox
    bx, by, bw, bh = predictedBbox
    # returns zero if rectangles don't intersect
    dx = min(ax + aw, bx + bw) - max(ax, bx)
    dy = min(ay + ah, by + bh) - max(ay, by)
    if (dx >= 0) and (dy >= 0):
        return dx * dy
    return 0


def area(actualBbox):
    return actualBbox[2] * actualBbox[3]


def getQuality(vehicleTrue, dontCare, bboxes):
    tp = []  # true positive: % area overlap
    fp = 0  # false positive

    for predictedBbox in bboxes:
        tpos = False
        dcare = False
        # true positive
        for actualBbox in vehicleTrue:
            overlap = areaOverlap(actualBbox, predictedBbox)
            if (overlap / area(actualBbox) > 0.7):
                tp.append(overlap / area(actualBbox))
                tpos = True
                break

        # check dont care
        if not tpos:
            for dcBbox in dontCare:
                overlap = areaOverlap(dcBbox, predictedBbox)
                if (overlap / area(dcBbox) > 0.7):
                    dcare = True
                    break

        # false positive: if neither true positive nor dont care
        if not tpos and not dcare:
            fp += 1

    # compute quality [alpha*N_fp, 1] -> [0,1]
    N_gt = len(vehicleTrue)  # number of ground truth instances
    N_tp = len(tp) # number of true positives
    alpha = 0.05  # penalty
    # corner case: if no vehicle in image
    if N_gt == 0:
        quality_1 = 1 
        quality_2 = (math.exp(-fp) - 1) # penalty term for FP
    else:
        ones = [1] * len(tp)
        overlap = [x / 0.7 for x in tp]
        # print ones
        # print overlap
        # quality = sum([1.0*x/N_gt for x in min(ones, overlap)]) - alpha*fp
        # changed from N_gt to N_tp since two predicted instances can lie on the same ground truth
        quality_1 = sum([1.0 * x / N_tp for x in min(ones, overlap)]) 
        quality_2 = (math.exp(-fp) - 1) # penalty term for FP

    quality = quality_1 + quality_2

    # debugging
    #print 'GroundTruth: ', N_gt,'|True positive: ', len(tp),'|False positive: ', fp
    #print quality, quality_1, quality_2
    
    # assert quality to be within bounds [-1,1]
    assert (quality+1>= epsilon and quality-1<=epsilon), 'Quality out of bounds! '+str(quality)
    return quality_1, quality_2


def main(args):
    # read input arguments
    #if (len(sys.argv) <= 3):
    #    sys.exit('Enter 3 arguments: classifier_path | test_image_dir | test_label_dir')
    #model = sys.argv[1]
    #test_imgs_path = sys.argv[2]
    #test_labels_path = sys.argv[3]

    # dir structure
    model_path = 'classifiers/'
    test_imgs_path = 'testImg/'
    test_labels_path = 'testLabel/'

    # read params from params.txt
    f_params = open('params_test.txt')
    params = []
    for i, line in enumerate(f_params):
        if i>=19:
            params.append(line.rstrip().split('\t'))

    f_params.close()
    # parse params
    params = parseParams(params)
    # print params
        

    f_results = open('results/results.txt', 'w')
    # for every classifier (P_t)
    for model in glob.glob(model_path+'*.xml'):

        totalTime = 0
        totalQuality = 0
        N = 0
        model_name = model.rsplit('/',1)[-1][:-4]
        # for every test parameter (P_r)
        param_index=1
        print 'Classifier: ', model
        for param in params:
            
            f_result = open('results/'+model_name+'_'+str(param_index)+'.txt', 'w')
            print 'Test parameters: ', param
            # for every test image
            for test_img_path in glob.glob(test_imgs_path+'*.png'):
                print 'Testing ', test_img_path, '|| ',

                # read img. convert to bw.
                test_img = cv2.imread(test_img_path)
                test_img_bw = cv2.cvtColor(test_img, cv2.COLOR_BGR2GRAY)
                
                # read corresponding label
                test_label_path = test_labels_path + test_img_path[-10:].replace('.png', '.txt')

                # get ground truth label
                vehicleTrue, dontCare = getGroundTruth(test_label_path)

                # predict
                # load model
                vehicle_cascade = cv2.CascadeClassifier(model)

                # test
                # (image[, scaleFactor[, minNeighbors[, flags[, minSize[, maxSize]]]]])
                # (img, scaleFactor=1.3, minNeighbors=4, minSize=(30, 30), flags = cv.CV_HAAR_SCALE_IMAGE)
                t0 = time.clock()
                bboxes = vehicle_cascade.detectMultiScale(test_img_bw, scaleFactor=param[0], minNeighbors=param[1], minSize=(param[2],param[3]), maxSize=(param[4],param[5]))
                timeCurrent = time.clock() - t0
                totalTime += timeCurrent

                # quality: compare predicted and ground truth
                quality_1, quality_2 = getQuality(vehicleTrue, dontCare, bboxes)
                quality = quality_1 + quality_2
                totalQuality += quality

                N += 1
                # write to file and print to console
                result_line = test_img_path+'\t'+'{0:.4f}'.format(quality)+'\t'+'{0:.4f}'.format(quality_1)+'\t'+'{0:.4f}'.format(quality_2)+'\t'+str(timeCurrent)+'\n'
                f_result.write(result_line)
                print 'Quality: ' '{0:.4f}'.format(quality), '| Time: ', timeCurrent
                
            f_result.close()
            meanTime = totalTime / N
            meanQuality = totalQuality / N
            print 'Mean Time: ', meanTime
            print 'Mean Quality: ', meanQuality
            f_results.write(model_name+'_'+str(param_index)+'\t'+'{0:.4f}'.format(meanQuality)+'\t'+'{0:.4f}'.format(meanTime)+'\n')
            
            param_index += 1
            
    f_results.close()
            


if __name__ == "__main__":
    main(sys.argv)
