/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 13_02
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
#include <iostream>							// Librería de funciones del sistema
//--------------------------------------LIBRER�AS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));		// Definici�n de la c�mara
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);			// Posición de la luz	

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

//-----------------------------------------------------------FUNCIÓN CREATEFBO-----------------------------------------------------------//
std::tuple<uint32_t, uint32_t, uint32_t> createFBO() {
	uint32_t fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	uint32_t textureColor;
	glGenTextures(1, &textureColor);
	glBindTexture(GL_TEXTURE_2D, textureColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::instance()->getWidth(), Window::instance()->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColor, 0);

	uint32_t rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Window::instance()->getWidth(), Window::instance()->getHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer Incomplete" << std::endl;
	}

	return std::make_tuple(fbo, textureColor, rbo);
}
//-----------------------------------------------------------FUNCIÓN CREATEFBO-----------------------------------------------------------//

//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//
void render(const Geometry& quad, const Geometry& cube, const Shader& s_phong, const Shader& s_fbo,
	const Texture& t_albedo, const Texture& t_specular, const uint32_t fbo, const uint32_t fbo_texture) {
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);

	//FIRST PASS
	glEnable(GL_DEPTH_TEST);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	s_phong.use();
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	s_phong.set("viewPos", camera.getPosition());

	s_phong.set("light.position", lightPos);
	s_phong.set("light.ambient", 0.1f, 0.0f, 0.0f);
	s_phong.set("light.diffuse", 0.5f, 0.0f, 0.0f);
	s_phong.set("light.specular", 1.0f, 0.0f, 0.0f);

	t_albedo.use(s_phong, "material.diffuse", 0);
	t_specular.use(s_phong, "material.specular", 1);
	s_phong.set("material.shininess", 32);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	s_phong.set("model", model);
	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	quad.render();

	model = glm::mat4(1.0f);
	s_phong.set("model", model);
	normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	cube.render();

	//SECOND PASS

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT);

	s_fbo.use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	s_fbo.set("screenTexture", 0);

	quad.render();
}
//-------------------------------------------------------------------FUNCI�N RENDER-------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();

	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);														// Color de la ventana	

	const Shader s_phong("../projects/EJ13_02/phong.vs", "../projects/EJ13_02/blinn.fs");		// Carga del shader de phong
	const Shader s_fbo("../projects/EJ13_02/fbo.vs", "../projects/EJ13_02/fbo.fs");				// Carga del shader de fbo
	const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);		// Textura albedo
	const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);	// Textura specular
	const Quad quad(2.0f);																		// Creación del quad
	const Cube cube(1.0f);																		// Creación del cubo

	auto fbo = createFBO();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Input::instance()->setKeyPressedCallback(onKeyPress);
	Input::instance()->setMouseMoveCallback(onMouseMoved);
	Input::instance()->setScrollMoveCallback(onScrollMoved);

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el �ltimo frame

		handleInput(deltaTime);
		render(quad, cube, s_phong, s_fbo, t_albedo, t_specular, std::get<0>(fbo), std::get<1>(fbo));				// Se renderiza
		window->frame();																		// Se dibuja la ventana
	}

	glDeleteFramebuffers(1, &std::get<0>(fbo));
	glDeleteTextures(1, &std::get<1>(fbo));
	glDeleteRenderbuffers(1, &std::get<2>(fbo));

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////