#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "stb_image.h"
#include "gl_utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define GL_LOG_FILE "gl.log"
#include <iostream>
#include <windows.h>

int g_gl_width = 640;
int g_gl_height = 480;
GLFWwindow *g_window = NULL;


float vertices[] = {
	// positions				// colors           // texture coords
	//3
	/*0*/-0.9f, 0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.6f, 0.0f,	// top left
	-0.3f,  0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.9f, 0.0f,	// top right
	-0.3f,  0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.9f, 0.3f, // bottom right
	-0.9f,  0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.6f, 0.3f,	// bottom left
															//4
	/*32*/-0.3f,  0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.3f,	// top left
	0.3f,   0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.3f,	// top right
	0.3f,   0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.6f, // bottom right
	-0.3f,  0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.6f,	// bottom left
															//1
	/*64*/0.3f,   0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.0f,	// top left
	0.9f,   0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.0f,	// top right
	0.9f,   0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.3f, // bottom right
	0.3f,   0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.3f,	// bottom left
															//2
	/*96*/-0.9f,  0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.0f,	// top left
	-0.3f,  0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.0f,	// top right
	-0.3f,  -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.3f, // bottom right
	-0.9f,  -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.3f,	// bottom left
															//8
	/*128*/-0.3f,  0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.6f,	// top left
	0.3f,   0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.6f,	// top right
	0.3f,   -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.9f, // bottom right
	-0.3f,  -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.9f,	// bottom left
															//7
	/*160*/0.3f,   0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.0f, 0.6f,	// top left
	0.9f,   0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.6f,	// top right
	0.9f,   -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.9f, // bottom right
	0.3f,   -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.0f, 0.9f,	// bottom left
															//6
	/*192*/-0.9f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.3f,	// top left
	-0.3f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.9f, 0.3f,	// top right
	-0.3f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.9f, 0.6f, // bottom right
	-0.9f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.6f,	// bottom left
															//5
	/*224*/-0.3f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.3f,	// top left
	0.3f,   -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.3f,	// top right
	0.3f,   -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.6f, // bottom right
	-0.3f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.6f,	// bottom left
															//9
	/*256*/0.3f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5f, 0.5f,	// top left
	0.9f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5F, 0.5f,	// top right
	0.9f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5f, 0.5f, // bottom right
	0.3f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5f, 0.5f	// bottom left
};

float points_square_empty[];

int pos_square;

unsigned int indices[];

int movesCounter;
int lengthLine;
int lengthSquare;

void levelOne();

void levelOne() {

	vertices[] = {
		// positions				// colors           // texture coords
		//3
		/*0*/-0.9f, 0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.6f, 0.0f,	// top left
		-0.3f,  0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.9f, 0.0f,	// top right
		-0.3f,  0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.9f, 0.3f, // bottom right
		-0.9f,  0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.6f, 0.3f,	// bottom left
																//4
		/*32*/-0.3f,  0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.3f,	// top left
		0.3f,   0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.3f,	// top right
		0.3f,   0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.6f, // bottom right
		-0.3f,  0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.6f,	// bottom left
																//1
		/*64*/0.3f,   0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.0f,	// top left
		0.9f,   0.9f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.0f,	// top right
		0.9f,   0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.3f, 0.3f, // bottom right
		0.3f,   0.3f, 0.0f,		1.0f, 0.0f, 0.0f,   0.0f, 0.3f,	// bottom left
																//2
		/*96*/-0.9f,  0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.0f,	// top left
		-0.3f,  0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.0f,	// top right
		-0.3f,  -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.3f, // bottom right
		-0.9f,  -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.3f,	// bottom left
																//8
		/*128*/-0.3f,  0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.6f,	// top left
		0.3f,   0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.6f,	// top right
		0.3f,   -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.9f, // bottom right
		-0.3f,  -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.9f,	// bottom left
																//7
		/*160*/0.3f,   0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.0f, 0.6f,	// top left
		0.9f,   0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.6f,	// top right
		0.9f,   -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.9f, // bottom right
		0.3f,   -0.3f, 0.0f,	1.0f, 0.0f, 0.0f,   0.0f, 0.9f,	// bottom left
																//6
		/*192*/-0.9f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.3f,	// top left
		-0.3f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.9f, 0.3f,	// top right
		-0.3f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.9f, 0.6f, // bottom right
		-0.9f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.6f,	// bottom left
																//5
		/*224*/-0.3f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.3f,	// top left
		0.3f,   -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.3f,	// top right
		0.3f,   -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.6f, 0.6f, // bottom right
		-0.3f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.3f, 0.6f,	// bottom left
																//9
		/*256*/0.3f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5f, 0.5f,	// top left
		0.9f,  -0.3f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5F, 0.5f,	// top right
		0.9f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5f, 0.5f, // bottom right
		0.3f,  -0.9f,  0.0f,	1.0f, 0.0f, 0.0f,   0.5f, 0.5f	// bottom left
	};

	points_square_empty[] = {
		0.3f, -0.3f, 0.0f,
		0.9f, -0.9f, 0.0f

	};

	pos_square = 262;

	indices[] = {
		// 1
		0, 1, 2, // first triangle
		0, 2, 3,  // second triangle

		4, 5, 6, // first triangle
		4, 6, 7,  // second triangle

		8, 9, 10, // first triangle
		8, 10, 11,  // second triangle

		12, 13, 14, // first triangle
		12, 14, 15,  // second triangle

		16, 17, 18, // first triangle
		16, 18, 19,  // second triangle

		20, 21, 22, // first triangle
		20, 22, 23, // second triangle

		24, 25, 26, // first triangle
		24, 26, 27,  // second triangle

		28, 29, 30, // first triangle
		28, 30, 31, // second triangle

		32, 33, 34, // first triangle
		32, 34, 35  // second triangle
	};

	movesCounter = 30;
	lengthLine = 96;
	lengthSquare = 32;
}

int main() {
	restart_gl_log();
	// all the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	start_gl("Texture Mapping");
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable( GL_DEPTH_TEST ); // enable depth-testing
	glDepthFunc( GL_LESS );		 // depth-testing interprets a smaller value as "closer"


	levelOne();

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	char vertex_shader[1024 * 256];
	char fragment_shader[1024 * 256];
	parse_file_into_str( "test_vs.glsl", vertex_shader, 1024 * 256 );
	parse_file_into_str( "test_fs.glsl", fragment_shader, 1024 * 256 );

	GLuint vs = glCreateShader( GL_VERTEX_SHADER );
	const GLchar *p = (const GLchar *)vertex_shader;
	glShaderSource( vs, 1, &p, NULL );
	glCompileShader( vs );

	// check for compile errors
	int params = -1;
	glGetShaderiv( vs, GL_COMPILE_STATUS, &params );
	if ( GL_TRUE != params ) {
		fprintf( stderr, "ERROR: GL shader index %i did not compile\n", vs );
		print_shader_info_log( vs );
		return 1; // or exit or something
	}

	GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
	p = (const GLchar *)fragment_shader;
	glShaderSource( fs, 1, &p, NULL );
	glCompileShader( fs );

	// check for compile errors
	glGetShaderiv( fs, GL_COMPILE_STATUS, &params );
	if ( GL_TRUE != params ) {
		fprintf( stderr, "ERROR: GL shader index %i did not compile\n", fs );
		print_shader_info_log( fs );
		return 1; // or exit or something
	}

	GLuint shader_programme = glCreateProgram();
	glAttachShader( shader_programme, fs );
	glAttachShader( shader_programme, vs );
	glLinkProgram( shader_programme );

	glGetProgramiv( shader_programme, GL_LINK_STATUS, &params );
	if ( GL_TRUE != params ) {
		fprintf( stderr, "ERROR: could not link shader programme GL index %i\n",
						 shader_programme );
		print_programme_info_log( shader_programme );
		return false;
	}

	// load and create a texture
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char *data = stbi_load("cat.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glEnable( GL_CULL_FACE ); // cull face
	glCullFace( GL_BACK );		// cull back face
	glFrontFace( GL_CW );			// GL_CCW for counter clock-wise

	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while ( !glfwWindowShouldClose( g_window ) ) {

		//Sleep(100);

		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//
		// Note: this call is not necessary, but I like to do it anyway before any
		// time that I call glDrawArrays() so I never use the wrong shader programme
		glUseProgram( shader_programme );

		// Note: this call is not necessary, but I like to do it anyway before any
		// time that I call glDrawArrays() so I never use the wrong vertex data
		glBindVertexArray( VAO );
		glDrawElements(GL_TRIANGLES, 54, GL_UNSIGNED_INT, 0);
		// update other events like input handling
		glfwPollEvents();

		ImGui_ImplGlfwGL3_NewFrame();

		// 1. Show a simple window.
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug".
		
		{
			ImGui::Begin("Very first window", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
			ImGui::Text("Movimentos restantes: %i", movesCounter);
			ImGui::End();
		}
		

		/*float square_empty[] = {
			0.3f,  -0.3f,  0.0f,	// top left
			0.9f,  -0.9f,  0.0f,	// bottom right
		};*/

		if (movesCounter < 0) {
			int msgboxID = MessageBox(
				NULL,
					(LPCWSTR)L"\nNão foi dessa vez!",
					(LPCWSTR)L"GAME OVER",
					MB_ICONERROR
				);

			glfwSetWindowShouldClose(g_window, 1);
			return 0;
		}
		if (vertices[6] == 0.0f && vertices[7] == 0.0f
			&& vertices[38] == 0.3f && vertices[39] == 0.0f
			&& vertices[70] == 0.6f && vertices[71] == 0.0f

			&& vertices[102] == 0.0f && vertices[103] == 0.3f
			&& vertices[134] == 0.3f && vertices[135] == 0.3f
			&& vertices[166] == 0.6f && vertices[167] == 0.3f

			&& vertices[198] == 0.0f && vertices[199] == 0.6f
			&& vertices[230] == 0.3f && vertices[231] == 0.6f) {

			vertices[pos_square] = 0.6f;
			vertices[pos_square + 1] = 0.6f;
			vertices[pos_square + 8] = 0.6f;
			vertices[pos_square + 9] = 0.9f;
			vertices[pos_square + 16] = 0.9f;
			vertices[pos_square + 17] = 0.9f;
			vertices[pos_square + 24] = 0.6f;
			vertices[pos_square + 25] = 0.9f;

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// put the stuff we've been drawing onto the display
			glfwSwapBuffers(g_window);

			int msgboxID = MessageBox(
				NULL,
				(LPCWSTR)L"Parabéns\nAgora tente no próximo nível.",
				(LPCWSTR)L"JOGO",
				MB_DEFBUTTON2
			);
			
			glfwSetWindowShouldClose(g_window, 1);

			return 0;
		}

		if ( GLFW_PRESS == glfwGetKey( g_window, GLFW_KEY_ESCAPE ) ) {
			glfwSetWindowShouldClose( g_window, 1 );
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_UP)) {
			if (points_square_empty[4] > -0.9f) {
				--movesCounter;

				points_square_empty[4] -= 0.6f;
				points_square_empty[1] -= 0.6f;


				float p1_x = vertices[pos_square + lengthLine];
				float p1_y = vertices[pos_square + lengthLine + 1];
				float p2_x = vertices[pos_square + lengthLine + 8];
				float p2_y = vertices[pos_square + lengthLine + 9];
				float p3_x = vertices[pos_square + lengthLine + 16];
				float p3_y = vertices[pos_square + lengthLine + 17];
				float p4_x = vertices[pos_square + lengthLine + 24];
				float p4_y = vertices[pos_square + lengthLine + 25];

				vertices[pos_square + lengthLine] = 0.5f;
				vertices[pos_square + lengthLine + 1] = 0.5f;
				vertices[pos_square + lengthLine + 8] = 0.5f;
				vertices[pos_square + lengthLine + 9] = 0.5f;
				vertices[pos_square + lengthLine + 16] = 0.5f;
				vertices[pos_square + lengthLine + 17] = 0.5f;
				vertices[pos_square + lengthLine + 24] = 0.5f;
				vertices[pos_square + lengthLine + 25] = 0.5f;

				vertices[pos_square] = p1_x;
				vertices[pos_square + 1] = p1_y;
				vertices[pos_square + 8] = p2_x;
				vertices[pos_square + 9] = p2_y;
				vertices[pos_square + 16] = p3_x;
				vertices[pos_square + 17] = p3_y;
				vertices[pos_square + 24] = p4_x;
				vertices[pos_square + 25] = p4_y;

				pos_square += 96;

				Sleep(200);
			}
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_DOWN)) {
			if (points_square_empty[1] < 0.9f) {
				--movesCounter;

				points_square_empty[1] += 0.6f;
				points_square_empty[4] += 0.6f;


				float p1_x = vertices[pos_square - lengthLine];
				float p1_y = vertices[pos_square - lengthLine + 1];
				float p2_x = vertices[pos_square - lengthLine + 8];
				float p2_y = vertices[pos_square - lengthLine + 9];
				float p3_x = vertices[pos_square - lengthLine + 16];
				float p3_y = vertices[pos_square - lengthLine + 17];
				float p4_x = vertices[pos_square - lengthLine + 24];
				float p4_y = vertices[pos_square - lengthLine + 25];

				vertices[pos_square - lengthLine] = 0.5f;
				vertices[pos_square - lengthLine + 1] = 0.5f;
				vertices[pos_square - lengthLine + 8] = 0.5f;
				vertices[pos_square - lengthLine + 9] = 0.5f;
				vertices[pos_square - lengthLine + 16] = 0.5f;
				vertices[pos_square - lengthLine + 17] = 0.5f;
				vertices[pos_square - lengthLine + 24] = 0.5f;
				vertices[pos_square - lengthLine + 25] = 0.5f;

				vertices[pos_square ] = p1_x;
				vertices[pos_square + 1] = p1_y;
				vertices[pos_square + 8] = p2_x;
				vertices[pos_square + 9] = p2_y;
				vertices[pos_square + 16] = p3_x;
				vertices[pos_square + 17] = p3_y;
				vertices[pos_square + 24] = p4_x;
				vertices[pos_square + 25] = p4_y;

				pos_square -= 96;

				Sleep(200);
			}
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_LEFT)) {
			if (points_square_empty[3] < 0.9f) {
				--movesCounter;

				points_square_empty[3] += 0.6f;
				points_square_empty[0] += 0.6f;


				float p1_x = vertices[pos_square + lengthSquare];
				float p1_y = vertices[pos_square + lengthSquare + 1];
				float p2_x = vertices[pos_square + lengthSquare + 8];
				float p2_y = vertices[pos_square + lengthSquare + 9];
				float p3_x = vertices[pos_square + lengthSquare + 16];
				float p3_y = vertices[pos_square + lengthSquare + 17];
				float p4_x = vertices[pos_square + lengthSquare + 24];
				float p4_y = vertices[pos_square + lengthSquare + 25];

				vertices[pos_square + lengthSquare] = 0.5f;
				vertices[pos_square + lengthSquare + 1] = 0.5f;
				vertices[pos_square + lengthSquare + 8] = 0.5f;
				vertices[pos_square + lengthSquare + 9] = 0.5f;
				vertices[pos_square + lengthSquare + 16] = 0.5f;
				vertices[pos_square + lengthSquare + 17] = 0.5f;
				vertices[pos_square + lengthSquare + 24] = 0.5f;
				vertices[pos_square + lengthSquare + 25] = 0.5f;

				vertices[pos_square] = p1_x;
				vertices[pos_square + 1] = p1_y;
				vertices[pos_square + 8] = p2_x;
				vertices[pos_square + 9] = p2_y;
				vertices[pos_square + 16] = p3_x;
				vertices[pos_square + 17] = p3_y;
				vertices[pos_square + 24] = p4_x;
				vertices[pos_square + 25] = p4_y;

				pos_square += 32;

				Sleep(200);
			}
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_RIGHT)) {
			if (points_square_empty[0] > -0.9f) {
				--movesCounter;
				
				points_square_empty[0] -= 0.6f;
				points_square_empty[3] -= 0.6f;


				float p1_x = vertices[pos_square - lengthSquare];
				float p1_y = vertices[pos_square - lengthSquare + 1];
				float p2_x = vertices[pos_square - lengthSquare + 8];
				float p2_y = vertices[pos_square - lengthSquare + 9];
				float p3_x = vertices[pos_square - lengthSquare + 16];
				float p3_y = vertices[pos_square - lengthSquare + 17];
				float p4_x = vertices[pos_square - lengthSquare + 24];
				float p4_y = vertices[pos_square - lengthSquare + 25];

				vertices[pos_square - lengthSquare] = 0.5f;
				vertices[pos_square - lengthSquare + 1] = 0.5f;
				vertices[pos_square - lengthSquare + 8] = 0.5f;
				vertices[pos_square - lengthSquare + 9] = 0.5f;
				vertices[pos_square - lengthSquare + 16] = 0.5f;
				vertices[pos_square - lengthSquare + 17] = 0.5f;
				vertices[pos_square - lengthSquare + 24] = 0.5f;
				vertices[pos_square - lengthSquare + 25] = 0.5f;

				vertices[pos_square] = p1_x;
				vertices[pos_square + 1] = p1_y;
				vertices[pos_square + 8] = p2_x;
				vertices[pos_square + 9] = p2_y;
				vertices[pos_square + 16] = p3_x;
				vertices[pos_square + 17] = p3_y;
				vertices[pos_square + 24] = p4_x;
				vertices[pos_square + 25] = p4_y;

				pos_square -= 32;

				Sleep(200);
			}
		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		ImGui::Render();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(g_window);
		
	}

	ImGui_ImplGlfwGL3_Shutdown();
	// close GL context and any other GLFW resources
	glfwTerminate();
	return 0;
}
