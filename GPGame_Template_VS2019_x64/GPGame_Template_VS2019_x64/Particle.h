#pragma once
class Particle{
public:
	int timetolive;
	glm::vec3 position;
	//glm::vec3 speed;
	//glm::vec3 acceleration;
	bool isalive;
	Line visualParticle;

	Particle();
	Particle(int input_timetolive, glm::vec3 input_vector, bool input_isalive);
	void init();
	void update(Graphics graphics);
	void destroy();
};

