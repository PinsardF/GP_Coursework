//#include <iostream>
#include "Obstacle.h"
#include "PlayerBoundaryBox.h"
//#include <vector>
//using namespace std;
//#include <string>
#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
//#include <vector>
using namespace std;
#pragma once

class Player
{
public:
	Cube		character;
	PlayerBoundaryBox hitbox;
	glm::vec3	pos_player;
	glm::vec3	cel_player;
	std::vector<char> pushed;

	Player();
	//~Player();
	void init();
	void update_player();
	void render_character(Graphics graphics);
	void detect_collision(Obstacle obstacle);
};