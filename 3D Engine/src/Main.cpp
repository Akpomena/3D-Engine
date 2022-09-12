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

#include "./Model.h"

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

struct PointLightVariables
{
	float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;
};

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

	glm::vec4 lightPosition = { 1.2f, 1.0f, 2.0f, 1.0f };
	glm::vec3 lightColor = glm::vec3(1.0f);

	// Shader

	Shader boxShader("assets/shaders/BasicVertexShader.vert", "assets/shaders/BasicFragShader.frag");
	Shader lightShader("assets/shaders/LightVertexShader.vert", "assets/shaders/LightFragShader.frag");

	// Texture

	Texture container("assets/textures/container2.png", 0);
	Texture containerSpecular("assets/textures/container2_specular.png", 1);
	Texture emission("assets/textures/matrix.jpg", 2);

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
	
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f),
		glm::vec3(1.0f)
	};

	PointLightVariables pointLightVars[4];

	boxShader.Bind();
	boxShader.SetUniformInt("u_Material.diffuse", 0);
	boxShader.SetUniformInt("u_Material.specular", 1);
	boxShader.SetUniformInt("u_Material.emission", 2);

	float spotLightConstant = 1.0f, spotLightLinear = 0.09f, spotLightQuadratic = 0.032f;
	float cutoff = 12.5f, outterCutoff = 17.5f;

	float shininess = 1.0f;

	glm::vec3 dirLightColor = glm::vec3(1.0f);
	glm::vec3 dirLightDirection = { -0.2f, -1.0f, -0.3f };

	glm::vec3 spotLightColor = glm::vec3(1.0f);
	glm::vec4 clearColor = { 0.2f, 0.2f, 0.2f, 0.0f };

	Model backpack("assets/models/backpack/backpack.obj");
	
	while (!glfwWindowShouldClose(window.GetWindow()))
	{

		glm::vec3 diffuseColor = lightColor * 0.5f;
		glm::vec3 ambientColor = lightColor * 0.2f;

		boxShader.Bind();

		// Setting Point Lights Uniforms


		boxShader.SetUniformVec3(("u_PointLight.ambient"), pointLightColors[0] * 0.2f);
		boxShader.SetUniformVec3(("u_PointLight.diffuse"), pointLightColors[0] * 0.5f);
		boxShader.SetUniformVec3(("u_PointLight.specular"), pointLightColors[0]);

		boxShader.SetUniformVec3(("u_PointLight.position"), pointLightPositions[0]);

		boxShader.SetUniformFloat(("u_PointLight.constant"), pointLightVars[0].constant);
		boxShader.SetUniformFloat(("u_PointLight.linear"), pointLightVars[0].linear);
		boxShader.SetUniformFloat(("u_PointLight.quadratic"), pointLightVars[0].quadratic);
	
		//
		boxShader.SetUniformFloat("u_Material.shininess", 128.0f * shininess);

		boxShader.SetUniformVec3("viewPosition", camera.Position);

		boxShader.SetUniformFloat("u_Time", glfwGetTime());

		// Timer

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		int FPS = 1 / deltaTime;


		// Imgui 
		imguiManager.BeginDraw();

		ImGui::Text("Frame Time: %.3fms  FPS: %d", deltaTime * 1000, FPS);
		
		ImGui::ColorEdit4("Clear Color", &clearColor[0]);



		std::string name = "Point Light";
		if (ImGui::CollapsingHeader(name.c_str()))
		{
			ImGui::ColorEdit3("Light Color", &pointLightColors[0][0]);
			ImGui::SliderFloat3("Light Position", (float*)&pointLightPositions[0], -10.0f, 10.0f, "%.3f", 1.0f);

			ImGui::InputFloat("Constant", &pointLightVars[0].constant, 0.01, 1, "% .1f");
			ImGui::InputFloat("Linear", &pointLightVars[0].linear, 0.001, 1, "% .3f");
			ImGui::InputFloat("Quadratic", &pointLightVars[0].quadratic, 0.001, 1, "% .4f");
		}
		
		//ImGui::InputFloat("Shininess", &shininess, 0.01, 1, "% .3f");

		//ImGui::End();
		imguiManager.EndDraw();

		// per-frame time logic
		// --------------------

		perspective = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		boxShader.SetUniformMat4("u_Perspective", perspective);
		
		view = camera.GetViewMatrix();
		boxShader.SetUniformMat4("u_View", view);

	
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader.Bind();

		lightShader.SetUniformMat4("u_Model", model);
		lightShader.SetUniformMat4("u_Perspective", perspective);
		lightShader.SetUniformMat4("u_View", view);
		lightShader.SetUniformVec3("u_Color", pointLightColors[0]);

		boxVertexArray.bind();

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float));

		boxShader.Bind();

		model = glm::mat4(1.0f);
		boxShader.SetUniformMat4("u_Model", model);
		boxShader.SetUniformMat4("u_Perspective", perspective);
		boxShader.SetUniformMat4("u_View", view);

		backpack.Draw(boxShader);

		/*********************/

		/* Test inputs */

		processInput(window.GetWindow());

		/***************/

		window.UpdateWindow();

		/* Rendering goes here*/
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
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