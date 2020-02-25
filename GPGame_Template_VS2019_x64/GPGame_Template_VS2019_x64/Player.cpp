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
Graphics    graphics;
bool        keysStatus[1024];

glm::mat4 move_cube =
	glm::translate(glm::vec3(x, y, z)) *
	glm::mat4(1.0f);

Player::Player(float input_x, float input_y, float input_z) {
	x = input_x;
	y = input_y;
	z = input_z;
}

Player::~Player()
{
	delete this;
}

void init() { character.Load(); }

void set_in_space() {
	character.mv_matrix = graphics.viewMatrix * move_cube;
	character.proj_matrix = graphics.proj_matrix;
}

void render_character() {
	character.Draw();
}

void move() {

	if (keysStatus[GLFW_KEY_UP]) z+=0.01f;
	else if (keysStatus[GLFW_KEY_LEFT]) x -= 0.01f;
	else if (keysStatus[GLFW_KEY_DOWN]) z -= 0.01f;
	if (keysStatus[GLFW_KEY_RIGHT]) x += 0.01f;

	character.mv_matrix = graphics.viewMatrix * move_cube;
	character.proj_matrix = graphics.proj_matrix;
}