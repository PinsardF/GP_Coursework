
#include <iostream>
#include <vector>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "graphics.h"
#include "shapes.h"
#include <vector>
#include "glm/ext.hpp"

// Personal classes
#include "Player.h"
#include "Arena.h"
#include "Obstacle.h"
#include "Event.h"
#include "Missile.h"
#include "ExplosionEmitter.h"
#include "Particle.h"

// MAIN FUNCTIONS
void startup();
void updateCamera();
void updateSceneElements();
void renderScene();

// CALLBACK FUNCTIONS
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void onMouseMoveCallback(GLFWwindow* window, double x, double y);
void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset);

// VARIABLES
bool        quit = false;
float       deltaTime = 0.0f;    // Keep track of time per frame.
float       lastTime = 0.0f;    // variable to keep overall time.
bool        keyStatus[1024];    // Hold key status.
bool		mouseEnabled = true; // keep track of mouse toggle.

// MAIN GRAPHICS OBJECT
Graphics    myGraphics;        // Runing all the graphics in this object

// Objects
Player	player;
Arena	arena;
std::vector<Obstacle> obstaclesList;
std::vector<Event> eventsList;
std::vector<Missile> missilesList;
//Missile missile = Missile(glm::vec3(7.5f, 0.5f, 7.5f));

// Some global variable to do the animation.
float t = 0.001f;            // Global variable for animation


int main()
{
	int errorGraphics = myGraphics.Init();			// Launch window and graphics context
	if (errorGraphics) return 0;					// Close if something went wrong...

	startup();										// Setup all necessary information for startup (aka. load texture, shaders, models, etc).s

	// MAIN LOOP run until the window is closed
	while (!quit) {

		// Update the camera transform based on interactive inputs or by following a predifined path.
		updateCamera();

		// Update position, orientations and any other relevant visual state of any dynamic elements in the scene.
		updateSceneElements();

		// Render a still frame into an off-screen frame buffer known as the backbuffer.
		renderScene();

		// Swap the back buffer with the front buffer, making the most recently rendered image visible on-screen.
		glfwSwapBuffers(myGraphics.window);        // swap buffers (avoid flickering and tearing)

	}


	myGraphics.endProgram();            // Close and clean everything up...

   // cout << "\nPress any key to continue...\n";
   // cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {
	// Keep track of the running time
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime;                        // start delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Callback graphics and key update functions - declared in main to avoid scoping complexity.
	// More information here : https://www.glfw.org/docs/latest/input_guide.html
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);            // Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);                    // Set Callback for keys
	glfwSetMouseButtonCallback(myGraphics.window, onMouseButtonCallback);    // Set callback for mouse click
	glfwSetCursorPosCallback(myGraphics.window, onMouseMoveCallback);        // Set callback for mouse move
	glfwSetScrollCallback(myGraphics.window, onMouseWheelCallback);            // Set callback for mouse wheel.

	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	player.init();
	arena.init();
	//missile.init();

	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 0.5f), glm::vec3(0.9f, 0.9f, 2.0f),120));
	eventsList.push_back(Event('O', glm::vec3(5.5f, 0.5f, 9.0f), glm::vec3(4.0f, 0.9f, 0.9f),150));
	eventsList.push_back(Event('O', glm::vec3(-9.0f, 0.5f, 1.0f), glm::vec3(0.9f, 0.9f, 10.0f), 200));
	eventsList.push_back(Event('O', glm::vec3(4.5f, 0.5f, -9.0f), glm::vec3(8.0f, 0.9f, 0.9f), 200));
	eventsList.push_back(Event('O', glm::vec3(-2.5f, 0.5f, -9.0f), glm::vec3(12.0f, 0.9f, 0.9f), 400));
	eventsList.push_back(Event('O', glm::vec3(2.5f, 0.5f, -9.0f), glm::vec3(12.0f, 0.9f, 0.9f), 450));
	eventsList.push_back(Event('O', glm::vec3(-2.5f, 0.5f, -9.0f), glm::vec3(12.0f, 0.9f, 0.9f), 500));
	eventsList.push_back(Event('O', glm::vec3(2.5f, 0.5f, -9.0f), glm::vec3(12.0f, 0.9f, 0.9f), 550));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -1.0f), glm::vec3(0.9f, 0.9f, 15.0f), 800));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -4.0f), glm::vec3(0.9f, 0.9f, 9.0f), 900));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 7.5f), glm::vec3(0.9f, 0.9f, 3.0f), 900));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -5.0f), glm::vec3(0.9f, 0.9f, 7.0f), 1000));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 6.5f), glm::vec3(0.9f, 0.9f, 5.0f), 1000));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -8.0f), glm::vec3(0.9f, 0.9f, 1.0f), 1100));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 3.5f), glm::vec3(0.9f, 0.9f, 11.0f), 1100));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -3.0f), glm::vec3(0.9f, 0.9f, 11.0f), 1200));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 7.0f), glm::vec3(0.9f, 0.9f, 4.0f), 1200));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -8.0f), glm::vec3(0.9f, 0.9f, 1.0f), 1300));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 2.0f), glm::vec3(0.9f, 0.9f, 14.0f), 1300));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -1.5f), glm::vec3(0.9f, 0.9f, 14.0f), 1400));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 7.5f), glm::vec3(0.9f, 0.9f, 1.0f), 1400));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, -8.0f), glm::vec3(0.9f, 0.9f, 1.0f), 1500));
	eventsList.push_back(Event('O', glm::vec3(9.0f, 0.5f, 1.5f), glm::vec3(0.9f, 0.9f, 15.0f), 1500));
	eventsList.push_back(Event('M', glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1700));
	eventsList.push_back(Event('M', glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1700));
	eventsList.push_back(Event('M', glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1800));
	eventsList.push_back(Event('M', glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 1900));
	eventsList.push_back(Event('M', glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 2000));
	eventsList.push_back(Event('M', glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 2000));


	for (int i = 0; i < obstaclesList.size(); i++) {
		obstaclesList[i].init();
	}

	// Optimised Graphics
	myGraphics.SetOptimisations();        // Cull and depth testing
}

void updateCamera() {

	// calculate movement for FPS camera
	GLfloat xoffset = myGraphics.mouseX - myGraphics.cameraLastX;
	GLfloat yoffset = myGraphics.cameraLastY - myGraphics.mouseY;    // Reversed mouse movement
	myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX;
	myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY;

	GLfloat sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	myGraphics.cameraYaw += xoffset;
	myGraphics.cameraPitch += yoffset;

	// check for pitch out of bounds otherwise screen gets flipped
	if (myGraphics.cameraPitch > 89.0f) myGraphics.cameraPitch = 89.0f;
	if (myGraphics.cameraPitch < -89.0f) myGraphics.cameraPitch = -89.0f;

	// Calculating FPS camera movement (See 'Additional Reading: Yaw and Pitch to Vector Calculations' in VISION)
	glm::vec3 front;
	front.x = cos(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));
	front.y = sin(glm::radians(myGraphics.cameraPitch));
	front.z = sin(glm::radians(myGraphics.cameraYaw)) * cos(glm::radians(myGraphics.cameraPitch));

	myGraphics.cameraFront = glm::normalize(front);

	// Update movement using the keys
	GLfloat cameraSpeed = 3.0f * deltaTime;
	if (keyStatus[GLFW_KEY_W]) myGraphics.cameraPosition += cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_S]) myGraphics.cameraPosition -= cameraSpeed * myGraphics.cameraFront;
	if (keyStatus[GLFW_KEY_A]) myGraphics.cameraPosition -= glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;
	if (keyStatus[GLFW_KEY_D]) myGraphics.cameraPosition += glm::normalize(glm::cross(myGraphics.cameraFront, myGraphics.cameraUp)) * cameraSpeed;

	// IMPORTANT PART
	// Calculate my view matrix using the lookAt helper function
	if (mouseEnabled) {
		myGraphics.viewMatrix = glm::lookAt(myGraphics.cameraPosition,			// eye
			myGraphics.cameraPosition + myGraphics.cameraFront,					// centre
			myGraphics.cameraUp);												// up
	}
}

void updateSceneElements() {

	glfwPollEvents();                                // poll callbacks

	// Calculate frame time/period -- used for all (physics, animation, logic, etc).
	GLfloat currentTime = (GLfloat)glfwGetTime();    // retrieve timelapse
	deltaTime = currentTime - lastTime;                // Calculate delta time
	lastTime = currentTime;                            // Save for next frame calculations.

	// Do not forget your ( T * R * S ) http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	
	// Player's movements
	if (keyStatus[GLFW_KEY_UP]) player.cel_player.z += 0.1f;//CHANGE TO 0.07f
	if (keyStatus[GLFW_KEY_LEFT]) player.cel_player.x += 0.1f;//CHANGE
	if (keyStatus[GLFW_KEY_DOWN]) player.cel_player.z -= 0.1f;//CHANGE
	if (keyStatus[GLFW_KEY_RIGHT]) player.cel_player.x -= 0.1f;//CHANGE

	for (int i = 0; i < obstaclesList.size(); i++) {
		obstaclesList[i].update_obstacle();
	}
	for (int i = 0; i < obstaclesList.size(); i++) {
		if (player.detect_collision_obstacles(obstaclesList[i])) {
			player.react_collision(obstaclesList[i]);
		}
	}
	for (int i = 0; i < missilesList.size(); i++) {
		if (missilesList[i].missileTimeToLive > 0) {
			missilesList[i].update_missile(myGraphics);
		}
		if (missilesList[i].missileLoadingTime <= 0 && missilesList[i].missileTimeToLive > 5) {
			if (!player.detect_collision_missile(missilesList[i].pos_missile.x, missilesList[i].pos_missile.z)) {
				missilesList[i].pathfinding(player);
			}
			else {
				player.death();
				missilesList[i].missileTimeToLive = 5;
			}
		}
	}
	player.detect_collision_walls();
	player.update_player();
	arena.flashing_cube();
	//missile.update_missile(myGraphics);
	/*if (missile.missileLoadingTime <= 0 && missile.missileTimeToLive > 5) {
		missile.pathfinding(player);
	}*/

	int j = 0;//managing events
	float this_minimum = 0.0f;
	float this_maximum = 0.0f;
	for (int i = 0; i < eventsList.size(); i++) {
		switch (eventsList[i].type) {
		case 'O':
			if (eventsList[i].timetostart == 120) {
				switch (eventsList[i].eventDirection) {
				case 'E':
					this_minimum = eventsList[i].pos_event.z - (eventsList[i].dim_event.z / 2);
					this_maximum = eventsList[i].pos_event.z + (eventsList[i].dim_event.z / 2);
					j = (int)(this_minimum + 0.5f);
					while (j < this_maximum) {
						arena.flashingCubesChar.push_back(eventsList[i].eventDirection);
						arena.flashingCubesTime.push_back(120);
						arena.flashingCubesInt.push_back(8 + j);
						j++;
					}
					break;
				case 'W':
					this_minimum = eventsList[i].pos_event.z - (eventsList[i].dim_event.z / 2);
					this_maximum = eventsList[i].pos_event.z + (eventsList[i].dim_event.z / 2);
					j = (int)(this_minimum + 0.5f);
					while (j < this_maximum) {
						arena.flashingCubesChar.push_back(eventsList[i].eventDirection);
						arena.flashingCubesTime.push_back(120);
						arena.flashingCubesInt.push_back(8 + j);
						j++;
					}
					break;
				case 'S':
					this_minimum = eventsList[i].pos_event.x - (eventsList[i].dim_event.x / 2);
					this_maximum = eventsList[i].pos_event.x + (eventsList[i].dim_event.x / 2);
					j = (int)(this_minimum + 0.5f);
					while (j < this_maximum) {
						arena.flashingCubesChar.push_back(eventsList[i].eventDirection);
						arena.flashingCubesTime.push_back(120);
						arena.flashingCubesInt.push_back(8 - j);
						j++;
					}
					break;
				case 'N':
					this_minimum = eventsList[i].pos_event.x - (eventsList[i].dim_event.x / 2);
					this_maximum = eventsList[i].pos_event.x + (eventsList[i].dim_event.x / 2);
					j = (int)(this_minimum + 0.5f);
					while (j < this_maximum) {
						arena.flashingCubesChar.push_back(eventsList[i].eventDirection);
						arena.flashingCubesTime.push_back(120);
						arena.flashingCubesInt.push_back(8 - j);
						j++;
					}
					break;
				}
				eventsList[i].timetostart--;

			}
			else if (eventsList[i].timetostart > 0) {
				eventsList[i].timetostart--;
			}
			else {
				obstaclesList.insert(obstaclesList.begin(), eventsList[i].launch_obstacle());
				obstaclesList[0].init();
				eventsList.erase(eventsList.begin() + i);
			}
			break;
		case 'M':
			if (eventsList[i].timetostart > 0) {
				eventsList[i].timetostart--;
			}
			else if (eventsList[i].timetostart == 0) {
				missilesList.insert(missilesList.begin(), eventsList[i].launch_missile());
				missilesList[0].init();
				eventsList.erase(eventsList.begin() + i);
			}
		}
	}

	arena.flashing_cube();

	t += 0.01f; // increment movement variables

	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) quit = true; // If quit by pressing x on window.
}

void renderScene() {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw objects in screen
	player.render_character(myGraphics);
	arena.render_arena(myGraphics);
	arena.update_arena(myGraphics);
	//missile.render_missile(myGraphics);

	/*if (missile.missileTimeToLive < 5) {
		missile.explosion.update(myGraphics);
	}*/

	for (int i = 0; i < obstaclesList.size(); i++) {
		obstaclesList[i].render_obstacle(myGraphics);
	}

	for (int i = 0; i < obstaclesList.size(); i++) {
		if (obstaclesList[i].obstacleDirection == 'X') {
			obstaclesList.erase(obstaclesList.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < missilesList.size(); i++) {
		missilesList[i].render_missile(myGraphics);
		if (missilesList[i].missileTimeToLive < 5 && missilesList[i].missileTimeToLive > -30) {
			missilesList[i].explosion.update(myGraphics);
		}
	}
	for (int i = 0; i < missilesList.size(); i++) {
		if (missilesList[i].missileTimeToLive < -30) {
			missilesList.erase(missilesList.begin() + i);
			i--;
		}
	}
	arena.flashing_cube();
}



// CallBack functions low level functionality.
void onResizeCallback(GLFWwindow* window, int w, int h) {    // call everytime the window is resized
	//myGraphics.windowWidth = w;
	//myGraphics.windowHeight = h;

	glfwGetFramebufferSize(window, &myGraphics.windowWidth, &myGraphics.windowHeight);

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (action == GLFW_PRESS) keyStatus[key] = true;
	else if (action == GLFW_RELEASE) keyStatus[key] = false;

	// toggle showing mouse.
	if (keyStatus[GLFW_KEY_M]) {
		mouseEnabled = !mouseEnabled;
		myGraphics.ToggleMouse();
	}
	// If exit key pressed.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void onMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void onMouseMoveCallback(GLFWwindow* window, double x, double y) {
	int mouseX = static_cast<int>(x);
	int mouseY = static_cast<int>(y);

	myGraphics.mouseX = mouseX;
	myGraphics.mouseY = mouseY;

	// helper variables for FPS camera
	if (myGraphics.cameraFirstMouse) {
		myGraphics.cameraLastX = (GLfloat)myGraphics.mouseX; myGraphics.cameraLastY = (GLfloat)myGraphics.mouseY; myGraphics.cameraFirstMouse = false;
	}
}

void onMouseWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
	int yoffsetInt = static_cast<int>(yoffset);
}
