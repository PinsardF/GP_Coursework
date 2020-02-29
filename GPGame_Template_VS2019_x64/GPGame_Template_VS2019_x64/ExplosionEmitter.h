// Standard C++ libraries
//#include <iostream>
//#include <vector>
//using namespace std;
//#include <string>

// Helper graphic libraries
//#include <GL/glew.h>

//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/transform.hpp>
#include "graphics.h"
//#include "shapes.h"
//#include <vector>
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

