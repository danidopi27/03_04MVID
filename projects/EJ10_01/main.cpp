/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 10_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Febrero 2020
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
//--------------------------------------LIBRER�AS--------------------------------------//
#include <glad/glad.h>						// Librería de manejo de GLAD
#include <GLFW/glfw3.h>						// Librería de manejo de GLFW
#include <glm/gtc/matrix_transform.hpp>		// Librería de transformaci�n de matrices

#include "engine/camera.hpp"				// Librería de manejo de c�mara
#include "engine/geometry/cube.hpp"			// Librería de manejo de geometr�a cubo
#include "engine/input.hpp"					// Librería de manejo de inputs
#include "engine/shader.hpp"				// Librería de manejo de shaders
#include "engine/texture.hpp"				// Librería de manejo de texturas
#include "engine/window.hpp"				// Librería de manejo de ventanas
#include "engine/geometry/sphere.hpp"		// Librería de manejo de geometría esfera
#include "engine/geometry/quad.hpp"			// Librería de manejo de geometría quad
#include "engine/geometry/teapot.hpp"		// Librería de manejo de geometría tetera
#include "engine/model.hpp"					// Librería de manejo de modelos

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definici�n de la c�mara
glm::vec3 lightPos(0.0f, 2.0f, 0.0f);			// Posición de la luz
glm::vec3 lightDir(-1.0f, -1.0f, -1.0f);		// Dirección de la luz

glm::vec3 pointLightPositions[] = {
	glm::vec3(4.0f, 2.0f, 0.0f),
	glm::vec3(-4.0f, 2.0f, 0.0f)
};

glm::vec3 spotLightPositions[] = {
	glm::vec3(0.0f, 2.0f, 4.0f),
	glm::vec3(0.0f, 2.0f, -4.0f)
};

float lastFrame = 0.0f;							// Variable de �ltimo frame
float lastX, lastY;								// Variable de �ltima coordenada x, y
bool firstMouse = true;							// Variable de primer movimiento de rat�n
//----------------------------------------VARIABLES----------------------------------------//

//----------------------------------------FUNCI�N HANDLEINPUT----------------------------------------//
void handleInput(float dt) {
	// Funci�n que maneja las entradas

	Input* input = Input::instance();								// Objeto input

	// Si la tecla W est� pulsada
	if (input->isKeyPressed(GLFW_KEY_W)) {
		camera.handleKeyboard(Camera::Movement::Forward, dt);		// Movimiento hacia adelante
	}
	// Si la tecla S est� pulsada
	if (input->isKeyPressed(GLFW_KEY_S)) {
		camera.handleKeyboard(Camera::Movement::Backward, dt);		// Movimiento hacia atr�s
	}
	// Si la tecla A est� pulsada
	if (input->isKeyPressed(GLFW_KEY_A)) {
		camera.handleKeyboard(Camera::Movement::Left, dt);			// Movimiento hacia la izquierda
	}
	// Si la tecla D est� pulsada
	if (input->isKeyPressed(GLFW_KEY_D)) {
		camera.handleKeyboard(Camera::Movement::Right, dt);			// Movimiento hacia la derecha
	}
}
//----------------------------------------FUNCI�N HANDLEINPUT----------------------------------------//

//----------------------------------FUNCI�N ONKEYPRESS----------------------------------//
void onKeyPress(int key, int action) {
	// Funci�n que controla las pulsaciones de teclas

	// Si se pulsa la tecla Q
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		Window::instance()->setCaptureMode(true);		// Se pone el modo captura ON
	}
	// Si se pulsa la tecla E
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		Window::instance()->setCaptureMode(false);		// Se pone el modo captura OFF
	}
}
//----------------------------------FUNCI�N ONKEYPRESS----------------------------------//

//----------------------------------------FUNCI�N ONMOUSEMOVED----------------------------------------//
void onMouseMoved(float x, float y) {
	// Funci�n que controla el movimiento del rat�n

	// Si es el primer movimiento del rat�n
	if (firstMouse) {
		firstMouse = false;								// Se realiz� primer movimiento de rat�n
		lastX = x;										// Guardado de la posici�n de x
		lastY = y;										// Guardado de la posici�n de y
	}

	const float xoffset = x - lastX;					// Offset en x (posici�n actual - anterior)
	const float yoffset = lastY - y;					// Offset en x (anterior posici�n - actual)
	lastX = x;											// Actualizaci�n de la posici�n anterior en x
	lastY = y;											// Actualizaci�n de la posici�n anterior en y

	camera.handleMouseMovement(xoffset, yoffset);		// Ajuste del movimiento de la c�mara en x, y
}
//----------------------------------------FUNCI�N ONMOUSEMOVED----------------------------------------//

//----------------------------FUNCI�N ONSCROLLMOVED----------------------------//
void onScrollMoved(float x, float y) {
	// Funci�n que controla el movimiento scroll

	camera.handleMouseScroll(y);		// Ajuste del movimiento de la c�mara 
}
//----------------------------FUNCI�N ONSCROLLMOVED----------------------------//

//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//
void render(const Model& object, const Geometry& light, const Shader& s_phong, const Shader& s_light,
	const Texture& t_albedo, const Texture& t_specular) {
	// Funci�n de renderizaci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);													// Borrado de pantalla y profundidad

	glm::mat4 view = camera.getViewMatrix();															// Posici�n de la vista
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);	// Perspectiva de la visi�n

	glm::vec3 lightDiffuse(1.0f, 1.0f, 1.0f);
	glm::vec3 lightColorPoint(1.0f, 0.0f, 0.0f);
	glm::vec3 lightColorSpot(0.0f, 0.0f, 1.0f);

	s_light.use();																						// Se ejecuta la luz

	glm::mat4 model = glm::mat4(1.0f);																	// Posici�n de la c�mara
	model = glm::translate(model, lightPos);															// Traslaci�n con luz
	model = glm::scale(model, glm::vec3(0.25f));														// Escalado
	s_light.set("model", model);																		// Se aplican los cambios al model
	s_light.set("view", view);																			// Se aplican los cambios al view
	s_light.set("proj", proj);																			// Se aplican los cambios al proj
	s_light.set("lightColor", lightDiffuse);															// Se aplican los cambios de color

	light.render();

	s_light.use();																						// Se ejecuta la luz

	for (const auto& pointPos : pointLightPositions)
	{
		glm::mat4 model = glm::mat4(1.0f);																	// Posici�n de la c�mara
		model = glm::translate(model, pointPos);															// Traslaci�n con luz
		model = glm::scale(model, glm::vec3(0.25f));														// Escalado
		s_light.set("model", model);																		// Se aplican los cambios al model
		s_light.set("view", view);																			// Se aplican los cambios al view
		s_light.set("proj", proj);																			// Se aplican los cambios al proj
		s_light.set("lightColor", lightColorPoint);															// Se aplican los cambios de color

		light.render();
	}

	for (const auto& spotPos : spotLightPositions)
	{
		glm::mat4 model = glm::mat4(1.0f);																	// Posici�n de la c�mara
		model = glm::translate(model, spotPos);																// Traslaci�n con luz
		model = glm::scale(model, glm::vec3(0.25f));														// Escalado
		s_light.set("model", model);																		// Se aplican los cambios al model
		s_light.set("view", view);																			// Se aplican los cambios al view
		s_light.set("proj", proj);																			// Se aplican los cambios al proj
		s_light.set("lightColor", lightColorSpot);															// Se aplican los cambios de color

		light.render();
	}

	s_phong.use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	s_phong.set("viewPos", camera.getPosition());

	s_phong.set("light.position", lightPos);
	s_phong.set("light.direction", lightDir);
	s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
	s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
	s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

	const std::string prefixPoints = "pointLight[";
	for (uint32_t i = 0; i < sizeof(pointLightPositions); ++i) {
		float factor = i * 0.05;
		const std::string lightName = prefixPoints + std::to_string(i) + "].";
		s_phong.set((lightName + "position").c_str(), pointLightPositions[i]);
		s_phong.set((lightName + "ambient").c_str(), 0.02f + i, 0.02f + i, 0.02f + i);
		s_phong.set((lightName + "diffuse").c_str(), 0.2f + i, 0.0f + i, 0.0f + i);
		s_phong.set((lightName + "specular").c_str(), 0.5f + i, 0.0f + i, 0.0f + i);
		s_phong.set((lightName + "constant").c_str(), 1.0f);
		s_phong.set((lightName + "linear").c_str(), 0.09f);
		s_phong.set((lightName + "quadratic").c_str(), 0.032f);
	}

	const std::string prefixSpots = "spotLight[";
	for (uint32_t i = 0; i < sizeof(spotLightPositions); ++i) {
		float factor = i * 0.10;
		const std::string lightName = prefixSpots + std::to_string(i) + "].";
		s_phong.set((lightName + "position").c_str(), spotLightPositions[i]);
		s_phong.set((lightName + "ambient").c_str(), 0.02f + i, 0.02f + i, 0.02f + i);
		s_phong.set((lightName + "direction").c_str(), 0.0f, -1.0f, 0.0f);
		s_phong.set((lightName + "diffuse").c_str(), 0.2f + i, 0.0f + i, 0.0f + i);
		s_phong.set((lightName + "specular").c_str(), 0.5f + i, 0.0f + i, 0.0f + i);
		s_phong.set((lightName + "constant").c_str(), 1.0f);
		s_phong.set((lightName + "linear").c_str(), 0.09f);
		s_phong.set((lightName + "quadratic").c_str(), 0.032f);
		s_phong.set((lightName + "cutOff").c_str(), glm::cos(glm::radians(20.0f)));
		s_phong.set((lightName + "outerCutOff").c_str(), glm::cos(glm::radians(25.0f)));
	}

	t_albedo.use(s_phong, "material.diffuse", 0);
	t_specular.use(s_phong, "material.specular", 1);
	s_phong.set("material.shininess", 32);

	s_phong.use();
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	object.render(s_phong);
}
//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader s_phong("../projects/EJ09_04/phong.vs", "../projects/EJ09_04/blinn.fs");		// Carga del shader de phong
	const Shader s_light("../projects/EJ09_04/light.vs", "../projects/EJ09_04/light.fs");		// Carga del shader de light
	const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);		// Textura albedo
	const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);	// Textura specular
	const Sphere sphere(1.0f, 50, 50);															// Creaci�n de esfera
	const Model object("../assets/models/Volkswagen Touareg 2/model/Touareg.obj");				// Creación del modelo

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	glEnable(GL_DEPTH_TEST);																	// Activaci�n del cull depth test
	glDepthFunc(GL_LESS);

	Input::instance()->setKeyPressedCallback(onKeyPress);
	Input::instance()->setMouseMoveCallback(onMouseMoved);
	Input::instance()->setScrollMoveCallback(onScrollMoved);

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el �ltimo frame

		handleInput(deltaTime);
		render(object, sphere, s_phong, s_light, t_albedo, t_specular);																// Se renderiza el modelo y la luz
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////