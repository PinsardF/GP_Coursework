#pragma once
class ExplosionParticle{
public:
	int explosionTimetolive;
	glm::vec3 explosionPosition;
	glm::vec3 explosionVelocity;
	//glm::vec3 acceleration;
	bool explosionIsalive;
	Line explosionVisualParticle;

	ExplosionParticle();

	ExplosionParticle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive);//
	void init();

	void update(Graphics graphics);
};

