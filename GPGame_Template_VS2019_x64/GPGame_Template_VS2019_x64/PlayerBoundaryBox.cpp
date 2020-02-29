#include "PlayerBoundaryBox.h"

glm::vec3 playerBoxCenter;
glm::vec3 minPlayerBox;
glm::vec3 maxPlayerBox;

PlayerBoundaryBox::PlayerBoundaryBox() {
	playerBoxCenter = glm::vec3(0.0f,0.5f,0.0f);
	minPlayerBox = glm::vec3(-0.5f, 0.0f, -0.5f) + playerBoxCenter;
	maxPlayerBox = glm::vec3(0.5f,1.0f,0.5f) + playerBoxCenter;
}

void PlayerBoundaryBox::react_collision(Obstacle obstacle) {
	/*switch (obstacle.obstacleDirection) {
	case 'E':

	}*/
}
