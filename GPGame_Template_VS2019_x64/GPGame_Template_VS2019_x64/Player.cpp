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

glm::vec3	position;
Cube		character;
glm::mat4	pos_player;

Player::Player() {
	position.x = 0.0f;
	position.y = 0.5f;
	position.z = 0.0f;
	pos_player =
		glm::translate(glm::vec3(position.x, position.y, position.z)) *
		glm::mat4(1.0f);
}

/*Player::~Player()
{
	delete this;
}*/

void Player::init() {
	character.Load();
	character.fillColor = glm::vec4(0.0f, 0.0f, 255.0f, 1.0f); // Blue color
}

void Player::render_character() {
	character.Draw();
}