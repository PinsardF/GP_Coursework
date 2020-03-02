#include "Obstacle.h"

char obstacleDirection;//Direction of the obstacle (North, South, East, West)
glm::vec3 obstaclePosition;//Position of the obstacle
glm::vec3 obstacleVelocity;//Velocity of the obstacle
glm::vec3 obstacleDimension;//Dimensions of the obstacle
Cube obstacleBody;//Visual body of the obstacle
BoundaryBox obstacleBox;//Hitbox of the obstacle

Obstacle::Obstacle(glm::vec3 begin, char direction, glm::vec3 dim) {
	obstaclePosition = begin;
	obstacleDirection = direction;
	obstacleDimension = dim;
}

void Obstacle::init() {
	switch (obstacleDirection) {//Depending on the direction of the obstacle we chose the right velocity
	case 'E':
		obstacleVelocity = glm::vec3(-0.05f,0.0f,0.0f);
		break;
	case 'W':
		obstacleVelocity = glm::vec3(0.05f, 0.0f, 0.0f);
		break;
	case 'N':
		obstacleVelocity = glm::vec3(0.0f, 0.0f, 0.05f);
		break;
	case 'S':
		obstacleVelocity = glm::vec3(0.0f, 0.0f, -0.05f);
		break;
	}
	obstacleBody.Load();
	glm::vec3 dim = obstacleDimension / glm::vec3(2.0f, 2.0f, 2.0f);
	obstacleBox = BoundaryBox(obstaclePosition, obstaclePosition + dim, obstaclePosition - dim);//Initialisation of the hitbox
}

void Obstacle::render_obstacle(Graphics graphics) {
	glm::mat4 mv_obstacle = glm::translate(obstaclePosition) * 
		glm::scale(obstacleDimension) *
		glm::mat4(1.0f);
	obstacleBody.mv_matrix = graphics.viewMatrix * mv_obstacle;
	obstacleBody.proj_matrix = graphics.proj_matrix;
	obstacleBody.Draw();//We draw the obstacle
}

void Obstacle::update_obstacle() {
	obstaclePosition += obstacleVelocity;//We move the obstacle and its hitbox
	obstacleBox.center = obstaclePosition;
	obstacleBox.min_position += obstacleVelocity;
	obstacleBox.max_position += obstacleVelocity;

	switch (obstacleDirection) {//When the obstacle gets out of the arena, its direction changes to 'X' and it's not considered anymore
	case 'E':
		if (obstaclePosition.x < -9.0f) {
			obstacleDirection = 'X';
		}
		break;
	case 'W':
		if (obstaclePosition.x > 9.0f) {
			obstacleDirection = 'X';
		}
		break;
	case 'N':
		if (obstaclePosition.z > 9.0f) {
			obstacleDirection = 'X';
		}
		break;
	case 'S':
		if (obstaclePosition.z <-9.0f) {
			obstacleDirection = 'X';
		}
		break;
	}
}
