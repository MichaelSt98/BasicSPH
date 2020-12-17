#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "../include/matplotlibcpp.h"
#include "../include/Particle.h"
#include "../include/Settings.h"

namespace plt = matplotlibcpp;


static ParticleHandler particle_handler;

void Integrate(void)
{
	for (auto &p : particle_handler.particles)
	{
		// forward Euler integration
		p.v += DT * p.f / p.rho;
		p.x += DT * p.v;

		// enforce boundary conditions
		if (p.x(0) - EPS < 0.0f)
		{
			p.v(0) *= BOUND_DAMPING;
			p.x(0) = EPS;
		}
		if (p.x(0) + EPS > VIEW_WIDTH)
		{
			p.v(0) *= BOUND_DAMPING;
			p.x(0) = VIEW_WIDTH - EPS;
		}
		if (p.x(1) - EPS < 0.0f)
		{
			p.v(1) *= BOUND_DAMPING;
			p.x(1) = EPS;
		}
		if (p.x(1) + EPS > VIEW_HEIGHT)
		{
			p.v(1) *= BOUND_DAMPING;
			p.x(1) = VIEW_HEIGHT - EPS;
		}
	}
}

void ComputeDensityPressure(void)
{
	for (auto &pi : particle_handler.particles)
	{
		pi.rho = 0.f;
		for (auto &pj : particle_handler.particles)
		{
			Eigen::Vector2d rij = pj.x - pi.x;
			float r2 = rij.squaredNorm();

			if (r2 < HSQ)
			{
				// this computation is symmetric
				pi.rho += MASS * POLY6 * pow(HSQ - r2, 3.f);
			}
		}
		pi.p = GAS_CONST * (pi.rho - REST_DENS);
	}
}

void ComputeForces(void)
{
	for (auto &pi : particle_handler.particles)
	{
		Eigen::Vector2d fpress(0.f, 0.f);
		Eigen::Vector2d fvisc(0.f, 0.f);
		for (auto &pj : particle_handler.particles)
		{
			if (&pi == &pj)
				continue;

			Eigen::Vector2d rij = pj.x - pi.x;
			float r = rij.norm();

			if (r < H)
			{
				// compute pressure force contribution
				fpress += -rij.normalized() * MASS * (pi.p + pj.p) / (2.f * pj.rho) * SPIKY_GRAD * pow(H - r, 2.f);
				// compute viscosity force contribution
				fvisc += VISC * MASS * (pj.v - pi.v) / pj.rho * VISC_LAP * (H - r);
			}
		}
		Eigen::Vector2d fgrav = G * pi.rho;
		pi.f = fpress + fvisc + fgrav;
	}
}


void update() {
    //std::cout << "updating" << std::endl;
    //particle_handler.print_particles();
    ComputeDensityPressure();
    ComputeForces();
    Integrate();
}


int main(int argc, char **argv)
{

    //plt::figure(); //causes segmentation fault
    plt::backend("MacOSX"); //MacOSX, TKAgg, Qt4Agg, Qt4Agg //, cairo
    plt::ion();

    // Plot line from given x and y data. Color is selected automatically.
    std::vector<double> x_vec, y_vec;

	for (int i = 0; i < 1000; i++) {
	    std::cout << "i = " << i << std::endl;
	    update();
	    //if (i % 10 == 0) {
	    if (true) {
            x_vec.clear();
            y_vec.clear();
            for (auto &p : particle_handler.particles)
            {
                x_vec.push_back(p.x(0));
                y_vec.push_back(p.x(1));
            }
            plt::clf();
            plt::xlim(0, 1200);
            plt::ylim(0, 400);
            plt::scatter(x_vec, y_vec, 16);
            plt::show(false);
            plt::pause(0.001);
	    }
	}

    //plt::show(true); //block: false ?
    std::cout << "Hallo" << std::endl;
	//plt::close();
	//x_vec.clear();
	//y_vec.clear();
    //~x_vec();
    //~y_vec();

	return 0;

}
