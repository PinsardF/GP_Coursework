#include "graphics.h"
#include "ExplosionParticle.h"
#pragma once
class ExplosionEmitter{
public:
	glm::vec3 explosionEmitterPosition;
	std::vector<ExplosionParticle> explosionParticlesList;
	int timetoexplode;//

	ExplosionEmitter(glm::vec3 input_vector);
	ExplosionEmitter();
	void initExplosion();
	void update(Graphics graphics);
};

