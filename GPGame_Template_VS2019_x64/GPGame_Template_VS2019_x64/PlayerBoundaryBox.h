#pragma once
#include "Obstacle.h"
#include <glm/glm.hpp>
class PlayerBoundaryBox{
public:
	glm::vec3 playerBoxCenter;
	glm::vec3 minPlayerBox;
	glm::vec3 maxPlayerBox;

	PlayerBoundaryBox();
	void react_collision(Obstacle obstacle);
};

