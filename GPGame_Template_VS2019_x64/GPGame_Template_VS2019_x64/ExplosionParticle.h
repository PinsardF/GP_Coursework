#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#pragma once
class ExplosionParticle{
public:
	int explosionTimetolive;//Time to live of the particle
	glm::vec3 explosionPosition;//Position of the particle
	glm::vec3 explosionVelocity;//Velocity of the particle
	bool explosionIsalive;//Is the particle still on screen ?
	Line explosionVisualParticle;//Visual body of the particle

	ExplosionParticle();//Constructor
	ExplosionParticle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive);//Constructor
	void init();//Initialisation of the particle
	void update(Graphics graphics);//Updating the particle at each frame
};

