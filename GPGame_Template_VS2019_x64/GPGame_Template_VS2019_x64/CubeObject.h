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
//#include "ParticleEmitter.h"
#include "BoundaryBox.h"
#pragma once
class CubeObject{
public:
	glm::vec3 cubePosition;
	glm::vec3 cubeVelocity;
	glm::vec3 cubeAcceleration;
	int cubeWeight;
	Cube cubeBody;
	BoundaryBox cubeBox;

	CubeObject(glm::vec3 input_position, glm::vec3 input_velocity, glm::vec3 input_acceleration, int input_weight, Cube input_body);
	CubeObject();
	void init();
	void collide(BoundaryBox object);
	void react(glm::vec3 force);
	void update(Graphics graphics);
};

