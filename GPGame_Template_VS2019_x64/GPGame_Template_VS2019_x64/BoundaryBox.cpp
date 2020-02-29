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

/*bool BoundaryBox::detect_collision(BoundaryBox other_object) {
	if (max_position.x >= other_object.min_position.x && min_position.x <= other_object.max_position.x &&
		max_position.y >= other_object.min_position.y && min_position.y <= other_object.max_position.y &&
		max_position.z >= other_object.min_position.z && min_position.z <= other_object.max_position.z) {
		return true;
	}
	//if (min_position.x < other_object.max_position.x) {
	//	return true;
	//}
	return false;
}*/

/*glm::vec3 BoundaryBox::center_of_collision(BoundaryBox other_object) {
	glm::vec3 collisionCenter = glm::vec3(0.0f, 0.0f, 0.0f);
	if (abs(max_position.x - other_object.min_position.x) <= abs(min_position.x - other_object.max_position.x)) {
		collisionCenter.x = (max_position.x + other_object.min_position.x) / 2;
	}
	else {
		collisionCenter.x = (min_position.x + other_object.max_position.x) / 2;
	}
	if (abs(max_position.y - other_object.min_position.y) <= abs(min_position.y - other_object.max_position.y)) {
		collisionCenter.y = (max_position.y + other_object.min_position.y) / 2;
	}
	else {
		collisionCenter.y = (min_position.y + other_object.max_position.y) / 2;
	}
	if (abs(max_position.z - other_object.min_position.z) <= abs(min_position.z - other_object.max_position.z)) {
		collisionCenter.z = (max_position.z + other_object.min_position.z) / 2;
	}
	else {
		collisionCenter.z = (min_position.z + other_object.max_position.z) / 2;
	}
	return collisionCenter;
}*/