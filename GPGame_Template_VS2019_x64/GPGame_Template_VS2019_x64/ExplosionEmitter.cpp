#include "ExplosionEmitter.h"

glm::vec3 explosionEmitterPosition;
std::vector<ExplosionParticle> explosionParticlesList;
int timetoexplode;//

ExplosionEmitter::ExplosionEmitter(glm::vec3 input_vector) {
	explosionEmitterPosition.x = input_vector.x;
	explosionEmitterPosition.y = input_vector.y;
	explosionEmitterPosition.z = input_vector.z;
	timetoexplode = 30;//
}

ExplosionEmitter::ExplosionEmitter(): explosionEmitterPosition(glm::vec3(0.0f,0.0f,0.0f)), timetoexplode(30){}

void ExplosionEmitter::initExplosion() {
	for (int i = 0; i < 80; i++) {
		ExplosionParticle newParticle = ExplosionParticle(20 + rand() % 6,explosionEmitterPosition,glm::vec3(0.0f,0.0f,0.0f),true);
		newParticle.init();
		explosionParticlesList.push_back(newParticle);
	}
}

void ExplosionEmitter::update(Graphics graphics) {
	for (int i = 0; i < explosionParticlesList.size(); i++) {
		if (explosionParticlesList[i].explosionTimetolive <= 0.0f) {
			explosionParticlesList[i].explosionIsalive = false;
		}
		if (!explosionParticlesList[i].explosionIsalive) {
			explosionParticlesList.erase(explosionParticlesList.begin() + i);
		}
		else {
			explosionParticlesList[i].update(graphics);
		}
	}

	/*if (explosionParticlesList.size() == 0) {
		if (timetoexplode <= 0) {
			initExplosion();
			timetoexplode = 30;
		}
		else {
			timetoexplode--;
		}
	}*/
}


