//
// Created by Michael Staneker on 18.12.20.
//

#include "../include/Forces.h"

void Forces::compute_forces(std::vector<Particle> &particles)
{
    for (auto &pi : particles)
    {
        Eigen::Vector2d fpress(0.f, 0.f);
        Eigen::Vector2d fvisc(0.f, 0.f);
        for (auto &pj : particles)
        {
            if (&pi == &pj)
                continue;

            Eigen::Vector2d rij = pj.x - pi.x;
            float r = rij.norm();

            if (r < settings::H)
            {
                // compute pressure force contribution
                fpress += -rij.normalized() * settings::MASS * (pi.p + pj.p) / (2.f * pj.rho) *
                          settings::SPIKY_GRAD * pow(settings::H - r, 2.f);
                // compute viscosity force contribution
                fvisc += settings::VISC * settings::MASS * (pj.v - pi.v) / pj.rho * settings::VISC_LAP *
                         (settings::H - r);
            }
        }
        Eigen::Vector2d fgrav = settings::G * pi.rho;
        pi.f = fpress + fvisc + fgrav;
    }
}

