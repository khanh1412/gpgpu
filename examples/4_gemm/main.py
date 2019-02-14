#!/usr/bin/env python3
import numpy as np
import time
size = 4096
np.random.seed(int(time.time()))
alpha = np.random.normal(0, 1)
beta = np.random.normal(0, 1)
a = np.random.normal(0, 1, [size,size]).astype(np.float32)
b = np.random.normal(0, 1, [size,size]).astype(np.float32)
c = np.random.normal(0, 1, [size,size]).astype(np.float32)
t1 = time.time()
c = alpha * np.matmul(a, b) + beta * c
t2 = time.time()
print("Time: {} ns".format(1e9*(t2-t1)), end = "\n")
