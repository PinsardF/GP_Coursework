#include "ExplosionParticle.h"

int explosionTimetolive;
glm::vec3 explosionPosition;
glm::vec3 explosionVelocity;
//glm::vec3 acceleration;
bool explosionIsalive;
Line explosionVisualParticle;

ExplosionParticle::ExplosionParticle(int input_timetolive, glm::vec3 input_position, glm::vec3 input_velocity, bool input_isalive) {
	explosionTimetolive = input_timetolive;
	explosionPosition.x = input_position.x;
	explosionPosition.y = input_position.y;
	explosionPosition.z = input_position.z;
	explosionVelocity.x = input_velocity.x;
	explosionVelocity.y = input_velocity.y;
	explosionVelocity.z = input_velocity.z;
	explosionIsalive = input_isalive;
}

ExplosionParticle::ExplosionParticle() : explosionTimetolive(200), explosionPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
explosionVelocity(glm::vec3(0.0f, 0.0f, 0.0f)), explosionIsalive(true) {}

void ExplosionParticle::init() {
	explosionVisualParticle.Load();
	float color_a = rand() % 100;//choosing random colors
	color_a /= 100;
	float color_b = rand() % 100;
	color_b /= 100;
	float color_c = rand() % 100;
	color_c /= 100;
	float color_d = rand() % 100;
	color_d /= 100;
	explosionVisualParticle.fillColor = glm::vec4(/*1.0f, 1.0f, 1.0f, 1.0f*/color_a, color_b, color_c, color_d);
	explosionVisualParticle.lineColor = glm::vec4(/*0.2f, 1.0f, 0.8f, 1.0f*/color_a, color_b, color_c, color_d);
	explosionVisualParticle.lineWidth = 5.0f;
	float x_deviation = rand() % 10;
	float x_sign = rand() % 2;
	if (x_sign > 0) x_deviation = -x_deviation;
	x_deviation /= 100;
	float y_deviation = rand() % 10;
	float y_sign = rand() % 2;
	if (y_sign > 0) y_deviation = -y_deviation;
	y_deviation /= 100;
	float z_deviation = rand() % 10;
	float z_sign = rand() % 2;
	if (z_sign > 0) z_deviation = -z_deviation;
	z_deviation /= 100;
	explosionVelocity = glm::vec3(x_deviation, y_deviation, z_deviation);
}

void ExplosionParticle::update(Graphics graphics) {
	if (explosionTimetolive > 0.0f) {
		explosionPosition.x += explosionVelocity.x;
		explosionPosition.y += explosionVelocity.y;
		explosionPosition.z += explosionVelocity.z;
		explosionTimetolive--;//lifetime decreases
		glm::mat4 mv_particle =//we calculate the new projection of the particle
			glm::translate(explosionPosition) *
			glm::scale(glm::vec3(200.0f, 200.0f, 0.03f)) *
			glm::mat4(1.0f);
		explosionVisualParticle.mv_matrix = graphics.viewMatrix * mv_particle;
		explosionVisualParticle.proj_matrix = graphics.proj_matrix;
	}
}
