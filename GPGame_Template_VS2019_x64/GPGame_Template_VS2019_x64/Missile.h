#pragma once
#include "shapes.h"
#include "graphics.h"
#include "ExplosionEmitter.h"
#include "Player.h"

class Missile{
public:
	Sphere missileBody;
	glm::vec3 pos_missile;
	glm::vec3 vel_missile;
	int missileTimeToLive;
	int missileLoadingTime;
	ExplosionEmitter explosion;


	Missile(glm::vec3 spawnPoint);
	void init();
	void render_missile(Graphics graphics);
	void update_missile(Graphics graphics);
	void pathfinding(Player player);
};

