#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "../include/Particle.h"
#include "../include/Settings.h"


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

void Update(void)
{
	ComputeDensityPressure();
	ComputeForces();
	Integrate();

	glutPostRedisplay();
}

void InitGL(void)
{
	glClearColor(0.9f, 0.9f, 0.9f, 1);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(H / 2.f);
	glMatrixMode(GL_PROJECTION);
}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(0, VIEW_WIDTH, 0, VIEW_HEIGHT, 0, 1);

	glColor4f(0.2f, 0.6f, 1.0f, 1);
	glBegin(GL_POINTS);
	for (auto &p : particle_handler.particles)
		glVertex2f(p.x(0), p.x(1));
	glEnd();

	glutSwapBuffers();
}

void Keyboard(unsigned char c, __attribute__((unused)) int x, __attribute__((unused)) int y)
{
	switch (c)
	{
	case ' ':
		if (particle_handler.particles.size() >= MAX_PARTICLES)
			std::cout << "maximum number of particles reached" << std::endl;
		else
		{
			unsigned int placed = 0;
			for (float y = VIEW_HEIGHT / 1.5f - VIEW_HEIGHT / 5.f; y < VIEW_HEIGHT / 1.5f + VIEW_HEIGHT / 5.f; y += H * 0.95f)
				for (float x = VIEW_WIDTH / 2.f - VIEW_HEIGHT / 5.f; x <= VIEW_WIDTH / 2.f + VIEW_HEIGHT / 5.f; x += H * 0.95f)
					if (placed++ < BLOCK_PARTICLES && particle_handler.particles.size() < MAX_PARTICLES)
						particle_handler.particles.push_back(Particle(x, y));
		}
		break;
	case 'r':
	case 'R':
		particle_handler.particles.clear();
		particle_handler.init_distribution();
		break;
	}
}

int main(int argc, char **argv)
{



	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInit(&argc, argv);
	glutCreateWindow("Müller SPH");
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutKeyboardFunc(Keyboard);

	InitGL();

	glutMainLoop();
	return 0;

}
