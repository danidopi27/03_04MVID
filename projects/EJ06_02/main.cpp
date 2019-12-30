/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 6_02
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
//--------------------------------------LIBRERÍAS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definición de la cámara
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

//---------------------------------------------------------------------FUNCIÓN RENDER---------------------------------------------------------------------//
void render(const Geometry& geom, const Shader& shader, Texture& tex) {
	// Función de renderización

	glClear(GL_COLOR_BUFFER_BIT);																						// Borrado de la pantalla

	glm::mat4 model = glm::mat4(1.0f);																					// Matriz diagonal
	model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));	// Rotación de la cámara

	glm::mat4 view = glm::mat4(1.0f);																					// Matriz diagonal
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));															// Cámara acercandose a pantalla

	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);					// Perspectiva de la visión

	shader.use();																										// Se ejecuta el shader

	tex.use(shader, "tex", 0);																							// Uso de la textura

	shader.set("model", model);																							// Uso de la matriz model
	shader.set("view", camera.getViewMatrix());																			// Uso de la matriz view
	shader.set("proj", proj);																							// Uso de la matriz proj

	geom.render();																										// Se pinta la geometría
}
//---------------------------------------------------------------------FUNCIÓN RENDER---------------------------------------------------------------------//

//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader shader("../projects/EJ06_02/vertex.vs", "../projects/EJ06_02/fragment.fs");	// Carga de los shaders
	//const Cube cube(1.0f);																		// Creación de un cubo
	const Sphere sphere(1.0f, 50, 50);															// Creación de una esfera

	Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);					// Creación de la textura

	glEnable(GL_CULL_FACE);																		// Activación del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	Input::instance()->setKeyPressedCallback(onKeyPress);										// Asociacón de callback de tecla pulsada
	Input::instance()->setMouseMoveCallback(onMouseMoved);										// Asociacón de callback de ratón movido
	Input::instance()->setScrollMoveCallback(onScrollMoved);									// Asociacón de callback de scroll movido

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el último frame

		handleInput(deltaTime);																	// Se controlan las entradas
		render(sphere, shader, tex);															// Se renderiza la esfera, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////