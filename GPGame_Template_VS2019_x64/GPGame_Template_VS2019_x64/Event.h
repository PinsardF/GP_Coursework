#pragma once
#include <glm\ext\vector_float3.hpp>
#include "Obstacle.h"
class Event{
public:
	char type;
	glm::vec3 pos_event;
	glm::vec3 dim_event;
	int timetostart;
	char eventDirection;

	Event(char input_type, glm::vec3 input_pos, glm::vec3 input_dim, int input_time);
	Event(char input_type);
	void update_event();
	Obstacle launch_obstacle();
};

