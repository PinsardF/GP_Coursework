#include "Particle.h"

int timetolive;
glm::vec3 p_position;
glm::vec3 velocity;
//glm::vec3 acceleration;
bool isalive;
Line visualParticle;

Particle::Particle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive) {
	timetolive = input_timetolive;
	p_position.x = input_position.x;
	p_position.y = input_position.y;
	p_position.z = input_position.z;
	velocity.x = input_velocity.x;
	velocity.y = input_velocity.y;
	velocity.z = input_velocity.z;
	isalive = input_isalive;
}

Particle::Particle() : timetolive(200), p_position(glm::vec3(0.0f, 0.0f, 0.0f)), velocity(glm::vec3(0.0f,0.0f,0.0f)),
isalive(true) {}

void Particle::init() {
	visualParticle.Load();
	float color_a = rand() % 100;//choosing random colors
	color_a /= 100;
	float color_b = rand() % 100;
	color_b /= 100;
	float color_c = rand() % 100;
	color_c /= 100;
	float color_d = rand() % 100;
	color_d /= 100;
	visualParticle.fillColor = glm::vec4(/*1.0f, 1.0f, 1.0f, 1.0f*/color_a,color_b,color_c,color_d);
	visualParticle.lineColor = glm::vec4(/*0.2f, 1.0f, 0.8f, 1.0f*/color_a, color_b, color_c, color_d);
	visualParticle.lineWidth = 5.0f;
}

void Particle::update(Graphics graphics) {
	if (timetolive > 0.0f) {//if the particle's lifetime isn't over...
		float x_deviation = rand() % 10;//it randomly deviates on the x and z axis
		float x_sign = rand() % 2;
		if (x_sign > 0) x_deviation = -x_deviation;
		x_deviation /= 200;
		float z_deviation = rand() % 10;
		float z_sign = rand() % 2;
		if (z_sign > 0) z_deviation = -z_deviation;
		z_deviation /= 200;
		velocity = glm::vec3(x_deviation, 0.01f, z_deviation);
		p_position.x += velocity.x;
		p_position.y += velocity.y;
		p_position.z += velocity.z;
		timetolive--;//lifetime decreases
		glm::mat4 mv_particle =//we calculate the new projection of the particle
			glm::translate(p_position) *
			glm::scale(glm::vec3(200.0f, 200.0f, 0.03f)) *
			glm::mat4(1.0f);
		visualParticle.mv_matrix = graphics.viewMatrix * mv_particle;
		visualParticle.proj_matrix = graphics.proj_matrix;
		//visualParticle.Draw();
	}
}
