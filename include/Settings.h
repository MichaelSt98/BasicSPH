//
// Created by Michael Staneker on 11.12.20.
//

#ifndef BASICSPH_SETTINGS_H
#define BASICSPH_SETTINGS_H

#include <vector>
#include <eigen3/Eigen/Dense>

namespace settings {

    // everything was const static ...

    // "Particle-Based Fluid Simulation for Interactive Applications"
    // solver parameters
    static Eigen::Vector2d G(0.f, 12000 * -9.8f); // external (gravitational) forces
    static float REST_DENS = 1000.f;         // rest density
    static float GAS_CONST = 2000.f;         // const for equation of state
    static float H = 16.f;                 // kernel radius
    static float HSQ = H * H;                 // radius^2 for optimization
    static float MASS = 65.f;                 // assume all particles have the same mass
    static float VISC = 250.f;             // viscosity constant
    static float DT = 0.0008f;             // integration timestep

    // smoothing kernels defined in Müller and their gradients
    static float POLY6 = 315.f / (65.f * M_PI * pow(H, 9.f));
    static float SPIKY_GRAD = -45.f / (M_PI * pow(H, 6.f));
    static float VISC_LAP = 45.f / (M_PI * pow(H, 6.f));

    // simulation parameters
    static float EPS = H; // boundary epsilon
    static float BOUND_DAMPING = -0.5f;

    // interaction
    static int MAX_PARTICLES = 2500;
    static int DAM_PARTICLES = 120;
    static int BLOCK_PARTICLES = 250;

    // rendering projection parameters
    static int WINDOW_WIDTH = 800;
    static int WINDOW_HEIGHT = 600;
    static double VIEW_WIDTH = 1.5 * 800.f;
    static double VIEW_HEIGHT = 1.5 * 600.f;

}

#endif //BASICSPH_SETTINGS_H
