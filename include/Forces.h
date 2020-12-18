//
// Created by Michael Staneker on 18.12.20.
//

#ifndef BASICSPH_FORCES_H
#define BASICSPH_FORCES_H

#include "Settings.h"
#include "Particle.h"

class Forces {

private:

public:
    void compute_forces(std::vector<Particle> &particles);
};


#endif //BASICSPH_FORCES_H
