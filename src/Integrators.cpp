//
// Created by Michael Staneker on 17.12.20.
//

#include "../include/Integrators.h"

IntegratorInterface::IntegratorInterface(float dt, float eps, double view_width, double view_height, float bound_damping)
                    :  dt {dt}, eps{ eps }, view_width{ view_width }, view_height{ view_height},
                        bound_damping{ bound_damping} {

    std::cout << "Class: IntegratorInterface constructor called..." << std::endl;

}


Integrator::Integrator(float dt, float eps, double view_width, double view_height, float bound_damping):
IntegratorInterface {dt, eps, view_width, view_height, bound_damping} {
    std::cout << "Class: Integrator constructor called..." << std::endl;
}

void Integrator::integrate(std::vector<Particle> &particles) {
    {
        for (auto &p : particles) {
            // forward Euler integration
            p.v += dt * p.f / p.rho;
            p.x += dt * p.v;

            // enforce boundary conditions
            if (p.x(0) - eps < 0.0f) {
                p.v(0) *= bound_damping;
                p.x(0) = eps;
            }
            if (p.x(0) + eps > view_width) {
                p.v(0) *= bound_damping;
                p.x(0) = view_width - eps;
            }
            if (p.x(1) - eps < 0.0f) {
                p.v(1) *= bound_damping;
                p.x(1) = eps;
            }
            if (p.x(1) + eps > view_height) {
                p.v(1) *= bound_damping;
                p.x(1) = view_height - eps;
            }
        }
    }
}