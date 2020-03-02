#pragma once
#include "shapes.h"
#include "BoundaryBox.h"
#include <glm\gtx\transform.hpp>
#include "graphics.h"

class Obstacle{
public: 
	char obstacleDirection;//Direction of the obstacle (North, South, East, West)
	glm::vec3 obstaclePosition;//Position of the obstacle
	glm::vec3 obstacleVelocity;//Velocity of the obstacle
	glm::vec3 obstacleDimension;//Dimensions of the obstacle
	Cube obstacleBody;//Visual body of the obstacle
	BoundaryBox obstacleBox;//Hitbox of the obstacle

	Obstacle(glm::vec3 begin, char direction, glm::vec3 dim);//Constructor
	void init(); //Initialisation of the obstacle
	void render_obstacle(Graphics graphics);//Rendering of the obstacle
	void update_obstacle();//Updating the obstacle at each frame
};

