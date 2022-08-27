#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "./Shader.h"
#include "./Camera.h"
#include "./Texture.h"

#include <imgui.h>

#include "./ImguiManager.h"

#include "./Events/Event.h"
#include "./Events/ApplicationEvent.h"
#include "./Events/KeyEvent.h"
#include "./Events/MouseEvent.h"

#include "glad/glad.h"
#include "./Window.h"

#include "./VertexArray.h"
#include "./VertexBuffer.h"
#include "./VertexBufferLayout.h"
#include "./IndexBuffer.h"

void eventHandler(Event& e);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouseMove = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("3D Engine", SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
	window.SetEventCallback(eventHandler);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
		return -1;
	}

	ImguiManager imguiManager;
	imguiManager.init(window.GetWindow());
	

	/* Opengl Setup */

	float vertices[] = {

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

	};

	unsigned int indices[] = {
		// Front face
		0, 1, 2,
		2, 3, 0,

		// Back face
		4, 5, 6,
		6, 7, 4,

		// Right Face
		1, 5, 6,
		6, 2, 1,

		// Left Face
		0, 4, 7,
		7, 3, 0,

		// Top Face
		0, 1, 5,
		5, 4, 0,

		// Bottom Face
		3, 7, 6,
		6, 2, 3

	};

	
	IndexBuffer indexBuffer(indices, sizeof(indices));
	VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	VertexBufferLayout bufferLayout;
	bufferLayout.push<float>(3);
	bufferLayout.push<float>(2);

	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, bufferLayout);


	///shader

	Shader shader("assets/shaders/BasicVertexShader.vert", "assets/shaders/BasicFragShader.frag");


	/***************************/

	glm::mat4 perspective;
	glm::mat4 view;

	/***************************/

	// Textures

	/***************************/

	Texture box("assets/textures/container.jpg", 0);

	Texture awesomeface("assets/textures/awesomeface.png", 1);

	shader.Bind();

	shader.SetUniform1i("u_Texture0", 0);
	shader.SetUniform1i("u_Texture1", 1);
	
	/***************************/

	glm::vec3 positions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	
	// IMGUI
	

	bool show_demo_window = true;

	while (!glfwWindowShouldClose(window.GetWindow()))
	{

		// Imgui 
		imguiManager.BeginDraw();
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		imguiManager.EndDraw();

		// per-frame time logic
		// --------------------

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		perspective = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		shader.SetUniformMat4("u_Perspective", perspective);
		
		view = camera.GetViewMatrix();
		shader.SetUniformMat4("u_View", view);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), positions[i]);
			//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.7f, 0.5f, 1.0f));
			shader.SetUniformMat4("u_Model", model);			
	
			//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));
		}

		
		/*********************/

		/* Test inputs */

		processInput(window.GetWindow());

		/***************/

		window.UpdateWindow();

		/* Rendering goes here*/
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	window.ShutDown();

	return 0;
}

void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

}


void eventHandler(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent event)
		{
			if (event.GetKeyCode() ==  GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window.GetWindow(), true);

			if (event.GetKeyCode() == GLFW_KEY_ENTER)
			{
				firstMouse = true;
				window.enableCursor(mouseMove);
				mouseMove = !mouseMove;
			}

			return true;
		});

	dispatcher.Dispatch<MouseScrolledEvent>([](MouseScrolledEvent event)
		{
			camera.ProcessMouseScroll(static_cast<float>(event.GetYOffset() ));
			return true;
		});

	dispatcher.Dispatch<MouseMovedEvent>([](MouseMovedEvent event)
		{
			float xpos = static_cast<float>(event.GetX());
			float ypos = static_cast<float>(event.GetY());

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			if(mouseMove)
				camera.ProcessMouseMovement(xoffset, yoffset);

			return true;
		});
}