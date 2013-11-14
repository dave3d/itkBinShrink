#!/bin/env python

import SimpleITK as sitk
import numpy as np
import math
from timeit import Timer
import matplotlib.pyplot as plt


sz = [256]*3

n = np.random.normal(0, scale=1.0, size=sz).astype(np.float32)
img = sitk.GetImageFromArray(n)

# Bin Shrink
def my_shrink1(img, shrink):
    return sitk.BinShrink(img,[shrink]*3)


def my_shrink2(img, shrink):
    return sitk.BinShrink2(img,[shrink]*3)

def my_smooth(img,shrink):
    sigma = shrink*0.7*img.GetSpacing()[0]
    return sitk.Shrink(sitk.SmoothingRecursiveGaussian(img, sigma), [shrink]*3)

def my_mean(img,shrink):
    r = (shrink+1)//2
    return sitk.Shrink(sitk.Mean(img, [r]*3), [shrink]*3)

t_repeat = 3
t_number = 1
factors = [2,3,4,6,8,12,16,24,32]
#factors = [2,4,8]
med_times1 = []

print "Timing shrink1..."
for factor in factors:
    timer = Timer( lambda: my_shrink1(img, factor) )
    times = timer.repeat( repeat=t_repeat, number= t_number )
    med_times1.append(np.median(times) )

print "Timing shrink2..."
med_times2 = []
for factor in factors:
    timer = Timer( lambda: my_shrink2(img, factor) )
    times = timer.repeat( repeat=t_repeat, number= t_number )
    med_times2.append(np.median(times) )

print "Timing smooth..."
med_times3 = []
for factor in factors:
    timer = Timer( lambda: my_smooth(img, factor) )
    times = timer.repeat( repeat=t_repeat, number= t_number )
    med_times3.append(np.median(times) )

print "Timing mean..."
med_times4 = []
for factor in factors:
    timer = Timer( lambda: my_mean(img, factor) )
    times = timer.repeat( repeat=t_repeat, number= t_number )
    med_times4.append(np.median(times) )


plt.plot(factors,med_times1, 'ro:', label="BinShrink")
plt.plot(factors,med_times2, 'b^:', label="BinShrink2")
plt.plot(factors,med_times3, 'cs:', label="Gaussian Shrink")
plt.plot(factors,med_times4, 'gx:', label="Mean Shrink")
plt.yscale("log")
plt.legend(loc='upper center')
plt.xlabel("Shrink Size")
plt.ylabel("Time (seconds)")
plt.show()
