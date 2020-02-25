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

Player::Player(float input_x, float input_y, float input_z) {
	x = input_x;
	y = input_y;
	z = input_z;
	cout << "Initilialisé à " << x << " " << y << " " << y << endl;
}

/*Player::~Player()
{
	delete this;
}*/

void Player::init() {
	Cube* visualPlayer = new Cube;
	character = *visualPlayer;
	character.Load();
	cout << "Load" << endl;
}

void Player::render_character() {
	character.Draw();
	cout << "Rendering " << character.lineWidth << endl;
}

void Player::move() {

	if (keysStatus[GLFW_KEY_UP]) z+=0.01f;
	else if (keysStatus[GLFW_KEY_LEFT]) x -= 0.01f;
	else if (keysStatus[GLFW_KEY_DOWN]) z -= 0.01f;
	if (keysStatus[GLFW_KEY_RIGHT]) x += 0.01f;

	character.mv_matrix = graphics.viewMatrix * pos_char;
	character.proj_matrix = graphics.proj_matrix;

	cout << "Rendering" << endl;
}