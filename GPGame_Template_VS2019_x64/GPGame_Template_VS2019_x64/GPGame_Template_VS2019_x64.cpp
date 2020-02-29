
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
Cube    myFloor;
Cube	flashing_cube;
Player	player;
Arena	arena;
int		frozen = 0, flashing_time = 0, flash = 0, shot_direction_picker = 0, th_cube = 0;
char	walls[4] = { 'N','S','E','O' };
bool	throwing = false;

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

	myFloor.Load();
	myFloor.fillColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand Colour
	myFloor.lineColor = glm::vec4(130.0f / 255.0f, 96.0f / 255.0f, 61.0f / 255.0f, 1.0f);    // Sand again

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
	if (keyStatus[GLFW_KEY_UP]) player.position.z += 0.007f;
	if (keyStatus[GLFW_KEY_LEFT]) player.position.x += 0.007f;
	if (keyStatus[GLFW_KEY_DOWN]) player.position.z -= 0.007f;
	if (keyStatus[GLFW_KEY_RIGHT]) player.position.x -= 0.007f;

	glm::mat4 pos_player =
		glm::translate(glm::vec3(player.position.x, player.position.y, player.position.z)) *
		glm::mat4(1.0f);
	player.character.mv_matrix = myGraphics.viewMatrix * pos_player;
	player.character.proj_matrix = myGraphics.proj_matrix;

	// Calculate floor position and resize
	myFloor.mv_matrix = myGraphics.viewMatrix *
		glm::translate(glm::vec3(0.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(1000.0f, 0.001f, 1000.0f)) *
		glm::mat4(1.0f);
	myFloor.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_arena =
		glm::translate(glm::vec3(0.0f, 0.003f, 0.0f)) *
		glm::scale(glm::vec3(17.0f, 0.001f, 17.0f)) *
		glm::mat4(1.0f);
	arena.arena.mv_matrix = myGraphics.viewMatrix * mv_matrix_arena;
	arena.arena.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_wall_N, mv_matrix_wall_S, mv_matrix_wall_E, mv_matrix_wall_O;
	float original_x = 9.0f;
	float original_z = 8.0f;

	for (int i = 0; i < size(arena.wall_N); i++) {
		mv_matrix_wall_N =
			glm::translate(glm::vec3(original_x, 0.5f, 9.0f)) *
			glm::mat4(1.0f);
		arena.wall_N[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_wall_N;
		arena.wall_N[i].proj_matrix = myGraphics.proj_matrix;

		mv_matrix_wall_S =
			glm::translate(glm::vec3(original_x, 0.5f, -9.0f)) *
			glm::mat4(1.0f);
		arena.wall_S[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_wall_S;
		arena.wall_S[i].proj_matrix = myGraphics.proj_matrix;

		original_x--;
	}

	for (int i = 0; i < size(arena.wall_E); i++) {
		mv_matrix_wall_E =
			glm::translate(glm::vec3(-9.0f, 0.5f, original_z)) *
			glm::mat4(1.0f);
		arena.wall_E[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_wall_E;
		arena.wall_E[i].proj_matrix = myGraphics.proj_matrix;

		mv_matrix_wall_O =
			glm::translate(glm::vec3(9.0f, 0.5f, -original_z)) *
			glm::mat4(1.0f);
		arena.wall_O[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_wall_O;
		arena.wall_O[i].proj_matrix = myGraphics.proj_matrix;

		original_z--;
	}

	t += 0.01f; // increment movement variables

	if (glfwWindowShouldClose(myGraphics.window) == GL_TRUE) quit = true; // If quit by pressing x on window.
}

void renderScene() {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw objects in screen
	myFloor.Draw();
	player.render_character();
	arena.render_arena();





	// Choosing of a new cube to flash
	if (arena.shot_direction == 'v') { // Manage with time
		srand(time(NULL));
		arena.shot_direction = walls[rand() % 4];

		if (arena.shot_direction == 'S' || arena.shot_direction == 'N') th_cube = rand() % 19;
		else th_cube = rand() % 17;
	}

	// Flashing a cube and throw a projectile
	if (frozen == 1500) { // When the break is finished ...

		if (flashing_time < 800) { // Beginning of flashing
			if (flash == 200) {
				arena.color_a_cube(th_cube, glm::vec4(150.0f, 0.0f, 0.0f, 1.0f));
				flash++;
			}
			else if (flash == 400) {
				arena.color_a_cube(th_cube, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
				flash = 0;
			}
			else flash++;

			flashing_time++;
		}
		else { // Flashing is finished and we throw a projectile
			flashing_time = 0;
			frozen = 0;
			flash = 0;
			arena.color_a_cube(th_cube, arena.original_cube_color); // Original color
			arena.shot_direction = 'v';

			// Throw projectile


		}
	}
	else frozen++;
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
