//#include <iostream>
#include "Obstacle.h"
#include "PlayerBoundaryBox.h"
#include "Arena.h"
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
	std::vector<char> pushedList;

	Player();
	//~Player();
	void init();
	void update_player();
	void render_character(Graphics graphics);
	bool detect_collision_obstacles(Obstacle obstacle);
	void detect_collision_walls();
	glm::vec3 center_collision(Obstacle obstacle);
	void react_collision(Obstacle obstacle);
};