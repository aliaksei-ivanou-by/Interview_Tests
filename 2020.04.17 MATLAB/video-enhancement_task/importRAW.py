import numpy
import os
import configparser as ini
import cv2
        
def loadRaw(filename):

    file_path = filename

    file_path2 = os.path.splitext(file_path)
    file_path3 = os.path.dirname(file_path)

    cfg = ini.ConfigParser()
    cfg.read(file_path3 + '/dataDescription.ini')
    try:
        width  = int(cfg['Global']['width'])
    except KeyError:
        width  = 320
    try:
        height = int(cfg['Global']['height'])
    except KeyError:
        height = 240
    try:
        byteOrdering = cfg['Global']['byteOrdering']
    except KeyError:
        byteOrdering = 'LE'
    try:
        numOfFrames = int(cfg['Global']['numOfFrames'])
    except KeyError:
        numOfFrames = 1
        
    #
    try:
        f = open(file_path, 'rb')
    except FileNotFoundError:
        print('File not found ' + file_path)
        exit()
    binarr = numpy.fromfile(f, dtype=numpy.uint16, count=width * height * numOfFrames).reshape(numOfFrames, height, width)
    if byteOrdering == 'BE':
        binarr = ((binarr & 255) << 8) | ((binarr >> 8) & 255) 

    try:
        f.close
    except NameError:
        pass

    return binarr, numOfFrames
