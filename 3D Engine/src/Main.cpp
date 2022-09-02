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
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	
	VertexBuffer boxVertexBuffer(vertices, sizeof(vertices));
	VertexBufferLayout boxBufferLayout;
	boxBufferLayout.push<float>(3);
	boxBufferLayout.push<float>(3);
	boxBufferLayout.push<float>(2);

	VertexArray boxVertexArray;
	boxVertexArray.AddBuffer(boxVertexBuffer, boxBufferLayout);

	// Light Source

	glm::vec3 lightPosition = { 1.2f, 1.0f, 2.0f };
	glm::vec3 lightColor = glm::vec3(1.0f);

	// Shader

	Shader boxShader("assets/shaders/BasicVertexShader.vert", "assets/shaders/BasicFragShader.frag");
	Shader lightShader("assets/shaders/LightVertexShader.vert", "assets/shaders/LightFragShader.frag");

	// Texture

	Texture container("assets/textures/container2.png", 0);
	Texture containerSpecular("assets/textures/container2_specular.png", 1);

	/***************************/

	glm::mat4 perspective;
	glm::mat4 view;

	/***************************/

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
	
	// IMGUI
	

	bool show_demo_window = true;

	float shininess = 1.0f;


	boxShader.Bind();

	boxShader.SetUniformInt("u_Material.diffuse", 0);

	boxShader.SetUniformInt("u_Material.specular", 1);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glm::vec3 diffuseColor = lightColor * 0.5f;
		glm::vec3 ambientColor = lightColor * 0.2f;

		boxShader.Bind();

		boxShader.SetUniformVec3("u_Light.ambient", ambientColor);
		boxShader.SetUniformVec3("u_Light.diffuse", diffuseColor);
		boxShader.SetUniformVec3("u_Light.specular", lightColor);
		boxShader.SetUniformVec3("u_Light.position", lightPosition);

		boxShader.SetUniformFloat("u_Material.shininess", 128.0f * shininess);

		boxShader.SetUniformVec3("viewPosition", camera.Position);

		// Imgui 
		imguiManager.BeginDraw();
		ImGui::Begin("Light Properties");

		ImGui::ColorEdit3("Light Color", &lightColor[0]);
		ImGui::SliderFloat3("Light Position", (float*) & lightPosition, -2.0f, 2.0f, "%.3f", 1.0f);

		ImGui::Begin("Box Properties");

		ImGui::InputFloat("Shininess", &shininess, 0.01, 1, "% .3f");

		ImGui::End();

		ImGui::End();

		imguiManager.EndDraw();

		// per-frame time logic
		// --------------------

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		perspective = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		boxShader.SetUniformMat4("u_Perspective", perspective);
		
		view = camera.GetViewMatrix();
		boxShader.SetUniformMat4("u_View", view);


		glm::mat4 model = glm::mat4(1.0f);
		boxShader.SetUniformMat4("u_Model", model);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));

		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader.Bind();

		lightShader.SetUniformMat4("u_Model", model);
		lightShader.SetUniformMat4("u_Perspective", perspective);
		lightShader.SetUniformMat4("u_View", view);
		lightShader.SetUniformVec3("u_Color", lightColor);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));
		
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