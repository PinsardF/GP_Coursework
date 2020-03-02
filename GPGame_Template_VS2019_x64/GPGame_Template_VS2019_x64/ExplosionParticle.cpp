#include "ExplosionParticle.h"

int explosionTimetolive;//Time to live of the particle
glm::vec3 explosionPosition;//Position of the particle
glm::vec3 explosionVelocity;//Velocity of the particle
bool explosionIsalive;//Is the particle still on screen ?
Line explosionVisualParticle;//Visual body of the particle

ExplosionParticle::ExplosionParticle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive) {
	explosionTimetolive = input_timetolive;
	explosionPosition = input_position;
	explosionVelocity = input_velocity;
	explosionIsalive = input_isalive;
}

ExplosionParticle::ExplosionParticle() : explosionTimetolive(200), explosionPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
explosionVelocity(glm::vec3(0.0f, 0.0f, 0.0f)), explosionIsalive(true) {}

void ExplosionParticle::init() {
	explosionVisualParticle.Load();
	float color_a = rand() % 100;//Choosing random colors
	color_a /= 100;
	float color_b = rand() % 100;
	color_b /= 100;
	float color_c = rand() % 100;
	color_c /= 100;
	float color_d = rand() % 100;
	color_d /= 100;
	explosionVisualParticle.fillColor = glm::vec4(color_a, color_b, color_c, color_d);
	explosionVisualParticle.lineColor = glm::vec4(color_a, color_b, color_c, color_d);
	explosionVisualParticle.lineWidth = 5.0f;
	float x_deviation = rand() % 10;//Choosing random direction (random x, y and z, then the vector is normalized)
	float x_sign = rand() % 2;
	if (x_sign > 0) x_deviation = -x_deviation;
	x_deviation /= 260;
	float y_deviation = rand() % 10;
	float y_sign = rand() % 2;
	if (y_sign > 0) y_deviation = -y_deviation;
	y_deviation /= 260;
	float z_deviation = rand() % 10;
	float z_sign = rand() % 2;
	if (z_sign > 0) z_deviation = -z_deviation;
	z_deviation /= 260;
	explosionVelocity = glm::vec3(x_deviation, y_deviation, z_deviation);
}

void ExplosionParticle::update(Graphics graphics) {
	if (explosionTimetolive > 0.0f) {
		explosionPosition += explosionVelocity;
		explosionTimetolive--;//Lifetime decreases
		glm::mat4 mv_particle =//We calculate the new projection of the particle
			glm::translate(explosionPosition) *
			glm::scale(glm::vec3(1000.0f, 1000.0f, 0.2f)) *
			glm::mat4(1.0f);
		explosionVisualParticle.mv_matrix = graphics.viewMatrix * mv_particle;
		explosionVisualParticle.proj_matrix = graphics.proj_matrix;
		explosionVisualParticle.Draw();//And we draw it
	}
}
