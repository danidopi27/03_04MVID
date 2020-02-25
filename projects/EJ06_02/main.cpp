/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 6_02
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////

//------------------------------------------LIBRER�AS------------------------------------------//
#include <glad/glad.h>						// Librer�a de manejo de GLAD
#include <GLFW/glfw3.h>						// Librer�a de manejo de GLFW
#include <glm/gtc/matrix_transform.hpp>		// Librer�a de transformaci�n de matrices

#include "engine/camera_06_02.hpp"			// Librer�a de manejo de c�mara modificada
#include "engine/geometry/cube_05_01.hpp"	// Librer�a de manejo de geometr�a cubo modificada
#include "engine/input.hpp"					// Librer�a de manejo de inputs
#include "engine/shader.hpp"				// Librer�a de manejo de shaders
#include "engine/texture.hpp"				// Librer�a de manejo de texturas
#include "engine/window.hpp"				// Librer�a de manejo de ventanas
#include "engine/geometry/sphere.hpp"		// Librer�a de manejo de geometr�a esfera
//------------------------------------------LIBRER�AS------------------------------------------//

//--------------------------------------------VARIABLES--------------------------------------------//
Camera_06_02 camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definici�n de la c�mara
float lastFrame = 0.0f;									// Variable de �ltimo frame
float lastX, lastY;										// Variable de �ltima coordenada x, y
bool firstMouse = true;									// Variable de primer movimiento de rat�n
//--------------------------------------------VARIABLES--------------------------------------------//

//------------------------------------------FUNCI�N HANDLEINPUT------------------------------------------//
void handleInput(float dt) {
	// Funci�n que maneja las entradas

	Input* input = Input::instance();									// Objeto input

	// Si la tecla W est� pulsada
	if (input->isKeyPressed(GLFW_KEY_W)) {
		camera.handleKeyboard(Camera_06_02::Movement::Forward, dt);		// Movimiento hacia adelante
	}
	// Si la tecla S est� pulsada
	if (input->isKeyPressed(GLFW_KEY_S)) {
		camera.handleKeyboard(Camera_06_02::Movement::Backward, dt);	// Movimiento hacia atr�s
	}
	// Si la tecla A est� pulsada
	if (input->isKeyPressed(GLFW_KEY_A)) {
		camera.handleKeyboard(Camera_06_02::Movement::Left, dt);		// Movimiento hacia la izquierda
	}
	// Si la tecla D est� pulsada
	if (input->isKeyPressed(GLFW_KEY_D)) {
		camera.handleKeyboard(Camera_06_02::Movement::Right, dt);		// Movimiento hacia la derecha
	}
}
//------------------------------------------FUNCI�N HANDLEINPUT------------------------------------------//

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

//---------------------------------------------------------------------FUNCI�N RENDER---------------------------------------------------------------------//
void render(const Geometry& cube_1, const Geometry& cube_2, const Geometry& cube_3, const Shader& shader, Texture& tex) {
	// Funci�n de renderizaci�n

	glClear(GL_COLOR_BUFFER_BIT);																						// Borrado de la pantalla

	glm::mat4 model = glm::mat4(1.0f);																					// Matriz diagonal

	glm::mat4 view = camera.getViewMatrix();

	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);					// Perspectiva de la visi�n

	shader.use();																										// Se ejecuta el shader

	tex.use(shader, "tex", 0);																							// Uso de la textura

	shader.set("model", model);																							// Uso de la matriz model
	shader.set("view", camera.getViewMatrix());																			// Uso de la matriz view
	shader.set("proj", proj);																							// Uso de la matriz proj

	cube_1.render();																									// Se pinta la geometr�a
	cube_2.render();																									// Se pinta la geometr�a
	cube_3.render();																									// Se pinta la geometr�a
}
//---------------------------------------------------------------------FUNCI�N RENDER---------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader shader("../projects/EJ06_02/vertex.vs", "../projects/EJ06_02/fragment.fs");	// Carga de los shaders
	float center_1[3] = { -0.5f, 0.0f, 1.0f };													// Coordenadas del centro
	float radio_1 = 0.1f;																		// Radio del cubo
	const Cube_05_01 cube_1(center_1, radio_1);													// Creaci�n del cubo

	float center_2[3] = { 0.25f, 0.0f, 0.0f };													// Coordenadas del centro
	float radio_2 = 0.05f;																		// Radio del cubo
	const Cube_05_01 cube_2(center_2, radio_2);													// Creaci�n del cubo

	float center_3[3] = { 0.25f, 0.75f, 1.0f };													// Coordenadas del centro
	float radio_3 = 0.3f;																		// Radio del cubo
	const Cube_05_01 cube_3(center_3, radio_3);													// Creaci�n del cubo

	Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);					// Creaci�n de la textura

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	Input::instance()->setKeyPressedCallback(onKeyPress);										// Asociac�n de callback de tecla pulsada
	Input::instance()->setMouseMoveCallback(onMouseMoved);										// Asociac�n de callback de rat�n movido
	Input::instance()->setScrollMoveCallback(onScrollMoved);									// Asociac�n de callback de scroll movido

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el �ltimo frame

		handleInput(deltaTime);																	// Se controlan las entradas
		render(cube_1, cube_2, cube_3, shader, tex);											// Se renderiza la esfera, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE C�DIGO////////////////////////////////////////////////////////////////////