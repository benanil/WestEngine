#include "WestEngine.h"
#include "Editor.h"
#include "Camera.h"
#include "Common.h"
#include <Shader.h>
#include <Input.h>
#include <Mesh.h>

#include <iostream>
#include "GLFW/glfw3.h"
#include "glad.h"
#include "SOIL/SOIL.h";
#include <filesystem>
#include <Texture.h>

// #include "assimp/scene.h"
// #include <assimp/Importer.hpp>  
// #include <assimp/scene.h>       
// #include <assimp/postprocess.h> 

namespace WestEngine
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void MainInput(GLFWwindow* window);

	void Engine::Run()
	{
		if (glfwInit() == 0)  std::cout << "glfw failed" << std::endl;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(900, 900, "West Engine", NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		//Creates Imgui functions
		Editor::Create(window);
		Input::Initialize(window);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        
		Shader shader(std::string("Assets\\First.vert"), std::string("Assets\\First.frag"));

        float vertices[] = {
             1,  1,  0,  0,  // top right
             1, -1,  0,  1,  // bottom right
            -1, -1,  1,  1,  // bottom left
            -1,  1,  1,  0  // top left 
        };

        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };

        unsigned int VBO, VAO, EBO, TEBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
		glGenBuffers(1, &TEBO);
		glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(float) * 4, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, TEBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		Texture texture(false, "texture.jpg");

		double newTime = 0, oldTime = 0;

		while (!glfwWindowShouldClose(window))
		{
			oldTime = newTime;
			newTime = glfwGetTime();

            Editor::Begin();

			MainInput(window);
			
            Time::Tick(newTime - oldTime);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            // draw our first triangle
            glUseProgram(shader.shaderProgram);
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			glActiveTexture(GL_TEXTURE0);
			texture.Bind();
			//glDrawArrays(GL_TRIANGLES, 0, 6);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            glUseProgram(0);

			Editor::Render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		Editor::Destroy();

		glfwTerminate();
		glfwDestroyWindow(window);
	}
	
	void MainInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}