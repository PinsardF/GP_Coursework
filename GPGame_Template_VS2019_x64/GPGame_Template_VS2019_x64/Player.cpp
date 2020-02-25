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

float		x = 2.0f;
float		y = 0.5f;
float		z = 0.0f;
Cube		character;
bool        keysStatus[1024];
glm::mat4    pos_player;

Player::Player() {
	x = 2.0f;
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
}

void Player::render_character() {
	character.Draw();
}

void Player::set_in_space(Graphics myGraphics) {
	character.mv_matrix = myGraphics.viewMatrix * pos_player;
	character.proj_matrix = myGraphics.proj_matrix;
}

void Player::move() {

	if (keysStatus[GLFW_KEY_UP]) z+=0.01f;
	else if (keysStatus[GLFW_KEY_LEFT]) x -= 0.01f;
	else if (keysStatus[GLFW_KEY_DOWN]) z -= 0.01f;
	if (keysStatus[GLFW_KEY_RIGHT]) x += 0.01f;

	character.mv_matrix = graphics.viewMatrix * pos_player;
	character.proj_matrix = graphics.proj_matrix;
}