#include "Particle.h"
#pragma once
class ParticleEmitter{
public:
	glm::vec3 emitterPosition;
	int reloadtime;
	std::vector<Particle> particlesList;

	ParticleEmitter(glm::vec3 input_vector, int input_reloadtime);
	ParticleEmitter();
	void initparticle();
	void update(Graphics graphics);
};

