#include "Filter.hpp"
#include "Image.hpp"

Image filters::getFilter(int filterNum, int rank) {
  switch (filterNum)
  {
    case 1: return getScharrFilter();
    case 2: return getSobelFilter();    
    case 3: return getGaussianFilter();
    case 4: return getRainbowFilter(rank);
    case 5: return getSharpenFilter();
    case 6: return getAllFilters(rank);
  }
}

Image filters::getScharrFilter() {
  Image filter(3, 3);

  filter(0, 0) = Image::Rgb(1);
  filter(1, 0) = Image::Rgb(1);
  filter(2, 0) = Image::Rgb(0);
  
  filter(0, 1) = Image::Rgb(1);
  filter(1, 1) = Image::Rgb(0);
  filter(2, 1) = Image::Rgb(-1);
  
  filter(0, 2) = Image::Rgb(0);
  filter(1, 2) = Image::Rgb(-1);
  filter(2, 2) = Image::Rgb(-1);

  return filter;
}

Image filters::getSobelFilter() {
  Image filter(3, 3);

  filter(0, 0) = Image::Rgb(1);
  filter(1, 0) = Image::Rgb(2);
  filter(2, 0) = Image::Rgb(1);
  
  filter(0, 1) = Image::Rgb(0);
  filter(1, 1) = Image::Rgb(0);
  filter(2, 1) = Image::Rgb(0);
  
  filter(0, 2) = Image::Rgb(-1);
  filter(1, 2) = Image::Rgb(-2);
  filter(2, 2) = Image::Rgb(-1);

  return filter;
}

Image filters::getGaussianFilter() {
  Image filter(5, 5);
  
  filter(0, 0) = Image::Rgb(1.0/273);
  filter(1, 0) = Image::Rgb(4.0/273);
  filter(2, 0) = Image::Rgb(7.0/273);
  filter(3, 0) = Image::Rgb(4.0/273);
  filter(4, 0) = Image::Rgb(1.0/273);

  filter(0, 1) = Image::Rgb(4.0/273);
  filter(1, 1) = Image::Rgb(16.0/273);
  filter(2, 1) = Image::Rgb(26.0/273);
  filter(3, 1) = Image::Rgb(16.0/273);
  filter(4, 1) = Image::Rgb(4.0/273);
  
  filter(0, 2) = Image::Rgb(7.0/273);
  filter(1, 2) = Image::Rgb(26.0/273);
  filter(2, 2) = Image::Rgb(41.0/273);
  filter(3, 2) = Image::Rgb(26.0/273);
  filter(4, 2) = Image::Rgb(7.0/273);
  
  filter(0, 3) = Image::Rgb(4.0/273);
  filter(1, 3) = Image::Rgb(16.0/273);
  filter(2, 3) = Image::Rgb(26.0/273);
  filter(3, 3) = Image::Rgb(16.0/273);
  filter(4, 3) = Image::Rgb(4.0/273);
  
  filter(0, 4) = Image::Rgb(1.0/273);
  filter(1, 4) = Image::Rgb(4.0/273);
  filter(2, 4) = Image::Rgb(7.0/273);
  filter(3, 4) = Image::Rgb(4.0/273);
  filter(4, 4) = Image::Rgb(1.0/273);

  return filter;
}

Image filters::getRainbowFilter(int rank) {
  Image filter(1, 1);

  filter(0, 0) = Image::COLORS[rank % Image::COLORS.size()];

  return filter;
}

Image filters::getSharpenFilter() {
  Image filter(5, 5);

  filter(0, 0) = Image::Rgb(-1.0/256);
  filter(1, 0) = Image::Rgb(-4.0/256);
  filter(2, 0) = Image::Rgb(-6.0/256);
  filter(3, 0) = Image::Rgb(-4.0/256);
  filter(4, 0) = Image::Rgb(-1.0/256);

  filter(0, 1) = Image::Rgb(-4.0/256);
  filter(1, 1) = Image::Rgb(-16.0/256);
  filter(2, 1) = Image::Rgb(-24.0/256);
  filter(3, 1) = Image::Rgb(-16.0/256);
  filter(4, 1) = Image::Rgb(-4.0/256);
  
  filter(0, 2) = Image::Rgb(-6.0/256);
  filter(1, 2) = Image::Rgb(-24.0/256);
  filter(2, 2) = Image::Rgb(-476.0/256);
  filter(3, 2) = Image::Rgb(-26.0/256);
  filter(4, 2) = Image::Rgb(-7.0/256);
  
  filter(0, 3) = Image::Rgb(-4.0/256);
  filter(1, 3) = Image::Rgb(-16.0/256);
  filter(2, 3) = Image::Rgb(-24.0/256);
  filter(3, 3) = Image::Rgb(-16.0/256);
  filter(4, 3) = Image::Rgb(-4.0/256);
  
  filter(0, 4) = Image::Rgb(-1.0/256);
  filter(1, 4) = Image::Rgb(-4.0/256);
  filter(2, 4) = Image::Rgb(-4.0/256);
  filter(3, 4) = Image::Rgb(-4.0/256);
  filter(4, 4) = Image::Rgb(-1.0/256);

  return filter;
}

Image filters::getAllFilters(int rank) {
  int filterNum = filters::FILTERS[rank % filters::FILTERS.size()];

  Image filter = getFilter(filterNum, rank);

  return filter;
}
