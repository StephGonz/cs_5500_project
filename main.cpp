#include <chrono>
#include <iostream>
#include <mpi.h>
#include <string>
#include <time.h>
#include <vector>

#include "Convolution.hpp"
#include "Image.hpp"

using namespace std;
#define MCW MPI_COMM_WORLD

int main(int argc, char **argv) {
  int rank, size;
  int data;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MCW, &rank);
  MPI_Comm_size(MCW, &size);

  auto start = std::chrono::high_resolution_clock::now();

  Image squid = readPPM("./data/squid.PPM");
  int width = squid.getWidth();
  int height = squid.getHeight();

  int numRows = height / size;
  if (rank < static_cast<int>(height) % size) {
    ++numRows;
  }

  grayScale(squid);

  Image filter(3, 3);

  filter(0, 0) = Image::Rgb(-1);
  filter(1, 0) = Image::Rgb(-2);
  filter(2, 0) = Image::Rgb(-1);

  filter(0, 1) = Image::Rgb(0);
  filter(1, 1) = Image::Rgb(0);
  filter(2, 1) = Image::Rgb(0);

  filter(0, 2) = Image::Rgb(-1);
  filter(1, 2) = Image::Rgb(-2);
  filter(2, 2) = Image::Rgb(-1);

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
        finalImage(col, row) = convolve(col, row + startRow, squid, filter);
      } else {
        myWork(col, row) = convolve(col, row + startRow, squid, filter);
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
