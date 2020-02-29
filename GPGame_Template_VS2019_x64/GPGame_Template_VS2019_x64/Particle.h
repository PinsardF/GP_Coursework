#pragma once
class Particle{
public:
	int timetolive;
	glm::vec3 p_position;
	glm::vec3 velocity;
	//glm::vec3 acceleration;
	bool isalive;
	Line visualParticle;

	Particle();

	Particle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive);
	void init();

	void update(Graphics graphics);
};

