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
//#include <vector>
#include "shapes.h"
#pragma once
class ExplosionParticle{
public:
	int explosionTimetolive;
	glm::vec3 explosionPosition;
	glm::vec3 explosionVelocity;
	//glm::vec3 acceleration;
	bool explosionIsalive;
	Line explosionVisualParticle;

	ExplosionParticle();

	ExplosionParticle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive);//
	void init();

	void update(Graphics graphics);
};

