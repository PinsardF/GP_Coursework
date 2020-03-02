#pragma once
#include <glm\ext\vector_float3.hpp>
#include "Obstacle.h"
#include "Missile.h"

class Event{
public:
	char type;//Type of event : 'O' for Obstacle or 'M' for Missile
	glm::vec3 pos_event;//Position of the event (only for the obstacles)
	glm::vec3 dim_event;//Dimensions of the event (only for the obstacles)
	int timetostart;//Time to wait from the beginning until the event occurs
	char eventDirection;//Direction of the event (only for the obstacles)

	Event(char input_type, glm::vec3 input_pos, glm::vec3 input_dim, int input_time);//Constructor
	Obstacle launch_obstacle();//Creation of a missile
	Missile launch_missile();//Creation of an obstacle
};

