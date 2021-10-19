#include "WestEngine.h"
#include <iostream>
#include "GLFW/glfw3.h"
#include "glad.h"
#include "glm/glm.hpp"
#include "imgui/imgui.h"
#include <vector>

namespace WestEngine
{
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void MainInput(GLFWwindow* window);
    static void FocusCallback(GLFWwindow* window, int enter);
    static void MainEditor();

	int Engine::WindowWidth = 1200;
	int Engine::WindowHeight = 720;
    Event  Engine::OnUpdate;
    Event  Engine::OnEditor;
    Eventi Engine::OnFocus;
    
    static Camera SceneCamera;

    void Engine::Run()
	{
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        // glfw window creation
        GLFWwindow* window = glfwCreateWindow(Engine::WindowWidth, Engine::WindowHeight, "West Engine", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        // initialize callbacks
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetWindowFocusCallback(window, FocusCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to initialize GLAD" << std::endl;

        glEnable(GL_DEPTH_TEST);

        Editor::Create(window);
        Input::Initialize(window);
        Device::Create();
        Editor::AddOnEditor(MainEditor);

        Shader ourShader("First.vert", "First.frag");
        ourShader.Bind();
        glm::mat4 model(1.0f);
        model = glm::rotate(model, -1.57f, glm::vec3(1.0f, 0.0f, 0.0f));
        ourShader.setMat4("model", model);

        Texture texture(true, "map_Base_Colorenyeni.png");
        
        int meshCount = 0;
        Mesh* mesh = MeshLoader::Load(Helper::AssetsPath().append("map.fbx").u8string(), meshCount);

        SceneCamera = Camera(glm::vec3(0,0,0));

        float currentTime = 0, lastTime = 0;

        // main loop
        while (!glfwWindowShouldClose(window))
        {
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_SCISSOR_TEST);
            
            lastTime = currentTime;
            currentTime = (float)glfwGetTime();

            Editor::Begin();
            Time::Tick(currentTime - lastTime);

            MainInput(window);
            SceneCamera.Update();

            OnUpdate.Invoke();
            
            // render
            Renderer::Render(mesh, ourShader);
            
            Editor::Render();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
	}

    float Engine::sunAngle = 0;
    ShaderProperties Engine::properties = ShaderProperties();

    void MainEditor()
    {
        ImGui::Begin("Material Edit");
        ImGui::DragFloat("Sun Angle", &Engine::sunAngle);
        
        ImGui::DragFloat ("metallic"       , &Engine::properties.metalic   , .1f, 0, 1);
        ImGui::DragFloat ("roughness"      , &Engine::properties.roughness , .1f, 0, 1);
        ImGui::DragFloat ("specValue"      , &Engine::properties.specValue , .1f, 0, 5);
        ImGui::ColorEdit3("sunColor "      , &Engine::properties.sunColor.x );
        ImGui::ColorEdit3("ambientColor"   , &Engine::properties.ambientColor.x);
        ImGui::DragFloat ("ambientStrength", &Engine::properties.ambientStrength, .1f, 0, 1);

        ImGui::End();
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Input::MouseCallback(window, xpos, ypos);
        // std::cout << "glfw: " << " " << xpos << " " << ypos << std::endl;
        // camera.ProcessMouseMovement();
    }

    void FocusCallback(GLFWwindow* window, int enter) {
        Engine::OnFocus.Invoke(enter);
    }

    void MainInput(GLFWwindow* window) {

	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		Engine::WindowWidth = width;
		Engine::WindowHeight = height;
		glViewport(0, 0, width, height);
	}
}

