//
// Created by Michael Staneker on 18.12.20.
//

#include "../include/EOS.h"

void EOS::compute_density_pressure(std::vector<Particle> &particles) {
    for (auto &pi : particles)
    {
        pi.rho = 0.f;
        for (auto &pj : particles)
        {
            Eigen::Vector2d rij = pj.x - pi.x;
            float r2 = rij.squaredNorm();

            if (r2 < settings::HSQ)
            {
                // this computation is symmetric
                pi.rho += settings::MASS * settings::POLY6 * pow(settings::HSQ - r2, 3.f);
            }
        }
        pi.p = settings::GAS_CONST * (pi.rho - settings::REST_DENS);
    }
}
