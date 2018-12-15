#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Displayable_object.h"
#include "BigCube.h"
extern BigCube main_cube;
extern mat4 rotatation;
extern mat4 scaler;
double x_pos = 0, y_pos = 0;
int curr_button_pressed = -1;
int is_button_pressed = -1;
//'R' press state for right wall rotation(90 degrees clockwise).
//'L' press state for right wall rotation(90 degrees clockwise).
//'U' press state for up wall rotation(90 degrees clockwise).
//'D' press state for down wall rotation(90 degrees clockwise).
//'B' press state for back wall rotation(90 degrees clockwise).
//'F' press state for front wall rotation(90 degrees clockwise).
//' ' press state for flipping rotation direction(from clockwise to counter clockwise or vise versa).
//'Z' press state : dividing rotation angle by 2; i. 
//'A' press state : multiply rotation angle by 2 (until maximum of 180);

inline void scroll_callback(GLFWwindow *window, double x_axis_offset, double y_axis_offset) {
	std::cout << "Wheel has been activated:" << std::endl;
	std::cout << "X pos: " << x_axis_offset <<"     " << "Y pos" << y_axis_offset << std::endl;
	//-1 enlarges the image, 1 smallifies it.
	if (y_axis_offset < 0) {
		scaler = scaler * glm::scale(vec3(1.05));
	}
	else {
		scaler = scaler * glm::scale(vec3(0.95));
	}
}

inline void pos_callback(GLFWwindow *window, double x_pos_curr, double y_pos_curr) {
	int trice = 0;
	if (is_button_pressed == GLFW_RELEASE) {
		return;
	}
	//Need to check if the position is getting closer to the originial pressed position 
	//or is getting further away.
	if (curr_button_pressed == GLFW_MOUSE_BUTTON_LEFT) {
		rotatation = rotatation * glm::rotate(1.0f, vec3(-std::abs(y_pos_curr) + 
			std::abs(y_pos), -std::abs(x_pos_curr) + std::abs(x_pos), 0));
	}
	if (curr_button_pressed == GLFW_MOUSE_BUTTON_RIGHT) {
	}
}

inline void mouse_callback(GLFWwindow *window, int button_pressed, int action, int mods) {
	char* right = "right";
	char* left = "left";
	char* released = "released";
	char* pressed = "pressed";
	bool pressed_flag = false;
	bool valid_press = true;
	bool single_pos = true;
	char* curr_button = button_pressed == GLFW_MOUSE_BUTTON_RIGHT ? right : left;
	char* curr_action = action == GLFW_PRESS ? pressed : released;
	curr_button_pressed = button_pressed;
	is_button_pressed = action;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	std::cout << "X position is: " << x_pos << std::endl;
	std::cout << "Y position is: " << y_pos << std::endl;
	if (button_pressed == 2) {
		valid_press = false;
	}
	if (valid_press) {
		std::cout << curr_button << " button has been " << curr_action << std::endl;
		pressed_flag = action == 1 ? true : false;
		if (pressed_flag && single_pos) { //Gets the curser current position.
			glfwGetCursorPos(window, &x_pos, &y_pos);
			single_pos = false;
		}
	}
}


inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	char key_pressed = key;
	float change_display_by = 5.0f;
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		return;
	}
	std::cout << "Pressed the key: " << key_pressed << std::endl;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
			glfwSetWindowShouldClose(window,GLFW_TRUE);
		break;
	case GLFW_KEY_R:
		main_cube.rotate_index(vec3(1, 0, 0), 0);
		break;
	case GLFW_KEY_L:
		main_cube.rotate_index(vec3(1, 0, 0), main_cube.get_cube_size() - 1);
		break;
	case GLFW_KEY_U:
		main_cube.rotate_index(vec3(0, 1, 0), main_cube.get_cube_size() - 1);
		break;
	case GLFW_KEY_D:	
		main_cube.rotate_index(vec3(0, 1, 0), 0);
		break;
	case GLFW_KEY_F:
		main_cube.rotate_index(vec3(0, 0, 1), 0);
		break;
	case GLFW_KEY_B:
		main_cube.rotate_index(vec3(0, 0, 1), main_cube.get_cube_size() - 1);
		break;
	
	case GLFW_KEY_SPACE:
		main_cube.change_rotation_direction();
		break;
	case GLFW_KEY_Z:
		main_cube.change_rotation_angle(0.5);
		break;
	case GLFW_KEY_A:
		main_cube.change_rotation_angle(2);
		break;
	case GLFW_KEY_0:
		rotatation = rotatation * glm::rotate(45.0f, vec3(1, 1, 1));
		break;

	default:
		break;
	}
}



