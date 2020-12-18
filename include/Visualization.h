//
// Created by Michael Staneker on 18.12.20.
//

#ifndef BASICSPH_VISUALIZATION_H
#define BASICSPH_VISUALIZATION_H

#include "matplotlibcpp.h"
#include <string>
#include <vector>

namespace plt = matplotlibcpp;


class Visualization {

private:
    int s = 1;
    int x_lim[2] = {0, 0};
    int y_lim[2] = {0, 0};


public:
    Visualization(std::string backend, int s, int lower_x_lim, int upper_x_lim,
                  int lower_y_lim, int upper_y_lim);

    void update(std::vector<double> &x_vec, std::vector<double> &y_vec, float pause=0.001);


};


#endif //BASICSPH_VISUALIZATION_H
