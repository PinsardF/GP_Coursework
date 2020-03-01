#include "Player.h"

Cube		character;
PlayerBoundaryBox hitbox;
glm::vec3	pos_player;
glm::vec3	cel_player;
std::vector<char> pushedList;

Player::Player() {
	pos_player = glm::vec3(0.0f,0.5f,0.0f);
	cel_player = glm::vec3(0.0f,0.0f,0.0f);
}

/*Player::~Player()
{
	delete this;
}*/

void Player::init() {
	character.Load();
	character.fillColor = glm::vec4(0.0f, 0.0f, 255.0f, 1.0f); // Blue color
	pushedList.clear();
}

void Player::update_player() {
	int x_forces = 0;
	int z_forces = 0;
	bool x_pushed = false;
	bool z_pushed = false;

	for (int i = 0; i < pushedList.size(); i++) {
		switch (pushedList[i]) {
		case 'U':
			x_pushed = true;
			x_forces -= 1;
			break;
		case 'D':
			x_pushed = true;
			x_forces += 1;
			break;
		case 'L':
			z_pushed = true;
			z_forces -= 1;
			break;
		case 'R':
			z_pushed = true;
			z_forces += 1;
			break;
		}
	}
	int dead = false;
	if ((x_pushed && x_forces == 0) || (z_pushed && z_forces == 0)) {
		dead = true;
	}

	if (!dead) {
		pos_player += cel_player;
		hitbox.playerBoxCenter = pos_player;
		hitbox.minPlayerBox += cel_player;
		hitbox.maxPlayerBox += cel_player;
		cel_player = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else {
		pos_player = glm::vec3(-4.0f, 0.5f, -4.0f);
		hitbox.playerBoxCenter = pos_player;
		hitbox.minPlayerBox = pos_player - glm::vec3(0.5f,0.5f,0.5f);
		hitbox.maxPlayerBox = pos_player + glm::vec3(0.5f, 0.5f, 0.5f);
		cel_player = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	pushedList.clear();
}

void Player::render_character(Graphics graphics) {
	glm::mat4 mv_player =
		glm::translate(pos_player) *
		glm::mat4(1.0f);
	character.mv_matrix = graphics.viewMatrix * mv_player;
	character.proj_matrix = graphics.proj_matrix;
	character.Draw();
	character.fillColor = glm::vec4(0.0f, 0.0f, 255.0f, 1.0f);;
}

bool Player::detect_collision_obstacles(Obstacle obstacle) {
	if (hitbox.maxPlayerBox.x >= obstacle.obstacleBox.min_position.x && hitbox.minPlayerBox.x <= obstacle.obstacleBox.max_position.x &&
		hitbox.maxPlayerBox.y >= obstacle.obstacleBox.min_position.y && hitbox.minPlayerBox.y <= obstacle.obstacleBox.max_position.y &&
		hitbox.maxPlayerBox.z >= obstacle.obstacleBox.min_position.z && hitbox.minPlayerBox.z <= obstacle.obstacleBox.max_position.z) {
		return true;
	}
	return false;
}

void Player::detect_collision_walls() {
	if (hitbox.maxPlayerBox.z > 8.5f) {
		cel_player.z = -0.02f;
		pushedList.push_back('U');//pushed by the UP
	}
	if (hitbox.minPlayerBox.z < -8.5f) {
		cel_player.z = 0.02f;
		pushedList.push_back('D');//pushed by the DOWN
	}
	if (hitbox.minPlayerBox.x < -8.5f) {
		cel_player.x = 0.02f;
		pushedList.push_back('R');//pushed by the RIGHT
	}
	if (hitbox.maxPlayerBox.x > 8.5f) {
		cel_player.x = -0.02f;
		pushedList.push_back('L');//pushed by the LEFT
	}
}

glm::vec3 Player::center_collision(Obstacle obstacle) {
	glm::vec3 collisionCenter;
	//if obst_min < player_min < player_max < obst_max :
	//	collision = (player_min + player_max) / 2
	//elif obst_min < player_min < player_max < obst_max :
	//	collision = (player_max + obst_min) / 2
	//else
	//	collision = (player_min + obst_max) / 2
	if (hitbox.maxPlayerBox.x < obstacle.obstacleBox.max_position.x && hitbox.minPlayerBox.x > obstacle.obstacleBox.min_position.x) {
		collisionCenter.x = (hitbox.minPlayerBox.x + hitbox.maxPlayerBox.x) / 2;
	}else if (abs(hitbox.maxPlayerBox.x - obstacle.obstacleBox.min_position.x) <= abs(hitbox.minPlayerBox.x - obstacle.obstacleBox.max_position.x)) {
		collisionCenter.x = (hitbox.maxPlayerBox.x + obstacle.obstacleBox.min_position.x) / 2;
	}
	else {
		collisionCenter.x = (hitbox.minPlayerBox.x + obstacle.obstacleBox.max_position.x) / 2;
	}

	if (hitbox.maxPlayerBox.y < obstacle.obstacleBox.max_position.y && hitbox.minPlayerBox.y > obstacle.obstacleBox.min_position.y) {
		collisionCenter.y = (hitbox.minPlayerBox.y + hitbox.maxPlayerBox.y) / 2;
	}else if (abs(hitbox.maxPlayerBox.y - obstacle.obstacleBox.min_position.y) <= abs(hitbox.minPlayerBox.y - obstacle.obstacleBox.max_position.y)) {
		collisionCenter.y = (hitbox.maxPlayerBox.y + obstacle.obstacleBox.min_position.y) / 2;
	}
	else {
		collisionCenter.y = (hitbox.minPlayerBox.y + obstacle.obstacleBox.max_position.y) / 2;
	}

	if (hitbox.maxPlayerBox.z < obstacle.obstacleBox.max_position.z && hitbox.minPlayerBox.z > obstacle.obstacleBox.min_position.z) {
		collisionCenter.z = (hitbox.minPlayerBox.z + hitbox.maxPlayerBox.z) / 2;
	}else if (abs(hitbox.maxPlayerBox.z - obstacle.obstacleBox.min_position.z) <= abs(hitbox.minPlayerBox.z - obstacle.obstacleBox.max_position.z)) {
		collisionCenter.z = (hitbox.maxPlayerBox.z + obstacle.obstacleBox.min_position.z) / 2;
	}
	else {
		collisionCenter.z = (hitbox.minPlayerBox.z + obstacle.obstacleBox.max_position.z) / 2;
	}
	return collisionCenter;
}

void Player::react_collision(Obstacle obstacle) {
	glm::vec3 centerCollision = center_collision(obstacle);
	float x_distance = abs(pos_player.x - centerCollision.x);
	float z_distance = abs(pos_player.z - centerCollision.z);
	if (x_distance < z_distance) {//calculates if the collision is on the x or the z axis of the player
		if(centerCollision.z - pos_player.z < 0.0f){//if the player is moving towards the negative z...
			cel_player.z = 0.002f;//we push him back to the positive z
			pushedList.push_back('D');
		}
		else {//else we push him to the negative z
			cel_player.z = -0.002f;
			pushedList.push_back('U');
		}
	}
	else {
		if (centerCollision.x - pos_player.x < 0.0f) {
			cel_player.x = 0.002f;
			pushedList.push_back('R');
		}
		else {
			cel_player.x = -0.002f;
			pushedList.push_back('L');
		}
	}
	cel_player += obstacle.obstacleVelocity;
}