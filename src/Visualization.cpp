//
// Created by Michael Staneker on 18.12.20.
//

#include "../include/Visualization.h"

Visualization::Visualization(std::string backend, int s, int lower_x_lim, int upper_x_lim,
                             int lower_y_lim, int upper_y_lim)
        : s{ s }, x_lim{ lower_x_lim, upper_x_lim }, y_lim{ lower_y_lim, upper_y_lim } {

    if (backend != "") {
        plt::backend(backend);
    }

    plt::ion();

}

void Visualization::update(std::vector<double> &x_vec, std::vector<double> &y_vec, float pause) {
    //plt::figure(); //causes segmentation fault
    plt::clf();
    plt::xlim(x_lim[0], x_lim[1]);
    plt::ylim(y_lim[0], y_lim[1]);
    plt::scatter(x_vec, y_vec, s);
    plt::show(false);
    plt::pause(pause);
}