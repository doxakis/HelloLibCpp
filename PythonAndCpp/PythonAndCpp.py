from ctypes import cdll, c_int
from array import array
import cv2
import numpy as np

mydll = cdll.LoadLibrary("..\Debug\HelloLibCpp.dll")

img = cv2.imread("form9.jpg", 0)
arr = img.flatten()
arr = (c_int * len(arr))(*arr)

result = mydll.parseFileCpp(arr, len(arr))
print("Result: " + str(result))

result = mydll.parseFileC(arr, len(arr))
print("Result: " + str(result))
