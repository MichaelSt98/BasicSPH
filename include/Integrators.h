//
// Created by Michael Staneker on 17.12.20.
//

#ifndef BASICSPH_INTEGRATORS_H
#define BASICSPH_INTEGRATORS_H

#include "Particle.h"


class IntegratorInterface {

private:

protected:
    float dt = 0;
    float eps = 0;
    double view_width = 0;
    double view_height = 0;
    float bound_damping = 0;

public:

    IntegratorInterface(float dt, float eps, double view_width, double view_height, float bound_damping);

    void integrate(std::vector<Particle> &particles) {};
};


class Integrator: public IntegratorInterface {

private:

public:

    Integrator(float dt, float eps, double view_width, double view_height, float bound_damping);

    void integrate(std::vector<Particle> &particles);
};


#endif //BASICSPH_INTEGRATORS_H
