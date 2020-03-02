#include "Obstacle.h"
#include "PlayerBoundaryBox.h"
#include "Arena.h"
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#pragma once

class Player
{
public:
	Cube character;//Visual body of the player
	PlayerBoundaryBox hitbox;//Hitbox of the player
	glm::vec3 pos_player;//Position of the player
	glm::vec3 cel_player;//Velocity of the player
	std::vector<char> pushedList;//List of directions where the player is pushed (to know when he gets crushed)
	int lives;//Number of lives
	bool alive;//Is the player still alive ?

	Player();//Constructor
	void init();//Initialisation of the player
	void update_player();//Updating the player at each frame
	void render_character(Graphics graphics);//Rendering the player
	bool detect_collision_obstacles(Obstacle obstacle);// Detecting collisions with the obstacles
	void detect_collision_walls();//Detecting collisions with the walls
	bool detect_collision_missile(float input_x, float input_z);//Detecting collsions with the missiles
	glm::vec3 center_collision(Obstacle obstacle);//Determining the center of collision
	void react_collision(Obstacle obstacle);//Reaction to the collision
	void hurt();//Losing a life
	void death();//Dying when the player has no life left
};