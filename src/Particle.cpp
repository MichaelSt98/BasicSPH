//
// Created by Michael Staneker on 11.12.20.
//

#include "../include/Particle.h"

Particle::Particle(float _x, float _y)  : x(_x, _y), v(0.f, 0.f), f(0.f, 0.f), rho(0), p(0.f)
{
    //std::cout << "Particle constructor called!" << std::endl;
}

void Particle::set_x(float _x, float _y) {
    x(_x, _y);
}



ParticleHandler::ParticleHandler() {
    init_distribution();
}

ParticleHandler::ParticleHandler(int n_particles) {
    number_of_particles = n_particles;
    init_distribution();
}

ParticleHandler::~ParticleHandler(){
    particles.clear();
}

void ParticleHandler::init_distribution()
{
    std::cout << "initializing dam break with " << settings::DAM_PARTICLES << " particles" << std::endl;
    for (float y = settings::EPS; y < settings::VIEW_HEIGHT - settings::EPS * 2.f; y += settings::H)
        for (float x = settings::VIEW_WIDTH / 4; x <= settings::VIEW_WIDTH / 2; x += settings::H)
            if (particles.size() < settings::DAM_PARTICLES)
            {
                float jitter = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                particles.push_back(Particle(x + jitter, y));
            }
}

void ParticleHandler::print_particles() {
    for (auto &p : particles)
    {
        std::cout << "x = " << p.x(0) << "  y = " << p.x(1) << std::endl;
    }
}