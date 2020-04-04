# cs_5500_project

To Compile:
mpic++ main.cpp Convolution.cpp Filter.cpp Image.cpp

To Run:
mpirun -np [number of processes] a.out [image number range 1:3] [filter number range 1:6] 

Image Numers
  1: cabin.PPM
  2: squid.PPM
  3. tetons.PPM
  
Filter Numbers
  1: Scharr
  2: Sobel
  3: Gaussian
  4: Rainbow
  5: Sharpen
  6: All Filters
  
