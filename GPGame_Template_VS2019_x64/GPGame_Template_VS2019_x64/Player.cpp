// Standard C++ libraries
#include <iostream>
#include <vector>
using namespace std;
#include <string>

// Helper graphic libraries
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#include <vector>
#include "Player.h"

float		x;
float		y;
float		z;
Cube		character;
bool        keysStatus[1024];
glm::mat4    pos_player;

Player::Player() {
	x = 0.0f;
	y = 0.5f;
	z = 0.0f;
	pos_player =
		glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f);
}

/*Player::~Player()
{
	delete this;
}*/

void Player::init() {
	Cube* visualPlayer = new Cube;
	character = *visualPlayer;
	character.Load();
	character.fillColor = glm::vec4(0.0f, 0.0f, 255.0f, 1.0f); // Blue color
}

void Player::render_character() {
	character.Draw();
}

void Player::set_in_space(Graphics graphics) {
	character.mv_matrix = graphics.viewMatrix * pos_player;
	character.proj_matrix = graphics.proj_matrix;
}

void Player::move(Graphics graphics, bool* keyStatus) {
	if (keyStatus[GLFW_KEY_UP]) {
		z += 0.01f;
		cout << "monte" << endl;
	}
	else if (keyStatus[GLFW_KEY_LEFT]) x += 0.01f;
	else if (keyStatus[GLFW_KEY_DOWN]) z -= 0.01f;
	else if (keyStatus[GLFW_KEY_RIGHT]) x -= 0.01f;

	glm::mat4 pos_player =
		glm::translate(glm::vec3(x, y, z)) *
		glm::mat4(1.0f);
	set_in_space(graphics);
}