#!/bin/env python

import SimpleITK as sitk
import numpy as np
import math
import time

def marschner_lobb(size=40, alpha=0.25, f_M=6.0):
    img = sitk.PhysicalPointSource( sitk.sitkVectorFloat32, [size]*3, [-1]*3, [2.0/size]*3)
    imgx = sitk.VectorIndexSelectionCast(img, 0)
    imgy = sitk.VectorIndexSelectionCast(img, 1)
    imgz = sitk.VectorIndexSelectionCast(img, 2)
    del img
    r = sitk.Sqrt(imgx**2 + imgy**2)
    del imgx, imgy
    pr = sitk.Cos((2.0*math.pi*f_M)*sitk.Cos((math.pi/2.0)*r))
    return (1.0 - sitk.Sin((math.pi/2.0)*imgz) + alpha*(1.0+pr))/(2.0*(1.0+alpha))


ml = marschner_lobb(128)
zslice = ml.GetSize()[-1]//2
print zslice
ml = sitk.Normalize(ml)


n = np.random.normal(0, scale=1.0, size=ml.GetSize())
img_noise = sitk.GetImageFromArray(n)
img_noise.CopyInformation(ml)

resample = sitk.ResampleImageFilter()
resample.SetReferenceImage(ml)
resample.SetInterpolator(sitk.sitkNearestNeighbor)


cm_enum = sitk.ScalarToRGBColormapImageFilter.Jet
sn_list = [100.0, 2.0, 1.0, 1.0/2.0, 1.0/4.0]

#
# Bin Shrink
#
def my_shrink(img, shrink):
    return sitk.Normalize(resample.Execute(sitk.BinShrink(img,[shrink]*3)))

imgs = []
for sn in sn_list:

    img = (ml*sn+img_noise)/(1.0+sn)
    tiles = [sitk.Normalize(img),
             my_shrink(img,2),
             my_shrink(img,4)
             ]
    row = sitk.Tile(tiles,[len(tiles),1,1])[:,:,zslice]
    sitk.Show(row, "SN: "+str(sn))
    time.sleep(.1)

    imgs.extend( tiles )

t = sitk.Tile(imgs, [3,len(imgs)//3,1])

sitk.Show(sitk.ScalarToRGBColormap(t,cm_enum), "composite ")
sitk.WriteImage(sitk.ScalarToRGBColormap(t,cm_enum), "binshrink_hot.png")

#
# Gaussian
#

def my_smooth(img, shrink):
    sigma = shrink*0.7*img.GetSpacing()[0]
    s = sitk.Shrink(sitk.SmoothingRecursiveGaussian(img, sigma), [shrink]*3)
#   return sitk.Normalize(resample.Execute(s))
    return sitk.Normalize(sitk.SmoothingRecursiveGaussian(img, sigma))



imgs = []
for sn in sn_list:

    img = (ml*sn+img_noise)/(1.0+sn)
    tiles = [sitk.Normalize(img),
             my_smooth(img,2),
             my_smooth(img,4)
             ]
    row = sitk.Tile(tiles,[len(tiles),1,1])[:,:,zslice]
    sitk.Show(row, "Smooth SN: "+str(sn))
    time.sleep(.1)

    imgs.extend( tiles )

t = sitk.Tile(imgs, [3,len(imgs)//3,1])

sitk.Show(sitk.ScalarToRGBColormap(t,cm_enum), "Smooth composite ")
sitk.WriteImage(sitk.ScalarToRGBColormap(t,cm_enum), "gaussianshrink_hot.png")
