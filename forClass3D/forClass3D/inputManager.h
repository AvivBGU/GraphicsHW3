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
//'R' press state for right wall rotation(90 degrees clockwise).
//'L' press state for right wall rotation(90 degrees clockwise).
//'U' press state for up wall rotation(90 degrees clockwise).
//'D' press state for down wall rotation(90 degrees clockwise).
//'B' press state for back wall rotation(90 degrees clockwise).
//'F' press state for front wall rotation(90 degrees clockwise).
//' ' press state for flipping rotation direction(from clockwise to counter clockwise or vise versa).
//'Z' press state : dividing rotation angle by 2; i. 
//'A' press state : multiply rotation angle by 2 (until maximum of 180);


inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	char key_pressed = key;
	vec3*** index_matrixesseses;
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
	case GLFW_KEY_L:
		main_cube.rotate_index(vec3(1, 0, 0), 0);
		break;
	case GLFW_KEY_R:
		/*std::cout << "Before changing the indexes" << std::endl;
		index_matrixesseses = main_cube.get_index_matrix();
		for (auto i = 0; i < main_cube.get_cube_size(); i++) {
			std::cout << "Current wall: " << i << std::endl;
			for (auto j = 0; j < main_cube.get_cube_size(); j++) {
				std::cout << "Current row: " << j << std::endl;
				for (auto k = 0; k < main_cube.get_cube_size(); k++) {
					std::cout << "Current vector: " << index_matrixesseses[i][j][k].x << "   "
						<< index_matrixesseses[i][j][k].y << "   " << index_matrixesseses[i][j][k].z << std::endl;
				}
			}
		}*/
		main_cube.rotate_index(vec3(1, 0, 0), main_cube.get_cube_size()-1);
		/*index_matrixesseses = main_cube.get_index_matrix();
		for (auto i = 0; i < main_cube.get_cube_size(); i++) {
			std::cout << "Current wall: " << i << std::endl;
			for (auto j = 0; j < main_cube.get_cube_size(); j++) {
				std::cout << "Current row: " << j << std::endl;
				for (auto k = 0; k < main_cube.get_cube_size(); k++) {
					std::cout << "Current vector: " << index_matrixesseses[i][j][k].x << "   "
						<< index_matrixesseses[i][j][k].y << "   " << index_matrixesseses[i][j][k].z << std::endl;
				}
			}
		}*/
		break;
	case GLFW_KEY_U:
		main_cube.rotate_index(vec3(0, 1, 0), main_cube.get_cube_size() - 1);
		break;
	case GLFW_KEY_D:	
		main_cube.rotate_index(vec3(0, 1, 0), 0);
		break;
	case GLFW_KEY_B:
		main_cube.rotate_index(vec3(0, 0, 1), 0);
		break;
	case GLFW_KEY_F:
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
	default:
		break;
	}
}



