#include "ParticleEmitter.h"

glm::vec3 emitterPosition;
int reloadtime;
std::vector<Particle> particlesList;

ParticleEmitter::ParticleEmitter(glm::vec3 input_vector, int input_reloadtime) {
	emitterPosition.x = input_vector.x;
	emitterPosition.y = input_vector.y;
	emitterPosition.z = input_vector.z;
	reloadtime = input_reloadtime;
}

ParticleEmitter::ParticleEmitter() : emitterPosition(glm::vec3(-1.0f, 0.0f, -1.0f)), reloadtime(75) {};

void ParticleEmitter::initparticle() {
	Particle newParticle = Particle(150 + rand() % 150, glm::vec3(-1.0f, 0.0f, -1.0f),glm::vec3(0.0f,0.0f,0.0f),true);
	newParticle.init();
	particlesList.push_back(newParticle);
}

void ParticleEmitter::update(Graphics graphics) {
	for (int i = 0; i < particlesList.size(); i++) {//considering each particle...
		if (particlesList[i].timetolive <= 0.0f) {//if its lifetime is over, the particle dies
			particlesList[i].isalive = false;
		}
		if (!particlesList[i].isalive) {//if it's dead we delete it in the list
			particlesList.erase(particlesList.begin()+i);
		}
		else {//if it's still alive we update its position
			particlesList[i].update(graphics);
		}
	}

	if (reloadtime <= 0 && particlesList.size() < 10) {//if the number of particle is below the chosen one...
		initparticle();//we create a particle
		reloadtime = rand() % 50;//we reset the reloadTime
	}
	else {//else we just decrease the reloadTime
		reloadtime--;
	}
}
