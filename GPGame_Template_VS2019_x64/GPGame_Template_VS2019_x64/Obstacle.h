#pragma once
#include "shapes.h"
#include "BoundaryBox.h"
#include <glm\gtx\transform.hpp>
#include "graphics.h"

class Obstacle{
public: 
	glm::vec3 obstacleEndPosition;
	char obstacleDirection;
	glm::vec3 obstaclePosition;
	glm::vec3 obstacleVelocity;
	glm::vec3 obstacleDimension;
	Cube cubeBody;
	BoundaryBox obstacleBox;

	Obstacle(glm::vec3 begin, glm::vec3 end, char direction, glm::vec3 dim);
	void init(); 
	void render_obstacle(Graphics graphics);
	void update_obstacle();
};

