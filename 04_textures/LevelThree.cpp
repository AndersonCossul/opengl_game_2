#include "LevelThree.h"

#include "Level.h"

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

int runLevelThree() {
	restart_gl_log();
	// all the GLFW and GLEW start-up code is moved to here in gl_utils.cpp
	start_gl("Texture Mapping");
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);		 // depth-testing interprets a smaller value as "closer"

	float textureArray[25][8] = {
		//1
		0.0f,	0.0f,
		0.2f,	0.0f,
		0.2f,	0.2f,
		0.0f,	0.2f,

		0.2f,	0.0f,
		0.4f,	0.0f,
		0.4f,	0.2f,
		0.2f,	0.2f,

		0.4f,	0.0f,
		0.6f,	0.0f,
		0.6f,	0.2f,
		0.4f,	0.2f,

		0.6f,	0.0f,
		0.8f,	0.0f,
		0.8f,	0.2f,
		0.6f,	0.2f,

		//new
		0.8f,	0.0f,
		1.0f,	0.0f,
		1.0f,	0.2f,
		0.8f,	0.2f,
		//2
		0.0f,	0.2f,
		0.2f,	0.2f,
		0.2f,	0.4f,
		0.0f,	0.4f,

		0.2f,	0.2f,
		0.4f,	0.2f,
		0.4f,	0.4f,
		0.2f,	0.4f,

		0.4f,	0.2f,
		0.6f,	0.2f,
		0.6f,	0.4f,
		0.4f,	0.4f,

		0.6f,	0.2f,
		0.8f,	0.2f,
		0.8f,	0.4f,
		0.6f,	0.4f,

		//new
		0.8f,	0.2f,
		1.0f,	0.2f,
		1.0f,	0.4f,
		0.8f,	0.4f,
		//3
		0.0f,	0.4f,
		0.2f,	0.4f,
		0.2f,	0.6f,
		0.0f,	0.6f,

		0.2f,	0.4f,
		0.4f,	0.4f,
		0.4f,	0.6f,
		0.2f,	0.6f,

		0.4f,	0.4f,
		0.6f,	0.4f,
		0.6f,	0.6f,
		0.4f,	0.6f,

		0.6f,	0.4f,
		0.8f,	0.4f,
		0.8f,	0.6f,
		0.6f,	0.6f,

		//new
		0.8f,	0.4f,
		1.0f,	0.4f,
		1.0f,	0.6f,
		0.8f,	0.6f,
		//4
		0.0f,	0.6f,
		0.2f,	0.6f,
		0.2f,	0.8f,
		0.0f,	0.8f,

		0.2f,	0.6f,
		0.4f,	0.6f,
		0.4f,	0.8f,
		0.2f,	0.8f,

		0.4f,	0.6f,
		0.6f,	0.6f,
		0.6f,	0.8f,
		0.4f,	0.8f,

		//new
		0.6f,	0.6f,
		0.8f,	0.6f,
		0.8f,	0.8f,
		0.6f,	0.8f,

		//new
		0.8f,	0.6f,
		1.0f,	0.6f,
		1.0f,	0.8f,
		0.8f,	0.8f,
		//5
		0.0f,	0.8f,
		0.2f,	0.8f,
		0.2f,	1.0f,
		0.0f,	1.0f,

		0.2f,	0.8f,
		0.4f,	0.8f,
		0.4f,	1.0f,
		0.2f,	1.0f,

		0.4f,	0.8f,
		0.6f,	0.8f,
		0.6f,	1.0f,
		0.4f,	1.0f,

		//new
		0.6f,	0.8f,
		0.8f,	0.8f,
		0.8f,	1.0f,
		0.6f,	1.0f,

		//new
		0.5f,	0.5f,
		0.5f,	0.5f,
		0.5f,	0.5f,
		0.5f,	0.5f,
	};

	float vertices[] = {
		// positions				// colors           // texture coords
		// Linha 1
		//1
		-1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[10][0], textureArray[10][1],	// top left
		-0.6f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[10][2], textureArray[10][3],	// top right
		-0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[10][4], textureArray[10][5],	// bottom right
		-1.0f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[10][6], textureArray[10][7],	// bottom left
		//2
		-0.6f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[7][0], textureArray[7][1],	// top left
		-0.2f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[7][2], textureArray[7][3],	// top right
		-0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[7][4], textureArray[7][5],	// bottom right
		-0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[7][6], textureArray[7][7],	// bottom left
		//3
		-0.2f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[8][0], textureArray[8][1],	// top left
		0.2f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[8][2], textureArray[8][3],	// top right
		0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[8][4], textureArray[8][5],	// bottom right
		-0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[8][6], textureArray[8][7],	// bottom left
		//4
		0.2f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[0][0], textureArray[0][1],	// top left
		0.6f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[0][2], textureArray[0][3],	// top right
		0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[0][4], textureArray[0][5],	// bottom right
		0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[0][6], textureArray[0][7],	// bottom left
		//5
		0.6f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[23][0], textureArray[23][1],	// top left
		1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[23][2], textureArray[23][3],	// top right
		1.0f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[23][4], textureArray[23][5],	// bottom right
		0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[23][6], textureArray[23][7],	// bottom left
		// Linha 2
		//1
		-1.0f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[3][0], textureArray[3][1],	// top left
		-0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[3][2], textureArray[3][3],	// top right
		-0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[3][4], textureArray[3][5],	// bottom right
		-1.0f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[3][6], textureArray[3][7],	// bottom left
		//2
		-0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[6][0], textureArray[6][1],	// top left
		-0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[6][2], textureArray[6][3],	// top right
		-0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[6][4], textureArray[6][5],	// bottom right
		-0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[6][6], textureArray[6][7],	// bottom left
		//3
		-0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[1][0], textureArray[1][1],	// top left
		0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[1][2], textureArray[1][3],	// top right
		0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[1][4], textureArray[1][5],	// bottom right
		-0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[1][6], textureArray[1][7],	// bottom left
		//4
		0.2f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[4][0], textureArray[4][1],	// top left
		0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[4][2], textureArray[4][3],	// top right
		0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[4][4], textureArray[4][5],	// bottom right
		0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[4][6], textureArray[4][7],	// bottom left
		//5
		0.6f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[21][0], textureArray[21][1],	// top left
		1.0f, 0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[21][2], textureArray[21][3],	// top right
		1.0f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[21][4], textureArray[21][5],	// bottom right
		0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[21][6], textureArray[21][7],	// bottom left
		// Linha 3
		//1
		-1.0f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[13][0], textureArray[13][1],	// top left
		-0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[13][2], textureArray[13][3],	// top right
		-0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[13][4], textureArray[13][5],	// bottom right
		-1.0f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[13][6], textureArray[13][7],	// bottom left
		//2
		-0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[2][0], textureArray[2][1],	// top left
		-0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[2][2], textureArray[2][3],	// top right
		-0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[2][4], textureArray[2][5],	// bottom right
		-0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[2][6], textureArray[2][7],	// bottom left
		//3
		-0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[12][0], textureArray[12][1],	// top left
		0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[12][2], textureArray[12][3],	// top right
		0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[12][4], textureArray[12][5],	// bottom right
		-0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[12][6], textureArray[12][7],	// bottom left
		//4
		0.2f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[14][0], textureArray[14][1],	// top left
		0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[14][2], textureArray[14][3],	// top right
		0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[14][4], textureArray[14][5],	// bottom right
		0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[14][6], textureArray[14][7],	// bottom left
		//5
		0.6f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[20][0], textureArray[20][1],	// top left
		1.0f, 0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[20][2], textureArray[20][3],	// top right
		1.0f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[20][4], textureArray[20][5],	// bottom right
		0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[20][6], textureArray[20][7],	// bottom left
		// Linha 4
		//1
		-1.0f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[5][0], textureArray[5][1],	// top left
		-0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[5][2], textureArray[5][3],	// top right
		-0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[5][4], textureArray[5][5],	// bottom right
		-1.0f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[5][6], textureArray[5][7],	// bottom left
		//2
		-0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[11][0], textureArray[11][1],	// top left
		-0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[11][2], textureArray[11][3],	// top right
		-0.2f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[11][4], textureArray[11][5],	// bottom right
		-0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[11][6], textureArray[11][7],	// bottom left
		//3
		-0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[9][0], textureArray[9][1],	// top left
		0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[9][2], textureArray[9][3],	// top right
		0.2f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[9][4], textureArray[9][5],	// bottom right
		-0.2f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[9][6], textureArray[9][7],	// bottom left
		//4
		0.2f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[15][0], textureArray[15][1],	// top left
		0.6f, -0.2f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[15][2], textureArray[15][3],	// top right
		0.6f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[15][4], textureArray[15][5],	// bottom right
		0.2f, -0.6f, 0.0f,	1.0f, 0.0f, 0.0f, textureArray[15][6], textureArray[15][7],	// bottom left
		//5
		0.6f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[22][0], textureArray[22][1],	// top left
		1.0f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[22][2], textureArray[22][3],	// top right
		1.0f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[22][4], textureArray[22][5],	// bottom right
		0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[22][6], textureArray[22][7],	// bottom left
		// Linha 5
		//1
		-1.0f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][0], textureArray[18][1],	// top left
		-0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][2], textureArray[18][3],	// top right
		-0.6f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][4], textureArray[18][5],	// bottom right
		-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][6], textureArray[18][7],	// bottom left
		//2
		-0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[16][0], textureArray[16][1],	// top left
		-0.2f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[16][2], textureArray[16][3],	// top right
		-0.2f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[16][4], textureArray[16][5],	// bottom right
		-0.6f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[16][6], textureArray[16][7],	// bottom left
		//3
		-0.2f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][0], textureArray[18][1],	// top left
		0.2f,  -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][2], textureArray[18][3],	// top right
		0.2f,  -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][4], textureArray[18][5],	// bottom right
		-0.2f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[18][6], textureArray[18][7],	// bottom left
		//4
		0.2f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[17][0], textureArray[17][1],	// top left
		0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[17][2], textureArray[17][3],	// top right
		0.6f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[17][4], textureArray[17][5],	// bottom right
		0.2f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[17][6], textureArray[17][7],	// bottom left
		//5
		0.6f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[24][0], textureArray[24][1],	// top left
		1.0f, -0.6f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[24][2], textureArray[24][3],	// top right
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[24][4], textureArray[24][5],	// bottom right
		0.6f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, textureArray[24][6], textureArray[24][7],	// bottom left
	};

	float points_square_empty[] = {
		0.6f, -0.6f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	int pos_square = 774;

	int indices[] = {
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
		32, 34, 35, // second triangle

		36, 37, 38, // first triangle
		36, 38, 39, // second triangle

		40, 41, 42, // first triangle
		40, 42, 43, // second triangle

		44, 45, 46, // first triangle
		44, 46, 47, // second triangle

		48, 49, 50, // first triangle
		48, 50, 51, // second triangle

		52, 53, 54, // first triangle
		52, 54, 55, // second triangle

		56, 57, 58, // first triangle
		56, 58, 59, // second triangle

		60, 61, 62, // first triangle
		60, 62, 63, // second triangle

		64, 65, 66, // first triangle
		64, 66, 67, // second triangle

		68, 69, 70, // first triangle
		68, 70, 71, // second triangle

		72, 73, 74, // first triangle
		72, 74, 75, // second triangle

		76, 77, 78, // first triangle
		76, 78, 79, // second triangle

		80, 81, 82, // first triangle
		80, 82, 83, // second triangle

		84, 85, 86, // first triangle
		84, 86, 87, // second triangle

		88, 89, 90, // first triangle
		88, 90, 91, // second triangle

		92, 93, 94, // first triangle
		92, 94, 95, // second triangle

		96, 97, 98, // first triangle
		96, 98, 99, // second triangle
	};

	int movesCounter = 400;
	int lengthLine = 160;
	int lengthSquare = 32;

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
	parse_file_into_str("test_vs.glsl", vertex_shader, 1024 * 256);
	parse_file_into_str("test_fs.glsl", fragment_shader, 1024 * 256);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *p = (const GLchar *)vertex_shader;
	glShaderSource(vs, 1, &p, NULL);
	glCompileShader(vs);

	// check for compile errors
	int params = -1;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", vs);
		print_shader_info_log(vs);
		return 1; // or exit or something
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	p = (const GLchar *)fragment_shader;
	glShaderSource(fs, 1, &p, NULL);
	glCompileShader(fs);

	// check for compile errors
	glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: GL shader index %i did not compile\n", fs);
		print_shader_info_log(fs);
		return 1; // or exit or something
	}

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glGetProgramiv(shader_programme, GL_LINK_STATUS, &params);
	if (GL_TRUE != params) {
		fprintf(stderr, "ERROR: could not link shader programme GL index %i\n",
			shader_programme);
		print_programme_info_log(shader_programme);
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

	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK);		// cull back face
	glFrontFace(GL_CW);			// GL_CCW for counter clock-wise

	bool show_test_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(g_window)) {

		//Sleep(100);

		// wipe the drawing surface clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//
		// Note: this call is not necessary, but I like to do it anyway before any
		// time that I call glDrawArrays() so I never use the wrong shader programme
		glUseProgram(shader_programme);

		// Note: this call is not necessary, but I like to do it anyway before any
		// time that I call glDrawArrays() so I never use the wrong vertex data
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 150, GL_UNSIGNED_INT, 0);
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
		if (vertices[6] == textureArray[0][0] && vertices[7] == textureArray[0][1]
			&& vertices[38] == textureArray[1][0] && vertices[39] == textureArray[1][1]
			&& vertices[70] == textureArray[2][0] && vertices[71] == textureArray[2][1]
			&& vertices[102] == textureArray[3][0] && vertices[103] == textureArray[3][1]
			&& vertices[134] == textureArray[4][0] && vertices[135] == textureArray[4][1]
			
			&& vertices[166] == textureArray[5][0] && vertices[167] == textureArray[5][1]
			&& vertices[198] == textureArray[6][0] && vertices[199] == textureArray[6][1]
			&& vertices[230] == textureArray[7][0] && vertices[231] == textureArray[7][1]
			&& vertices[262] == textureArray[8][0] && vertices[263] == textureArray[8][1]
			&& vertices[294] == textureArray[9][0] && vertices[295] == textureArray[9][1]

			&& vertices[326] == textureArray[10][0] && vertices[327] == textureArray[10][1]
			&& vertices[358] == textureArray[11][0] && vertices[359] == textureArray[11][1]
			&& vertices[390] == textureArray[12][0] && vertices[391] == textureArray[12][1]
			&& vertices[422] == textureArray[13][0] && vertices[423] == textureArray[13][1]
			&& vertices[454] == textureArray[14][0] && vertices[455] == textureArray[14][1]

			&& vertices[486] == textureArray[15][0] && vertices[487] == textureArray[15][1]
			&& vertices[518] == textureArray[16][0] && vertices[519] == textureArray[16][1]
			&& vertices[550] == textureArray[17][0] && vertices[551] == textureArray[17][1]
			&& vertices[582] == textureArray[18][0] && vertices[583] == textureArray[18][1]
			&& vertices[614] == textureArray[19][0] && vertices[615] == textureArray[19][1]

			&& vertices[646] == textureArray[20][0] && vertices[647] == textureArray[20][1]
			&& vertices[678] == textureArray[21][0] && vertices[679] == textureArray[21][1]
			&& vertices[710] == textureArray[22][0] && vertices[711] == textureArray[22][1]
			&& vertices[742] == textureArray[23][0] && vertices[743] == textureArray[23][1]

			) {

			vertices[pos_square] = 0.8;
			vertices[pos_square + 1] = 0.8f;
			vertices[pos_square + 8] = 0.8f;
			vertices[pos_square + 9] = 1.0f;
			vertices[pos_square + 16] = 1.0f;
			vertices[pos_square + 17] = 1.0f;
			vertices[pos_square + 24] = 0.8f;
			vertices[pos_square + 25] = 1.0f;

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

		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(g_window, 1);
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_UP)) {
			if (points_square_empty[4] > -1.0f) {
				--movesCounter;

				points_square_empty[4] -= 0.5f;
				points_square_empty[1] -= 0.5f;


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

				pos_square += lengthLine;

				Sleep(200);
			}
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_DOWN)) {
			if (points_square_empty[1] < 1.0f) {
				--movesCounter;

				points_square_empty[1] += 0.5f;
				points_square_empty[4] += 0.5f;


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

				vertices[pos_square] = p1_x;
				vertices[pos_square + 1] = p1_y;
				vertices[pos_square + 8] = p2_x;
				vertices[pos_square + 9] = p2_y;
				vertices[pos_square + 16] = p3_x;
				vertices[pos_square + 17] = p3_y;
				vertices[pos_square + 24] = p4_x;
				vertices[pos_square + 25] = p4_y;

				pos_square -= lengthLine;

				Sleep(200);
			}
		}
		if (GLFW_PRESS == glfwGetKey(g_window, GLFW_KEY_LEFT)) {
			if (points_square_empty[3] < 1.0f) {
				--movesCounter;

				points_square_empty[3] += 0.5f;
				points_square_empty[0] += 0.5f;


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
			if (points_square_empty[0] > -1.0f) {
				--movesCounter;

				points_square_empty[0] -= 0.5f;
				points_square_empty[3] -= 0.5f;


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

/*
LevelThree::LevelThree()
{
}


LevelThree::~LevelThree()
{
}
*/
