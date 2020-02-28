/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 11_03
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
//--------------------------------------LIBRER�AS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definici�n de la c�mara
glm::vec3 lightPos(0.0f, 2.0f, 0.0f);			// Posición de la luz

glm::vec3 quadPositions[] = {					// Posiciones del cubo
	glm::vec3(0.0f, 0.0f, -4.0f),
	glm::vec3(0.0f, 0.0f, -0.5f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 0.5f)
};

glm::vec3 quadColor[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
};

float quadAlpha[]{
	0.5f,
	0.1f,
	0.5f,
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
void render(const Geometry& quad, const Shader& s_phong, const Shader& s_blend, const Texture& t_albedo, const Texture& t_specular) {
	// Funci�n de renderizaci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);													// Borrado de pantalla y profundidad

	glm::mat4 view = camera.getViewMatrix();															// Posici�n de la vista
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);	// Perspectiva de la visi�n

	s_phong.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	s_phong.set("viewPos", camera.getPosition());

	s_phong.set("light.direction", -0.2f, -1.0f, -0.3f);
	s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
	s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
	s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

	t_albedo.use(s_phong, "material.diffuse", 0);
	t_specular.use(s_phong, "material.specular", 1);
	s_phong.set("material.shininess", 32);

	quad.render();

	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			s_phong.use();
			model = glm::mat4(1.0f);
			model = glm::translate(model, quadPositions[i]);
			s_phong.set("model", model);
			s_phong.set("view", view);
			s_phong.set("proj", proj);

			normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
			s_phong.set("normalMat", normalMat);

			t_albedo.use(s_phong, "material.diffuse", 0);
			t_specular.use(s_phong, "material.specular", 1);
			s_phong.set("material.shininess", 32);

			quad.render();
		}

		else
		{
			s_blend.use();
			model = glm::mat4(1.0f);
			model = glm::translate(model, quadPositions[i]);
			s_blend.set("model", model);
			s_blend.set("view", view);
			s_blend.set("proj", proj);

			normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
			s_phong.set("normalMat", normalMat);

			s_blend.set("viewPos", camera.getPosition());

			s_blend.set("light.direction", -0.2f, -0.1f, -0.3f);
			s_blend.set("light.ambient", 0.1f, 0.1f, 0.1f);
			s_blend.set("light.diffuse", 0.5f, 0.5f, 0.5f);
			s_blend.set("light.specular", 1.0f, 1.0f, 1.0f);

			s_blend.set("material.ambient", 0.1f * quadColor[i - 1]);
			s_blend.set("material.diffuse", 0.5f * quadColor[i - 1]);
			s_blend.set("material.specular", 1.0f * quadColor[i - 1]);
			s_blend.set("material.shininess", 32);

			s_blend.set("material.alpha", quadAlpha[i - 1]);

			quad.render();
		}
	}
}
//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader s_phong("../projects/EJ11_02/phong.vs", "../projects/EJ11_02/blinn.fs");		// Carga del shader de phong
	const Shader s_blend("../projects/EJ11_02/blend.vs", "../projects/EJ11_02/blend.fs");		// Carga del shader de blend
	const Texture t_albedo("../assets/textures/Walnut_Italian_Diffuse.png", Texture::Format::RGB);		// Textura albedo
	const Texture t_specular("../assets/textures/Walnut_Italian_Specular.png", Texture::Format::RGB);	// Textura specular
	const Quad quad(1.0f);																		// Creaci�n de quad

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	glEnable(GL_DEPTH_TEST);																	// Activaci�n del cull depth test
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Input::instance()->setKeyPressedCallback(onKeyPress);
	Input::instance()->setMouseMoveCallback(onMouseMoved);
	Input::instance()->setScrollMoveCallback(onScrollMoved);

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el �ltimo frame

		handleInput(deltaTime);
		render(quad, s_phong, s_blend, t_albedo, t_specular);									// Se renderiza
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//


////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////