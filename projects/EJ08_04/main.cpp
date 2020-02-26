/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 8_04
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Febrero 2020
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////

//--------------------------------------LIBRER�AS--------------------------------------//
#include <glad/glad.h>						// Librer�a de manejo de GLAD
#include <GLFW/glfw3.h>						// Librer�a de manejo de GLFW
#include <glm/gtc/matrix_transform.hpp>		// Librer�a de transformaci�n de matrices

#include "engine/camera.hpp"				// Librer�a de manejo de c�mara
#include "engine/geometry/cube.hpp"			// Librer�a de manejo de geometr�a cubo
#include "engine/input.hpp"					// Librer�a de manejo de inputs
#include "engine/shader.hpp"				// Librer�a de manejo de shaders
#include "engine/texture.hpp"				// Librer�a de manejo de texturas
#include "engine/window.hpp"				// Librer�a de manejo de ventanas
#include "engine/geometry/sphere.hpp"		// Librer�a de manejo de geometr�a esfera
#include "engine/geometry/quad.hpp"			// Librer�a de manejo de geometr�a quad

#include <iostream>							// Librer�a de funciones del sistema
//--------------------------------------LIBRER�AS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definici�n de la c�mara
glm::vec3 lightPos(4.0f, 1.0f, 0.0f);			// Posici�n de la luz

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
void render(const Geometry& object, const Geometry& light, const Shader& s_phong, const Shader& s_light,
	const Texture& t_albedo, const Texture& t_specular, const Texture& t_emisivo) {
	// Funci�n de renderizaci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);													// Borrado de pantalla y profundidad

	glm::mat4 view = camera.getViewMatrix();															// Posici�n de la vista
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);	// Perspectiva de la visi�n

	glm::vec3 lightDiffuse(0.5f, 0.5f, 0.5f);

	s_light.use();																						// Se ejecuta la luz

	glm::mat4 model = glm::mat4(1.0f);																	// Posici�n de la c�mara
	model = glm::translate(model, lightPos);															// Traslaci�n con luz
	model = glm::scale(model, glm::vec3(0.25f));														// Escalado
	s_light.set("model", model);																		// Se aplican los cambios al model
	s_light.set("view", view);																			// Se aplican los cambios al view
	s_light.set("proj", proj);																			// Se aplican los cambios al proj
	s_light.set("lightColor", lightDiffuse);															// Se aplican los cambios de color

	light.render();																						// Se renderiza la luz

	s_phong.use();
	model = glm::mat4(1.0f);
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	s_phong.set("viewPos", camera.getPosition());

	s_phong.set("light.position", lightPos);
	s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
	s_phong.set("light.diffuse", lightDiffuse);
	s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

	t_albedo.use(s_phong, "material.diffuse", 0);
	t_specular.use(s_phong, "material.specular", 1);
	t_emisivo.use(s_phong, "material.emisivo", 2);
	s_phong.set("material.shininess", 32);

	object.render();
}
//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader s_phong("../projects/EJ08_04/phong.vs", "../projects/EJ08_04/blinn.fs");		// Carga del shader de phong
	const Shader s_light("../projects/EJ08_04/light.vs", "../projects/EJ08_04/light.fs");		// Carga del shader de light
	const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);		// Textura albedo
	const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);	// Textura specular
	const Texture t_emisivo("../assets/textures/emissive.jpg", Texture::Format::RGB);			// Textura emisiva

	const Sphere sphere(0.4f, 50, 50);															// Creaci�n de esfera

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
		render(sphere, sphere, s_phong, s_light, t_albedo, t_specular, t_emisivo);				// Se renderiza la esfera y la luz
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//


////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////