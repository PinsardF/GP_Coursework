// Standard C++ libraries
/*#include <iostream>
#include <vector>*/
using namespace std;
//#include <string>

// Helper graphic libraries
//#include <GL/glew.h>

//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
//#include <glm/gtx/transform.hpp>
//#include "graphics.h"
//#include "shapes.h"
//#include <vector>
//#include "ParticleEmitter.h"
#pragma once
class BoundaryBox{
public:
	glm::vec3 center;
	glm::vec3 max_position;
	glm::vec3 min_position;

	BoundaryBox(glm::vec3 input_center, glm::vec3 input_max, glm::vec3 input_min);
	BoundaryBox();
	//bool detect_collision(BoundaryBox other_object);
};

