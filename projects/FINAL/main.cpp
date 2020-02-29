/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 9_02
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Febrero 2020
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
//--------------------------------------LIBRER�AS--------------------------------------//
#include <glad/glad.h>						// Librería de manejo de GLAD
#include <GLFW/glfw3.h>						// Librería de manejo de GLFW
#include <glm/gtc/matrix_transform.hpp>		// Librería de transformaci�n de matrices

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"			// Librería de manejo de geometr�a cubo
#include "engine/input.hpp"					// Librería de manejo de inputs
#include "engine/shader.hpp"				// Librería de manejo de shaders
#include "engine/texture.hpp"				// Librería de manejo de texturas
#include "engine/window.hpp"				// Librería de manejo de ventanas
#include "engine/geometry/sphere.hpp"		// Librería de manejo de geometría esfera
#include "engine/geometry/quad.hpp"			// Librería de manejo de geometría quad
#include "engine/geometry/teapot.hpp"		// Librería de manejo de geometría tetera

#include <iostream>							// Librer�a de funciones del sistema
//--------------------------------------LIBRER�AS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));		// Definici�n de la c�mara
glm::vec3 lightPos(0.0f, 2.0f, 0.0f);			// Posición de la luz
glm::vec3 lightDir(0.0f, 0.0f, -1.0f);			// Dirección de la luz

glm::vec3 cubePositions[] = {					// Posiciones del cubo
	// Fila 13
	glm::vec3(7.0f, 0.0f, -7.0f),
	glm::vec3(6.0f, 0.0f, -7.0f),
	glm::vec3(5.0f, 0.0f, -7.0f),
	glm::vec3(4.0f, 0.0f, -7.0f),
	glm::vec3(3.0f, 0.0f, -7.0f),
	glm::vec3(2.0f, 0.0f, -7.0f),
	glm::vec3(1.0f, 0.0f, -7.0f),
	glm::vec3(0.0f, 0.0f, -7.0f),
	glm::vec3(-1.0f, 0.0f, -7.0f),
	glm::vec3(-2.0f, 0.0f, -7.0f),
	glm::vec3(-3.0f, 0.0f, -7.0f),
	glm::vec3(-4.0f, 0.0f, -7.0f),
	glm::vec3(-5.0f, 0.0f, -7.0f),
	glm::vec3(-6.0f, 0.0f, -7.0f),
	glm::vec3(-7.0f, 0.0f, -7.0f),

	// Fila 12
	glm::vec3(7.0f, 0.0f, -6.0f),
	glm::vec3(6.0f, 0.0f, -6.0f),
	glm::vec3(5.0f, 0.0f, -6.0f),
	glm::vec3(4.0f, 0.0f, -6.0f),
	glm::vec3(3.0f, 0.0f, -6.0f),
	glm::vec3(2.0f, 0.0f, -6.0f),
	glm::vec3(1.0f, 0.0f, -6.0f),
	glm::vec3(0.0f, 0.0f, -6.0f),
	glm::vec3(-1.0f, 0.0f, -6.0f),
	glm::vec3(-2.0f, 0.0f, -6.0f),
	glm::vec3(-3.0f, 0.0f, -6.0f),
	glm::vec3(-4.0f, 0.0f, -6.0f),
	glm::vec3(-5.0f, 0.0f, -6.0f),
	glm::vec3(-6.0f, 0.0f, -6.0f),
	glm::vec3(-7.0f, 0.0f, -6.0f),

	// Fila 11
	glm::vec3(7.0f, 0.0f, -5.0f),
	glm::vec3(6.0f, 0.0f, -5.0f),
	glm::vec3(5.0f, 0.0f, -5.0f),
	glm::vec3(2.0f, 0.0f, -5.0f),
	glm::vec3(-3.0f, 0.0f, -5.0f),
	glm::vec3(-7.0f, 0.0f, -5.0f),

	// Fila 10
	glm::vec3(7.0f, 0.0f, -4.0f),
	glm::vec3(6.0f, 0.0f, -4.0f),
	glm::vec3(5.0f, 0.0f, -4.0f),
	glm::vec3(3.0f, 0.0f, -4.0f),
	glm::vec3(2.0f, 0.0f, -4.0f),
	glm::vec3(1.0f, 0.0f, -4.0f),
	glm::vec3(0.0f, 0.0f, -4.0f),
	glm::vec3(-1.0f, 0.0f, -4.0f),
	glm::vec3(-3.0f, 0.0f, -4.0f),
	glm::vec3(-5.0f, 0.0f, -4.0f),
	glm::vec3(-6.0f, 0.0f, -4.0f),
	glm::vec3(-7.0f, 0.0f, -4.0f),

	// Fila 9
	glm::vec3(7.0f, 0.0f, -3.0f),
	glm::vec3(6.0f, 0.0f, -3.0f),
	glm::vec3(5.0f, 0.0f, -3.0f),
	glm::vec3(-1.0f, 0.0f, -3.0f),
	glm::vec3(-3.0f, 0.0f, -3.0f),
	glm::vec3(-5.0f, 0.0f, -3.0f),
	glm::vec3(-6.0f, 0.0f, -3.0f),
	glm::vec3(-7.0f, 0.0f, -3.0f),

	// Fila 8
	glm::vec3(7.0f, 0.0f, -2.0f),
	glm::vec3(6.0f, 0.0f, -2.0f),
	glm::vec3(5.0f, 0.0f, -2.0f),
	glm::vec3(3.0f, 0.0f, -2.0f),
	glm::vec3(2.0f, 0.0f, -2.0f),
	glm::vec3(1.0f, 0.0f, -2.0f),
	glm::vec3(-1.0f, 0.0f, -2.0f),
	glm::vec3(-3.0f, 0.0f, -2.0f),
	glm::vec3(-5.0f, 0.0f, -2.0f),
	glm::vec3(-6.0f, 0.0f, -2.0f),
	glm::vec3(-7.0f, 0.0f, -2.0f),

	// Fila 7
	glm::vec3(7.0f, 0.0f, -1.0f),
	glm::vec3(6.0f, 0.0f, -1.0f),
	glm::vec3(5.0f, 0.0f, -1.0f),
	glm::vec3(3.0f, 0.0f, -1.0f),
	glm::vec3(2.0f, 0.0f, -1.0f),
	glm::vec3(-3.0f, 0.0f, -1.0f),
	glm::vec3(-5.0f, 0.0f, -1.0f),
	glm::vec3(-6.0f, 0.0f, -1.0f),
	glm::vec3(-7.0f, 0.0f, -1.0f),

	// Fila 6
	glm::vec3(7.0f, 0.0f, 0.0f),
	glm::vec3(6.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(-1.0f, 0.0f, 0.0f),
	glm::vec3(-3.0f, 0.0f, 0.0f),
	glm::vec3(-5.0f, 0.0f, 0.0f),
	glm::vec3(-6.0f, 0.0f, 0.0f),
	glm::vec3(-7.0f, 0.0f, 0.0f),

	// Fila 5
	glm::vec3(7.0f, 0.0f, 1.0f),
	glm::vec3(6.0f, 0.0f, 1.0f),
	glm::vec3(4.0f, 0.0f, 1.0f),
	glm::vec3(2.0f, 0.0f, 1.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(-1.0f, 0.0f, 1.0f),
	glm::vec3(-5.0f, 0.0f, 1.0f),
	glm::vec3(-6.0f, 0.0f, 1.0f),
	glm::vec3(-7.0f, 0.0f, 1.0f),

	// Fila 4
	glm::vec3(7.0f, 0.0f, 2.0f),
	glm::vec3(6.0f, 0.0f, 2.0f),
	glm::vec3(4.0f, 0.0f, 2.0f),
	glm::vec3(2.0f, 0.0f, 2.0f),
	glm::vec3(1.0f, 0.0f, 2.0f),
	glm::vec3(0.0f, 0.0f, 2.0f),
	glm::vec3(-1.0f, 0.0f, 2.0f),
	glm::vec3(-3.0f, 0.0f, 2.0f),
	glm::vec3(-5.0f, 0.0f, 2.0f),
	glm::vec3(-6.0f, 0.0f, 2.0f),
	glm::vec3(-7.0f, 0.0f, 2.0f),

	// Fila 3
	glm::vec3(7.0f, 0.0f, 3.0f),
	glm::vec3(4.0f, 0.0f, 3.0f),
	glm::vec3(-5.0f, 0.0f, 3.0f),
	glm::vec3(-6.0f, 0.0f, 3.0f),
	glm::vec3(-7.0f, 0.0f, 3.0f),

	// Fila 2
	glm::vec3(7.0f, 0.0f, 4.0f),
	glm::vec3(6.0f, 0.0f, 4.0f),
	glm::vec3(5.0f, 0.0f, 4.0f),
	glm::vec3(4.0f, 0.0f, 4.0f),
	glm::vec3(3.0f, 0.0f, 4.0f),
	glm::vec3(2.0f, 0.0f, 4.0f),
	glm::vec3(1.0f, 0.0f, 4.0f),
	glm::vec3(-1.0f, 0.0f, 4.0f),
	glm::vec3(-2.0f, 0.0f, 4.0f),
	glm::vec3(-3.0f, 0.0f, 4.0f),
	glm::vec3(-7.0f, 0.0f, 4.0f),

	// Fila 1
	glm::vec3(7.0f, 0.0f, 5.0f),
	glm::vec3(6.0f, 0.0f, 5.0f),
	glm::vec3(5.0f, 0.0f, 5.0f),
	glm::vec3(4.0f, 0.0f, 5.0f),
	glm::vec3(3.0f, 0.0f, 5.0f),
	glm::vec3(2.0f, 0.0f, 5.0f),
	glm::vec3(1.0f, 0.0f, 5.0f),
	glm::vec3(-1.0f, 0.0f, 5.0f),
	glm::vec3(-2.0f, 0.0f, 5.0f),
	glm::vec3(-3.0f, 0.0f, 5.0f),
	glm::vec3(-4.0f, 0.0f, 5.0f),
	glm::vec3(-5.0f, 0.0f, 5.0f),
	glm::vec3(-6.0f, 0.0f, 5.0f),
	glm::vec3(-7.0f, 0.0f, 5.0f),

	// Fila 0
	glm::vec3(7.0f, 0.0f, 6.0f),
	glm::vec3(-7.0f, 0.0f, 6.0f),

	// Fila pared inicial
	glm::vec3(7.0f, 0.0f, 7.0f),
	glm::vec3(6.0f, 0.0f, 7.0f),
	glm::vec3(5.0f, 0.0f, 7.0f),
	glm::vec3(4.0f, 0.0f, 7.0f),
	glm::vec3(3.0f, 0.0f, 7.0f),
	glm::vec3(2.0f, 0.0f, 7.0f),
	glm::vec3(1.0f, 0.0f, 7.0f),
	glm::vec3(0.0f, 0.0f, 7.0f),
	glm::vec3(-1.0f, 0.0f, 7.0f),
	glm::vec3(-2.0f, 0.0f, 7.0f),
	glm::vec3(-3.0f, 0.0f, 7.0f),
	glm::vec3(-4.0f, 0.0f, 7.0f),
	glm::vec3(-5.0f, 0.0f, 7.0f),
	glm::vec3(-6.0f, 0.0f, 7.0f),
	glm::vec3(-7.0f, 0.0f, 7.0f),
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
void render(const Geometry& floor, const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light,
	const Texture& t_albedo, const Texture& t_specular) {
	// Funci�n de renderizaci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);													// Borrado de pantalla y profundidad

	glm::mat4 view = camera.getViewMatrix();															// Posici�n de la vista
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()),									// Perspectiva de la visi�n
					 static_cast<float>(Window::instance()->getWidth()) / static_cast<float>(Window::instance()->getHeight()),
					 0.1f, 100.0f);																		

	glm::vec3 lightDiffuse(1.0f, 1.0f, 1.0f);

	s_light.use();																						// Se ejecuta la luz

	glm::mat4 model = glm::mat4(1.0f);																	// Posici�n de la c�mara
	model = glm::translate(model, lightPos);															// Traslaci�n con luz
	model = glm::scale(model, glm::vec3(0.25f));														// Escalado
	s_light.set("model", model);																		// Se aplican los cambios al model
	s_light.set("view", view);																			// Se aplican los cambios al view
	s_light.set("proj", proj);																			// Se aplican los cambios al proj
	s_light.set("lightColor", lightDiffuse);															// Se aplican los cambios de color

	light.render();

	s_phong.use();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	s_phong.set("viewPos", camera.getPosition());

	s_phong.set("light.position", camera.getPosition());
	s_phong.set("light.direction", lightDir);
	s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
	s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
	s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);
	s_phong.set("light.constant", 1.0f);
	s_phong.set("light.linear", 0.2f);
	s_phong.set("light.quadratic", 0.06f);
	s_phong.set("light.cutOff", glm::cos(glm::radians(40.0f)));
	s_phong.set("light.outerCutOff", glm::cos(glm::radians(50.0f)));

	t_albedo.use(s_phong, "material.diffuse", 0);
	t_specular.use(s_phong, "material.specular", 1);
	s_phong.set("material.shininess", 32);

	floor.render();

	for (const auto& cubePos : cubePositions) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePos);
		s_phong.set("model", model);

		glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
		s_phong.set("normalMat", normalMat);

		object.render();
	}
}
//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader s_phong("../projects/EJ09_02/phong.vs", "../projects/EJ09_02/blinn.fs");		// Carga del shader de phong
	const Shader s_light("../projects/EJ09_02/light.vs", "../projects/EJ09_02/light.fs");		// Carga del shader de light
	const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);		// Textura albedo
	const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);	// Textura specular
	const Sphere sphere(1.0f, 50, 50);															// Creaci�n de esfera
	const Quad quad(1.0f);																		// Creaci�n de quad
	const Cube cube(1.0f);

	Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);					// Textura de objeto

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	glEnable(GL_DEPTH_TEST);																	// Activaci�n del cull depth test
	glDepthFunc(GL_LESS);

	Input::instance()->setKeyPressedCallback(onKeyPress);										// Asociac�n de callback de tecla pulsada
	Input::instance()->setMouseMoveCallback(onMouseMoved);										// Asociac�n de callback de rat�n movido
	Input::instance()->setScrollMoveCallback(onScrollMoved);									// Asociac�n de callback de scroll movido

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el �ltimo frame

		handleInput(deltaTime);
		render(quad, cube, sphere, s_phong, s_light, t_albedo, t_specular);						// Se renderiza la esfera y la luz
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////