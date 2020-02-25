/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 7_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////

//--------------------------------------LIBRERÍAS--------------------------------------//
#include <glad/glad.h>						// Librería de manejo de GLAD
#include <GLFW/glfw3.h>						// Librería de manejo de GLFW
#include <glm/gtc/matrix_transform.hpp>		// Librería de transformación de matrices

#include "engine/camera.hpp"				// Librería de manejo de cámara
#include "engine/geometry/cube.hpp"			// Librería de manejo de geometría cubo
#include "engine/input.hpp"					// Librería de manejo de inputs
#include "engine/shader.hpp"				// Librería de manejo de shaders
#include "engine/texture.hpp"				// Librería de manejo de texturas
#include "engine/window.hpp"				// Librería de manejo de ventanas
#include "engine/geometry/sphere.hpp"		// Librería de manejo de geometría esfera
#include "engine/geometry/quad.hpp"			// Librería de manejo de geometría quad

#include <iostream>							// Librería de funciones del sistema
//--------------------------------------LIBRERÍAS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definición de la cámara
glm::vec3 lightPos(4.0f, 1.0f, 0.0f);			// Posición de la luz
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);			// Color de la luz

float lastFrame = 0.0f;							// Variable de último frame
float lastX, lastY;								// Variable de última coordenada x, y
bool firstMouse = true;							// Variable de primer movimiento de ratón
//----------------------------------------VARIABLES----------------------------------------//

//----------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------//
void handleInput(float dt) {
	// Función que maneja las entradas

	Input* input = Input::instance();								// Objeto input

	// Si la tecla W está pulsada
	if (input->isKeyPressed(GLFW_KEY_W)) {
		camera.handleKeyboard(Camera::Movement::Forward, dt);		// Movimiento hacia adelante
	}
	// Si la tecla S está pulsada
	if (input->isKeyPressed(GLFW_KEY_S)) {
		camera.handleKeyboard(Camera::Movement::Backward, dt);		// Movimiento hacia atrás
	}
	// Si la tecla A está pulsada
	if (input->isKeyPressed(GLFW_KEY_A)) {
		camera.handleKeyboard(Camera::Movement::Left, dt);			// Movimiento hacia la izquierda
	}
	// Si la tecla D está pulsada
	if (input->isKeyPressed(GLFW_KEY_D)) {
		camera.handleKeyboard(Camera::Movement::Right, dt);			// Movimiento hacia la derecha
	}
}
//----------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------//

//----------------------------------FUNCIÓN ONKEYPRESS----------------------------------//
void onKeyPress(int key, int action) {
	// Función que controla las pulsaciones de teclas

	// Si se pulsa la tecla Q
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		Window::instance()->setCaptureMode(true);		// Se pone el modo captura ON
	}
	// Si se pulsa la tecla E
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		Window::instance()->setCaptureMode(false);		// Se pone el modo captura OFF
	}
}
//----------------------------------FUNCIÓN ONKEYPRESS----------------------------------//

//----------------------------------------FUNCIÓN ONMOUSEMOVED----------------------------------------//
void onMouseMoved(float x, float y) {
	// Función que controla el movimiento del ratón

	// Si es el primer movimiento del ratón
	if (firstMouse) {
		firstMouse = false;								// Se realizó primer movimiento de ratón
		lastX = x;										// Guardado de la posición de x
		lastY = y;										// Guardado de la posición de y
	}

	const float xoffset = x - lastX;					// Offset en x (posición actual - anterior)
	const float yoffset = lastY - y;					// Offset en x (anterior posición - actual)
	lastX = x;											// Actualización de la posición anterior en x
	lastY = y;											// Actualización de la posición anterior en y

	camera.handleMouseMovement(xoffset, yoffset);		// Ajuste del movimiento de la cámara en x, y
}
//----------------------------------------FUNCIÓN ONMOUSEMOVED----------------------------------------//

//----------------------------FUNCIÓN ONSCROLLMOVED----------------------------//
void onScrollMoved(float x, float y) {
	// Función que controla el movimiento scroll

	camera.handleMouseScroll(y);		// Ajuste del movimiento de la cámara 
}
//----------------------------FUNCIÓN ONSCROLLMOVED----------------------------//

//---------------------------------------------------------------FUNCIÓN RENDER---------------------------------------------------------------//
void render(const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light) {
	// Función de renderización

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);													// Borrado de pantalla y profundidad

	glm::mat4 view = camera.getViewMatrix();															// Posición de la vista
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);	// Perspectiva de la visión

	s_light.use();																						// Se ejecuta la luz

	glm::mat4 model = glm::mat4(1.0f);																	// Posición de la cámara
	model = glm::translate(model, lightPos);															// Traslación con luz
	model = glm::scale(model, glm::vec3(0.25f));														// Escalado
	s_light.set("model", model);																		// Se aplican los cambios al model
	s_light.set("view", view);																			// Se aplican los cambios al view
	s_light.set("proj", proj);																			// Se aplican los cambios al proj
	s_light.set("lightColor", lightColor);																// Se aplican los cambios de color

	light.render();																						// Se renderiza la luz

	s_phong.use();
	model = glm::mat4(1.0f);
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	s_phong.set("objectColor", glm::vec3(0.6f, 0.5f, 0.2f));
	s_phong.set("lightColor", lightColor);

	s_phong.set("ambientStrength", 0.7f);
	s_phong.set("lightPos", lightPos);

	s_phong.set("viewPos", camera.getPosition());
	s_phong.set("shininess", 85);
	s_phong.set("specularStrength", 0.1f);

	object.render();
}
//---------------------------------------------------------------FUNCIÓN RENDER---------------------------------------------------------------//

//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader s_phong("../projects/EJ07_02/phong.vs", "../projects/EJ07_02/blinn.fs");		// Carga del shader de phong
	const Shader s_light("../projects/EJ07_02/light.vs", "../projects/EJ07_02/light.fs");		// Carga del shader de light
	const Sphere sphere(1.0f, 50, 50);

	Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);					// Creación de la textura

	glEnable(GL_CULL_FACE);																		// Activación del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	glEnable(GL_DEPTH_TEST);																	// Activación del cull depth test
	glDepthFunc(GL_LESS);

	Input::instance()->setKeyPressedCallback(onKeyPress);										// Asociacón de callback de tecla pulsada
	Input::instance()->setMouseMoveCallback(onMouseMoved);										// Asociacón de callback de ratón movido
	Input::instance()->setScrollMoveCallback(onScrollMoved);									// Asociacón de callback de scroll movido

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el último frame

		handleInput(deltaTime);
		render(sphere, sphere, s_phong, s_light);												// Se renderiza la esfera y la luz
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////