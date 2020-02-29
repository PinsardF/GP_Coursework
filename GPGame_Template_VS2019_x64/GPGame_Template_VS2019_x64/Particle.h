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
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
//#include <vector>
#pragma once
class Particle{
public:
	int timetolive;
	glm::vec3 p_position;
	glm::vec3 velocity;
	//glm::vec3 acceleration;
	bool isalive;
	Line visualParticle;

	Particle();

	Particle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive);
	void init();

	void update(Graphics graphics);
};

