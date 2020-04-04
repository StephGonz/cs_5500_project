#include <cstdlib> 
#include <vector>

#include "Image.hpp"

#ifndef FILTER_HPP
#define FILTER_HPP
 
namespace filters {
    Image getFilter(int filterNum, int rank);
    Image getScharrFilter();
    Image getSobelFilter();
    Image getGaussianFilter();
    Image getRainbowFilter(int rank);
    Image getSharpenFilter();
    Image getAllFilters(int rank);
    const std::vector<int> FILTERS{1, 2, 3, 4, 5};
}

#endif
