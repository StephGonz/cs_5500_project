#include <chrono>
#include <iostream>
#include <mpi.h>
#include <string>
#include <time.h>
#include <vector>

#include "Convolution.hpp"
#include "Filter.hpp"
#include "Image.hpp"

using namespace std;
#define MCW MPI_COMM_WORLD

int main(int argc, char **argv) {
  int rank, size;
  int data;
  int filterNum;
  int imageNum;
  int err;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MCW, &rank);
  MPI_Comm_size(MCW, &size);

  if(rank == 0)
  {
    if(argc != 3)
    {
      std::cout << "Two arguments are expected to run this program" << std::endl;
      std::cout << "Arg 1 = number representing the image to use" << std::endl;
      std::cout << "Image Numbers\n1 : Cabin\t 2 : Squid\t 3 : Tetons" << std::endl;
      std::cout << "Arg 2 = number representing the filter to use" << std::endl;
      std::cout << "Filter Numbers\n1 : Scharr\t 2 : Sobel\t 3 : Gaussian" << std::endl;
      std::cout << "4 : Rainbow\t 5 : Unsharp\t 6 : All" << std::endl;
      std::cout << "Examples:\nCabin with Scharr filter\tmpirun -np 4 a.out 1 1" << std::endl;
      std::cout << "Squid with Rainbow filter\tmpirun -np 4 a.out 2 4" << std::endl;
      std::cout << "Tetons with Sobel filter\tmpirun -np 4 a.out 3 2" << std::endl;
      MPI_Abort(MCW, err);
    }
    else
    {
      imageNum = atof(argv[1]);
      filterNum = atof(argv[2]);
      if(imageNum < 1 || filterNum < 1) {
        std::cout << "Invalid parameters entered.\nArg 1 acceptable range 1 : 3\nArg 2 acceptable range 1 : 6" << std::endl;
        MPI_Abort(MCW, err);
      }
      if(imageNum > 3 || filterNum > 6) {
        std::cout << "Invalid parameters entered.\nArg 1 acceptable range 1 : 3\nArg 2 acceptable range 1 : 6" << std::endl;
        MPI_Abort(MCW, err);        
      }
    }
  }

  MPI_Barrier(MCW);

  imageNum = atof(argv[1]);
  filterNum = atof(argv[2]);

  auto start = std::chrono::high_resolution_clock::now();

  Image img;
  if(imageNum == 1) {
    img = readPPM("./data/cabin.PPM");
  } else if(imageNum == 2) {
    img = readPPM("./data/squid.PPM");
  } else {
    img = readPPM("./data/tetons.PPM");
  }

  int width = img.getWidth();
  int height = img.getHeight();

  int numRows = height / size;
  if (rank < static_cast<int>(height) % size) {
    ++numRows;
  }

  grayScale(img);


  Image filter = filters::getFilter(filterNum, rank);

  auto startRow = 0;
  for (int i = rank; i > 0; --i) {
    int tempRows = height / size;
    if (i - 1 < static_cast<int>(height) % size) {
      ++tempRows;
    }

    startRow += tempRows;
  }

  Image finalImage(width, height);
  Image myWork(width, numRows);
  if (rank == 0) {
  } else {
  }

  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < width; ++col) {
      // do work
      if (rank == 0) {
        finalImage(col, row) = convolve(col, row + startRow, img, filter);
      } else {
        myWork(col, row) = convolve(col, row + startRow, img, filter);
      }
    }
  }

  if (rank == 0) {
    // Recieve data
    int tempRows = 0;
    for (int i = 0; i < size - 1; ++i) {
      tempRows += height / size;
      if (i < static_cast<int>(height) % size) {
        ++tempRows;
      }

      int dataSize = height / size;
      if (i + 1 < static_cast<int>(height) % size) {
        ++dataSize;
      }

      MPI_Recv(&finalImage.pixels[tempRows * width], dataSize * width * 3,
               MPI_FLOAT, i + 1, 0, MCW, MPI_STATUS_IGNORE);
    }

    savePPM(finalImage, "./output/finalImage.ppm");

  } else {
    // Send data to thread 0
    MPI_Send(&myWork.pixels[0], numRows * width * 3, MPI_FLOAT, 0, 0, MCW);
  }

  MPI_Finalize();

  if (rank == 0) {
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("Duration: %li\n", duration.count());
  }

  return 0;
}
