#pragma once
#include "Obstacle.h"
#include <glm/glm.hpp>
class PlayerBoundaryBox{
public:
	glm::vec3 playerBoxCenter;//Center of the hitbox
	glm::vec3 minPlayerBox;
	glm::vec3 maxPlayerBox;

	PlayerBoundaryBox();//Constructor
};

