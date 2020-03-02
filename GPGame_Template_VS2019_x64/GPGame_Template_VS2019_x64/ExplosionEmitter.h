#include "graphics.h"
#include "ExplosionParticle.h"
#pragma once
class ExplosionEmitter{
public:
	glm::vec3 explosionEmitterPosition;
	std::vector<ExplosionParticle> explosionParticlesList;

	ExplosionEmitter(glm::vec3 input_vector);//Constructor
	ExplosionEmitter();//Constructor
	void initExplosion();//Initialisation of the particles
	void update(Graphics graphics);//Updating the emitter at each frame
};

