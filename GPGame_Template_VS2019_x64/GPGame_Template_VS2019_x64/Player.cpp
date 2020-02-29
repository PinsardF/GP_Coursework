#include "Player.h"

Cube		character;
PlayerBoundaryBox hitbox;
glm::vec3	pos_player;
glm::vec3	cel_player;
std::vector<char> pushed;

Player::Player() {
	pos_player = glm::vec3(0.0f,0.5f,0.0f);
	cel_player = glm::vec3(0.0f,0.0f,0.0f);
	pushed.clear();
}

/*Player::~Player()
{
	delete this;
}*/

void Player::init() {
	character.Load();
	character.fillColor = glm::vec4(0.0f, 0.0f, 255.0f, 1.0f); // Blue color
}

void Player::update_player() {
	for (int i = 0; i < pushed.size(); i++) {
		switch (pushed[i]) {
		case 'E':
			if (cel_player.x > -0.05f) {
				cel_player.x = -0.05f;
			}
			break;
		case 'W':
			if (cel_player.x > 0.05f) {
				cel_player.x = 0.05f;
			}
			break;
		case 'N':
			if (cel_player.z > 0.05f) {
				cel_player.z = 0.05f;
			}
			break;
		case 'S':
			if (cel_player.z > -0.05f) {
				cel_player.z = -0.05f;
			}
			break;
		}
	}
	pos_player += cel_player;
	hitbox.playerBoxCenter = pos_player;
	hitbox.minPlayerBox += cel_player;
	hitbox.maxPlayerBox += cel_player;
	cel_player = glm::vec3(0.0f, 0.0f, 0.0f);
	pushed.clear();
}

void Player::render_character(Graphics graphics) {
	glm::mat4 mv_player =
		glm::translate(pos_player) *
		glm::mat4(1.0f);
	character.mv_matrix = graphics.viewMatrix * mv_player;
	character.proj_matrix = graphics.proj_matrix;
	character.Draw();
}

void Player::detect_collision(Obstacle obstacle) {
	if (hitbox.maxPlayerBox.x >= obstacle.obstacleBox.min_position.x && hitbox.minPlayerBox.x <= obstacle.obstacleBox.max_position.x &&
		hitbox.maxPlayerBox.y >= obstacle.obstacleBox.min_position.y && hitbox.minPlayerBox.y <= obstacle.obstacleBox.max_position.y &&
		hitbox.maxPlayerBox.z >= obstacle.obstacleBox.min_position.z && hitbox.minPlayerBox.z <= obstacle.obstacleBox.max_position.z) {
		pushed.push_back(obstacle.obstacleDirection);
	}
}