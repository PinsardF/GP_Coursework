#include "BoundaryBox.h"

glm::vec3 center;
glm::vec3 max_position;
glm::vec3 min_position;

BoundaryBox::BoundaryBox(glm::vec3 input_center, glm::vec3 input_max, glm::vec3 input_min) {
	center = input_center;
	max_position = input_max;
	min_position = input_min;
}
BoundaryBox::BoundaryBox() : center(glm::vec3(0.0f, 0.0f, 0.0f)), max_position(glm::vec3(1.0f, 1.0f, 1.0f)),
min_position(glm::vec3(-1.0f, -1.0f, -1.0f)) {}