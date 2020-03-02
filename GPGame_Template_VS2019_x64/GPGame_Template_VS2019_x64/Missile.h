#pragma once
#include <glm\gtx\transform.hpp>
#include "shapes.h"
#include "graphics.h"
#include "ExplosionEmitter.h"
#include "Player.h"
#include "Node.h"

class Missile{
public:
	Sphere missileBody;//Visual body of the missile
	glm::vec3 pos_missile;//Position of the missile
	glm::vec3 vel_missile;//Velocity of the missile
	int missileTimeToLive;//Time to live of the missile
	int missileLoadingTime;//Loading time (time to start moving)
	ExplosionEmitter explosion;//Explosion when the missile dies

	Missile(glm::vec3 spawnPoint);//Constructor
	void init();//Initialisation of the missile
	void render_missile(Graphics graphics);//Rendering of the missile
	void update_missile(Graphics graphics);//Updating the missile at each frame
	void pathfinding(Player player);//Following the player
};

