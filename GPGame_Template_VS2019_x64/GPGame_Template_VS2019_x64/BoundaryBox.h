#include <glm/glm.hpp>
#pragma once
class BoundaryBox{
public:
	glm::vec3 center;
	glm::vec3 max_position;
	glm::vec3 min_position;

	BoundaryBox(glm::vec3 input_center, glm::vec3 input_max, glm::vec3 input_min);
	BoundaryBox();
};

