#include "Event.h"

char type;
int timetostart;
glm::vec3 pos_event;
glm::vec3 dim_event;
char eventDirection;

Event::Event(char input_type, glm::vec3 input_pos, glm::vec3 input_dim, int input_time) {
	type = input_type;
	pos_event = input_pos;
	dim_event = input_dim;
	timetostart = input_time;
	if (pos_event.x == 9.0f) {
		eventDirection = 'E';
	}
	else if (pos_event.x == -9.0f) {
		eventDirection = 'W';
	}
	else if (pos_event.z == 9.0f) {
		eventDirection = 'S';
	}
	else {
		eventDirection = 'N';
	}

}

Event::Event(char input_type) {
	type = input_type;
}

void Event::update_event() {

}

Obstacle Event::launch_obstacle(){
	return Obstacle(pos_event,eventDirection,dim_event);
}
