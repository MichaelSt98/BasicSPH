//
// Created by Michael Staneker on 18.12.20.
//

#ifndef BASICSPH_EOS_H
#define BASICSPH_EOS_H

#include "Settings.h"
#include "Particle.h"


class EOS {

private:

public:
    void compute_density_pressure(std::vector<Particle> &particles);

};


#endif //BASICSPH_EOS_H
