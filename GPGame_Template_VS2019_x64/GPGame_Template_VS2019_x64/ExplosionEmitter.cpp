// Standard C++ libraries
#include <iostream>
#include <vector>
using namespace std;
#include <string>

// Helper graphic libraries
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#include <vector>
#include "ExplosionEmitter.h"
#include "ExplosionParticle.h"

glm::vec3 explosionEmitterPosition;
int explosionReloadtime;
std::vector<ExplosionParticle> ExplosionParticlesList;

ExplosionEmitter::ExplosionEmitter(glm::vec3 input_vector, int input_reloadtime) {
	explosionEmitterPosition.x = input_vector.x;
	explosionEmitterPosition.y = input_vector.y;
	explosionEmitterPosition.z = input_vector.z;
	explosionReloadtime = input_reloadtime;
}

ExplosionEmitter::ExplosionEmitter() : explosionEmitterPosition(glm::vec3(-1.0f, 0.0f, -1.0f)), explosionReloadtime(75) {};

void ExplosionEmitter::initExplosion() {
	for (int i = 0; i < 80; i++) {
		ExplosionParticle newParticle = ExplosionParticle(20 + rand() % 7,explosionEmitterPosition,glm::vec3(0.0f,0.0f,0.0f),true);
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

	if (explosionParticlesList.size() == 0) {
		if (explosionReloadtime <= 0) {
			initExplosion();
			explosionReloadtime = 30;
		}
		else {
			explosionReloadtime--;
		}
	}
}


