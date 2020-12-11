//
// Created by Michael Staneker on 11.12.20.
//

#ifndef BASICSPH_SETTINGS_H
#define BASICSPH_SETTINGS_H

#include <vector>
#include <eigen3/Eigen/Dense>

// "Particle-Based Fluid Simulation for Interactive Applications"
// solver parameters
const static Eigen::Vector2d G(0.f, 12000 * -9.8f); // external (gravitational) forces
const static float REST_DENS = 1000.f;		 // rest density
const static float GAS_CONST = 2000.f;		 // const for equation of state
const static float H = 16.f;				 // kernel radius
const static float HSQ = H * H;				 // radius^2 for optimization
const static float MASS = 65.f;				 // assume all particles have the same mass
const static float VISC = 250.f;			 // viscosity constant
const static float DT = 0.0008f;			 // integration timestep

// smoothing kernels defined in Müller and their gradients
const static float POLY6 = 315.f / (65.f * M_PI * pow(H, 9.f));
const static float SPIKY_GRAD = -45.f / (M_PI * pow(H, 6.f));
const static float VISC_LAP = 45.f / (M_PI * pow(H, 6.f));

// simulation parameters
const static float EPS = H; // boundary epsilon
const static float BOUND_DAMPING = -0.5f;


// interaction
const static int MAX_PARTICLES = 2500;
const static int DAM_PARTICLES = 500;
const static int BLOCK_PARTICLES = 250;

// rendering projection parameters
const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 600;
const static double VIEW_WIDTH = 1.5 * 800.f;
const static double VIEW_HEIGHT = 1.5 * 600.f;

#endif //BASICSPH_SETTINGS_H
