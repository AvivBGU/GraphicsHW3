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
#define CUBE_SIZE 3
using namespace glm;


static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
static const glm::vec3 BLUE = glm::vec3(0, 0, 1);
static const glm::vec3 RED = glm::vec3(1, 0, 0);
static const glm::vec3 GREEN = glm::vec3(0, 1, 0);
static const glm::vec3 YELLOW = glm::vec3(1, 1, 0);
static const glm::vec3 TEAL = glm::vec3(0, 1, 1);
static const glm::vec3 PURPLE = glm::vec3(1, 0, 1);


int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	Vertex vertices[] =
	{	//position, coordinates texture, normal, color
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),BLUE),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),BLUE),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),BLUE),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),BLUE),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),RED),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),RED),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),RED),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),RED),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),GREEN),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),GREEN),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),GREEN),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),GREEN),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),YELLOW),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),YELLOW),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),YELLOW),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),YELLOW),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),TEAL),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),TEAL),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),TEAL),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),TEAL),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),PURPLE),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),PURPLE),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),PURPLE),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),PURPLE)
	};

	unsigned int indices[] = {0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
	Shader shader("./res/shaders/basicShader");
	vec3 pos = vec3(0,0,-5);
	vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
	vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	mat4 P = glm::perspective(60.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	mat4 M = glm::rotate(45.0f,vec3(1,1,1));//glm::mat4(1);
	float relative;
	P = P * glm::lookAt(pos, pos + forward, up);
	mat4 MVP = mat4(1);
	mat4 scale = glm::scale(glm::vec3(0.20));
	glfwSetKeyCallback(display.m_window,key_callback);

	BigCube da_cube(CUBE_SIZE);
	vec3 indexes;
	while(!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);
		shader.Bind();
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		for (auto i = 0; i < CUBE_SIZE; i++)
		{
			for (auto j = 0; j < CUBE_SIZE; j++)
			{
				for (auto k = 0; k < CUBE_SIZE; k++)
				{
					//std::cout << "indexes are: " << x << " " << y << " " << z << std::endl;
					M = glm::rotate(M, 0.01f, up);
					//M = localRotateX * localRotateY * rotate * translate;
					indexes = da_cube.get_index_vec(i, j, k);
					Displayable_object small_cube = da_cube.get_small_cube(indexes.x, indexes.y, indexes.z);
					mat4 small_cube_stuff = small_cube.get_result();
					MVP = P * scale*M*small_cube_stuff;
					shader.Update(MVP, M);
					mesh.Draw();
				}
			}
		}
		//MVP = P * M;
		//shader.Update(MVP,M);
		//MVP = MVP * move_cube;
		//mesh.Draw();
		//shader.Update(MVP,M);
		display.SwapBuffers();
		//Lets rotate some shit.
		glfwPollEvents();
	}

	return 0;
}




