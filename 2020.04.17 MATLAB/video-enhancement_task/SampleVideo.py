import numpy
import os
import cv2
from importRAW import loadRaw


filename = "./test.yuv"

[binarr, framesNum] = loadRaw(filename)

if framesNum <= 1:
    quit()

dstfilename = "./test.avi"

fourcc = cv2.VideoWriter_fourcc(*'FFV1')
video  = cv2.VideoWriter(dstfilename, fourcc, 50, (1024, 768), 1)

for i1 in range(framesNum):
    A = numpy.array(binarr[i1, :, :])

    (height, width) = numpy.shape(A)

    out = numpy.zeros([width, height], numpy.uint8)
    normalized = cv2.normalize(A, out, 255, 0, cv2.NORM_MINMAX)

    dst = numpy.uint8(numpy.rint(normalized))

    scaled = cv2.resize(dst, dsize=(1024, 768), interpolation=cv2.INTER_LINEAR)
    video.write(cv2.cvtColor(scaled, cv2.COLOR_GRAY2BGR))

if framesNum != 1:
    video.release()
