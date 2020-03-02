#include "ExplosionEmitter.h"

glm::vec3 explosionEmitterPosition;
std::vector<ExplosionParticle> explosionParticlesList;

ExplosionEmitter::ExplosionEmitter(glm::vec3 input_vector) {
	explosionEmitterPosition = input_vector;
}

ExplosionEmitter::ExplosionEmitter(): explosionEmitterPosition(glm::vec3(0.0f,0.0f,0.0f)){}

void ExplosionEmitter::initExplosion() {
	for (int i = 0; i < 80; i++) {//Creation of 80 particles with random lifetime
		ExplosionParticle newParticle = ExplosionParticle(20 + rand() % 6,explosionEmitterPosition,glm::vec3(0.0f,0.0f,0.0f),true);
		newParticle.init();
		explosionParticlesList.push_back(newParticle);
	}
}

void ExplosionEmitter::update(Graphics graphics) {
	for (int i = 0; i < explosionParticlesList.size(); i++) {//For each particle...
		if (explosionParticlesList[i].explosionTimetolive <= 0.0f) {//if the timetolive comes to an end, the particle dies
			explosionParticlesList[i].explosionIsalive = false;
		}
		if (!explosionParticlesList[i].explosionIsalive) {//if the particle is dead...
			explosionParticlesList.erase(explosionParticlesList.begin() + i);//we erase it
		}
		else {
			explosionParticlesList[i].update(graphics);//else we update it
		}
	}
}


