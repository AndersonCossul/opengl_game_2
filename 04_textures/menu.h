#ifndef MENU_H
#define MENU_H

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

int getLevelByMenu()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "ImGui OpenGL3 example", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	ImGui_ImplGlfwGL3_Init(window, true);

	int level = -1;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (level < 1)
	{
		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();

		{
			ImGui::Begin("Bem Vindo", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
			ImGui::Text("Selecione a dificuldade:");

			if (ImGui::Button("Nivel Facil"))
			{
				level = 1;
			}

			if (ImGui::Button("Nivel Medio"))
			{
				level = 2;
			}

			if (ImGui::Button("Nivel Dificil"))
			{
				level = 3;
			}
			ImGui::End();
		}

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	ImGui_ImplGlfwGL3_Shutdown();
	glfwDestroyWindow(window);
	//glfwTerminate();

	return level;
}

#endif
