#include "Event.h"
#include <time.h>

char type;//Type of event : 'O' for Obstacle or 'M' for Missile
glm::vec3 pos_event;//Position of the event (only for the obstacles)
glm::vec3 dim_event;//Dimensions of the event (only for the obstacles)
int timetostart;//Time to wait from the beginning until the event occurs
char eventDirection;//Direction of the event (only for the obstacles)

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

Missile Event::launch_missile() {
	srand(time(NULL));//Random initilisation
	int rand_x = rand() % 32;
	int rand_z = rand() % 32;
	float pos_x = 0.5f * (16 - rand_x);
	float pos_z = 0.5f * (16 - rand_z);
	cout << pos_x << ' ' << pos_z;
	return Missile(glm::vec3(pos_x, 0.0f, pos_z));//Returns a missile starting at a random position
}

Obstacle Event::launch_obstacle(){
	return Obstacle(pos_event,eventDirection,dim_event);//Creates an object with the parameters of the Event
}
