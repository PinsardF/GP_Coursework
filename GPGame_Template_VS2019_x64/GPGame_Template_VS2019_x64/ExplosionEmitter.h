#include "ExplosionParticle.h"
#pragma once
class ExplosionEmitter{
public:
	glm::vec3 explosionEmitterPosition;
	int explosionReloadtime;
	std::vector<ExplosionParticle> explosionParticlesList;

	ExplosionEmitter(glm::vec3 input_vector, int input_reloadtime);
	ExplosionEmitter();
	void initExplosion();
	void update(Graphics graphics);
};

