#include "Particle.h"
#pragma once
class ParticleEmitter{
public:
	glm::vec3 vector;
	int reloadtime;
	Particle emittedparticle;
	//Particle particlesList[6];

	ParticleEmitter(glm::vec3 input_vector, int input_reloadtime);
	ParticleEmitter();
	void initparticle();
	void update();
};

