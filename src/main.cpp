#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <string>

#include "../include/matplotlibcpp.h"
#include "../include/Particle.h"
#include "../include/Settings.h"
#include "../include/Integrators.h"
#include "../include/EOS.h"
#include "../include/Forces.h"
#include "../include/Timer.h"
#include "../include/Visualization.h"

namespace plt = matplotlibcpp;

static ParticleHandler particle_handler;
static Integrator integrator{settings::DT, settings::EPS, settings::VIEW_WIDTH,
                             settings::VIEW_HEIGHT, settings::BOUND_DAMPING};

static EOS eos{};
static Forces forces{};

static std::vector<double> time_density_pressure;
static Timer t_density_pressure;
static std::vector<double> time_forces;
static Timer t_forces;
static std::vector<double> time_integration;
static Timer t_integration;

void update() {
    //std::cout << "updating..." << std::endl;

    // density pressure
    t_density_pressure.reset();
    eos.compute_density_pressure(particle_handler.particles);
    time_density_pressure.push_back(t_density_pressure.elapsed());

    // forces
    t_forces.reset();
    forces.compute_forces(particle_handler.particles);
    time_forces.push_back(t_forces.elapsed());

    // integration
    t_integration.reset();
    integrator.integrate(particle_handler.particles);
    time_integration.push_back(t_integration.elapsed());
}

void progress_bar(float progress, int bar_width = 70) {
    std::cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}


int main(int argc, char **argv)
{
    bool visualize = false;
    int no_of_loops = 200;

    std::cout << std::endl << "STARTING BasicSPH... " << std::endl << std::endl;
    Timer t;


    Visualization visualization{"MacOSX", 16, 0, 1200, 0, 180};


    // Plot line from given x and y data. Color is selected automatically.
    std::vector<double> x_vec, y_vec;

    std::cout << std::endl;

    int bar_width = 70;
    std::cout << std::endl << "Progress:" << std::endl;
	for (int i = 0; i <= no_of_loops; i++) {

        float progress = i/(float)no_of_loops;
        progress_bar(progress, bar_width);

	    update();

	    // visualization
	    if (visualize && i % 2 == 0) {
            x_vec.clear();
            y_vec.clear();
            for (auto &p : particle_handler.particles)
            {
                x_vec.push_back(p.x(0));
                y_vec.push_back(p.x(1));
            }
            visualization.update(x_vec, y_vec);

	    }
	}

    std::cout << std::endl << std::endl << "Elapsed time: " << t.elapsed() << " seconds." << std::endl;

	//evaluation of computational time
	std::cout << std::endl;
	std::cout << "Elapsed time for Density & Pressure: " << std::endl;
	std::cout << "\tTotal:    "
	          << std::accumulate(time_density_pressure.begin(), time_density_pressure.end(), 0.0)
	          << " s" << std::endl;
    std::cout << "\tAveraged: "
              << std::accumulate(time_density_pressure.begin(), time_density_pressure.end(), 0.0) / time_density_pressure.size()
              << " s" << std::endl;
    std::cout << "Elapsed time for Forces: " << std::endl;
    std::cout << "\tTotal:    "
              << std::accumulate(time_forces.begin(), time_forces.end(), 0.0)
              << " s" << std::endl;
    std::cout << "\tAveraged: "
              << std::accumulate(time_forces.begin(), time_forces.end(), 0.0) / time_forces.size()
              << " s" << std::endl;
    std::cout << "Elapsed time for Integration: " << std::endl;
    std::cout << "\tTotal:    "
              << std::accumulate(time_integration.begin(), time_integration.end(), 0.0)
              << " s" << std::endl;
    std::cout << "\tAveraged: "
              << std::accumulate(time_integration.begin(), time_integration.end(), 0.0) / time_integration.size()
              << " s" << std::endl;

	return 0;
}
