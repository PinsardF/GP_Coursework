#include "Obstacle.h"

char obstacleDirection;
glm::vec3 obstaclePosition;
glm::vec3 obstacleVelocity;
glm::vec3 obstacleDimension;
Cube obstacleBody;
BoundaryBox obstacleBox;

Obstacle::Obstacle(glm::vec3 begin, char direction, glm::vec3 dim) {
	obstaclePosition = begin;
	obstacleDirection = direction;
	obstacleDimension = dim;
}

void Obstacle::init() {
	switch (obstacleDirection) {
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
	obstacleBox = BoundaryBox(obstaclePosition, obstaclePosition + dim, obstaclePosition - dim);
}

void Obstacle::render_obstacle(Graphics graphics) {
	glm::mat4 mv_obstacle = glm::translate(obstaclePosition) * 
		glm::scale(obstacleDimension) *
		glm::mat4(1.0f);
	obstacleBody.mv_matrix = graphics.viewMatrix * mv_obstacle;
	obstacleBody.proj_matrix = graphics.proj_matrix;
	obstacleBody.Draw();
}

void Obstacle::update_obstacle() {
	obstaclePosition += obstacleVelocity;
	obstacleBox.center = obstaclePosition;
	obstacleBox.min_position += obstacleVelocity;
	obstacleBox.max_position += obstacleVelocity;

	//CHANGE THIS WHEN WE HAVE A LIST OF OBSTACLES
	switch (obstacleDirection) {
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
