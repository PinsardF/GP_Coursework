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
#include "Particle.h"
#pragma once
class ParticleEmitter{
public:
	glm::vec3 emitterPosition;
	int reloadtime;
	std::vector<Particle> particlesList;

	ParticleEmitter(glm::vec3 input_vector, int input_reloadtime);
	ParticleEmitter();
	void initparticle();
	void update(Graphics graphics);
};

