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
#include "ParticleEmitter.h"
#include "Particle.h"

glm::vec3 vector;
int reloadtime;
Particle emittedparticle;
//Particle particlesList[6];

ParticleEmitter::ParticleEmitter(glm::vec3 input_vector, int input_reloadtime) {
	vector.x = input_vector.x;
	vector.y = input_vector.y;
	vector.z = input_vector.z;
	reloadtime = input_reloadtime;
}

ParticleEmitter::ParticleEmitter() : vector(glm::vec3(-1.0f, 0.0f, -1.0f)), reloadtime(40) {};

void ParticleEmitter::initparticle() {
	//if (listSize < 6) {
	//	//emittedparticle = Particle(150 + rand() % 150, -1.0f, 0.0f, -1.0f, true);
	//	Particle newParticle = Particle(150 + rand() % 150, -1.0f, 0.0f, -1.0f, true);
	//	//emittedparticle.init();
	//	newParticle.init();
	//	particlesList[listSize] = newParticle;
	//}
	Particle newParticle = Particle(150 + rand() % 150, glm::vec3(-1.0f, 0.0f, -1.0f), true);
	newParticle.init();
	emittedparticle = newParticle;
}

void ParticleEmitter::update() {
	if (!emittedparticle.isalive) {
		if (reloadtime <= 0) {
			initparticle();
			reloadtime = rand() % 50;
		}
		else {
			reloadtime--;
		}
	}
}
