//
// Created by Michael Staneker on 11.12.20.
//

#ifndef BASICSPH_PARTICLE_H
#define BASICSPH_PARTICLE_H

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

class Particle {
public:
    Particle(float _x, float _y);
    Eigen::Vector2d x, v, f;
    float rho, p;

    void set_x(float _x, float _y);
};

class ParticleHandler {
public:
    std::vector<Particle> particles;
    int number_of_particles;

    ParticleHandler();
    ParticleHandler(int n_particle);
    ~ParticleHandler();

    void init_distribution();
    void print_particles();
};


#endif //BASICSPH_PARTICLE_H
