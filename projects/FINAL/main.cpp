/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 9_02
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Febrero 2020
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
//--------------------------------------LIBRERÍAS--------------------------------------//
#include <glad/glad.h>						// Librería de manejo de GLAD
#include <GLFW/glfw3.h>						// Librería de manejo de GLFW
#include <glm/gtc/matrix_transform.hpp>		// Librería de transformaci�n de matrices

#include "engine/camera_FINAL.hpp"
#include "engine/geometry/cube.hpp"			// Librería de manejo de geometr�a cubo
#include "engine/input.hpp"					// Librería de manejo de inputs
#include "engine/shader.hpp"				// Librería de manejo de shaders
#include "engine/texture.hpp"				// Librería de manejo de texturas
#include "engine/window.hpp"				// Librería de manejo de ventanas
#include "engine/geometry/sphere.hpp"		// Librería de manejo de geometría esfera
#include "engine/geometry/quad.hpp"			// Librería de manejo de geometría quad
#include "engine/model.hpp"					// Librería de manejo de modelos

#include <iostream>							// Librería de funciones del sistema
//--------------------------------------LIBRERÍAS--------------------------------------//

//----------------------------------------VARIABLES----------------------------------------//
Camera_FINAL camera(glm::vec3(0.0f, 0.0f, 6.0f));		// Definición de la c�mara
glm::vec3 lightPos(0.0f, 2.0f, 0.0f);					// Posición de la luz
glm::vec3 lightDir(0.0f, 0.0f, -1.0f);					// Dirección de la luz

// Posición de las point lights
glm::vec3 pointLightPositions[] = {
	// Fila 0.5
	glm::vec3(-3.5f, 0.25f, 5.5f),
	glm::vec3(3.5f, 0.25f, 5.5f),
	
	// Fila 1.5
	glm::vec3(0.5f, 0.25f, 4.5f),
	glm::vec3(-0.5f, 0.25f, 4.5f),
	glm::vec3(-5.0f, 0.25, 4.5f),

	// Fila 2.5
	glm::vec3(-3.0f, 0.25f, 3.5f),
	glm::vec3(2.0f, 0.25f, 3.5f),

	// Fila 3.5
	glm::vec3(-3.0f, 0.25f, 2.5f),
	glm::vec3(2.0f, 0.25f, 2.5f),

	// Fila 4
	glm::vec3(4.5f, 0.25f, 2.0f),
	glm::vec3(5.5f, 0.25f, 2.0f),

	// Fila 4.5
	glm::vec3(-3.0f, 0.25f, 1.5f),

	// Fila 5.5
	glm::vec3(-3.0f, 0.25f, 0.5f),
	
	// Fila 6.5
	glm::vec3(-1.0f, 0.25f, -1.5f),
	glm::vec3(3.0f, 0.25f, -1.5f),

	// Fila 7
	glm::vec3(-4.5f, 0.25f, -2.0f),
	glm::vec3(-3.5f, 0.25f, -2.0f),

	// Fila 7.5
	glm::vec3(-1.0f, 0.25f, -2.5f),

	// Fila 8.5
	glm::vec3(3.0f, 0.25f, -3.5f),

	// Fila 9.5
	glm::vec3(3.0f, 0.25f, -4.5f),

	// Fila 11
	glm::vec3(-3.5f, 0.25f, -6.0f),
	glm::vec3(-2.5f, 0.25f, -6.0f),

	// Fila 11
	glm::vec3(-4.0f, 0.25f, -6.5f),
	glm::vec3(-2.0f, 0.25f, -6.5f),
};				

// Posición de las spot lights
glm::vec3 spotLightPositions[] = {
	glm::vec3 (0.0f, 2.0f, 0.0f)
};

// Posición de las paredes del laberinto
glm::vec3 LaberintoPositions[] = {						// Posiciones del cubo
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

glm::vec3 enemyPositions[] = {
	glm::vec3(-6.0f, 0.0f, -5.0f),
	glm::vec3(6.0f, 0.0f, 3.0f),
	glm::vec3(-6.0f, 0.0f, 4.0f)
};

const uint32_t k_shadow_height = 1024;
const uint32_t k_shadow_width = 1024;
const float k_shadow_near = 1.0f;
const float k_shadow_far = 7.5f;

float lastFrame = 0.0f;							// Variable de último frame
float lastX, lastY;								// Variable de última coordenada x, y
bool firstMouse = true;							// Variable de primer movimiento de rat�n
//----------------------------------------VARIABLES----------------------------------------//

//----------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------//
void handleInput(float dt) {
	// Función que maneja las entradas

	Input* input = Input::instance();									// Objeto input

	// Si la tecla W está pulsada
	if (input->isKeyPressed(GLFW_KEY_W)) {
		camera.handleKeyboard(Camera_FINAL::Movement::Forward, dt);		// Movimiento hacia adelante
	}
	// Si la tecla S está pulsada
	if (input->isKeyPressed(GLFW_KEY_S)) {
		camera.handleKeyboard(Camera_FINAL::Movement::Backward, dt);	// Movimiento hacia atrás
	}
	// Si la tecla A está pulsada
	if (input->isKeyPressed(GLFW_KEY_A)) {
		camera.handleKeyboard(Camera_FINAL::Movement::Left, dt);		// Movimiento hacia la izquierda
	}
	// Si la tecla D está pulsada
	if (input->isKeyPressed(GLFW_KEY_D)) {
		camera.handleKeyboard(Camera_FINAL::Movement::Right, dt);		// Movimiento hacia la derecha
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
	// Funci�n que controla el movimiento del rat�n

	// Si es el primer movimiento del rat�n
	if (firstMouse) {
		firstMouse = false;								// Se realizó primer movimiento de ratón
		lastX = x;										// Guardado de la posición de x
		lastY = y;										// Guardado de la posición de y
	}

	const float xoffset = x - lastX;					// Offset en x (posición actual - anterior)
	const float yoffset = lastY - y;					// Offset en x (anterior posición - actual)
	lastX = x;											// Actualizaci�n de la posición anterior en x
	lastY = y;											// Actualizaci�n de la posición anterior en y

	camera.handleMouseMovement(xoffset, yoffset);		// Ajuste del movimiento de la cámara en x, y
}
//----------------------------------------FUNCIÓN ONMOUSEMOVED----------------------------------------//

//----------------------------FUNCIÓN ONSCROLLMOVED----------------------------//
void onScrollMoved(float x, float y) {
	// Función que controla el movimiento scroll

	camera.handleMouseScroll(y);		// Ajuste del movimiento de la cámara 
}
//----------------------------FUNCIÓN ONSCROLLMOVED----------------------------//

//-----------------------------------------------------------FUNCIÓN CREATEFBO-----------------------------------------------------------//
std::pair<uint32_t, uint32_t> createFBO() {
	uint32_t fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	uint32_t depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, k_shadow_width, k_shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[]{ 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer Incomplete" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return std::make_pair(fbo, depthMap);
}
//-----------------------------------------------------------FUNCIÓN CREATEFBO-----------------------------------------------------------//

//-------------------------------------------------------------------FUNCIÓN RENDER-------------------------------------------------------------------//
void render(const Geometry& floor, const Geometry& object, const Geometry& light, const Model& enemy, const Model& coins,
			const Shader& s_phong, const Shader& s_light, const Shader& s_normal, const Shader& s_depth, const Shader& s_debug,
			const Texture& t_albedo, const Texture& t_specular, const Texture& t_normal,
			const uint32_t fbo, const uint32_t fbo_texture) {
	// Función de renderizaci�n

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);													// Borrado de pantalla y profundidad

	glm::mat4 view = camera.getViewMatrix();															// Posición de la vista
	glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);	// Perspectiva de la visión																		

	glm::vec3 lightDiffuse(0.6118f, 0.6118f, 0.6118f);
	glm::vec3 lightColorPoint(0.9804f, 0.8235f, 0.0039f);
	glm::vec3 lightColorSpot(0.6118f, 0.6118f, 0.6118f);

	s_light.use();																						// Se ejecuta la luz

	glm::mat4 model = glm::mat4(1.0f);																	// Posición de la cámara
	model = glm::translate(model, lightPos);															// Traslación con luz
	model = glm::scale(model, glm::vec3(0.25f));														// Escalado
	s_light.set("model", model);																		// Se aplican los cambios al model
	s_light.set("view", view);																			// Se aplican los cambios al view
	s_light.set("proj", proj);																			// Se aplican los cambios al proj
	s_light.set("lightColor", lightDiffuse);															// Se aplican los cambios de color

	light.render();

	s_light.use();

	for (const auto& pointPos : pointLightPositions)
	{
		glm::mat4 model = glm::mat4(1.0f);																// Posición de la c�mara
		model = glm::translate(model, pointPos);														// Traslación con luz
		model = glm::scale(model, glm::vec3(0.05f));													// Escalado
		s_light.set("model", model);																	// Se aplican los cambios al model
		s_light.set("view", view);																		// Se aplican los cambios al view
		s_light.set("proj", proj);																		// Se aplican los cambios al proj
		s_light.set("lightColor", lightColorPoint);														// Se aplican los cambios de color

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
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	s_phong.set("model", model);
	s_phong.set("view", view);
	s_phong.set("proj", proj);

	glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
	s_phong.set("normalMat", normalMat);

	s_phong.set("viewPos", camera.getPosition());

	s_phong.set("dirLight.position", camera.getPosition());
	s_phong.set("dirLight.ambient", 0.02f, 0.02f, 0.02f);
	s_phong.set("dirLight.diffuse", 0.1f, 0.1f, 0.1f);
	s_phong.set("dirLight.specular", 0.2f, 0.2f, 0.2f);

	const std::string prefixPoints = "pointLight[";
	for (uint32_t i = 0; i < sizeof(pointLightPositions); ++i) {
		float factor = i * 0.05;
		const std::string lightName = prefixPoints + std::to_string(i) + "].";
		s_phong.set((lightName + "position").c_str(), pointLightPositions[i]);
		s_phong.set((lightName + "ambient").c_str(), 0.02f, 0.02f, 0.02f);
        s_phong.set((lightName + "diffuse").c_str(), 0.1f, 0.1f, 0.0f);
        s_phong.set((lightName + "specular").c_str(), 0.1f, 0.1f, 0.0f);
        s_phong.set((lightName + "constant").c_str(), 1.0f);
        s_phong.set((lightName + "linear").c_str(), 0.09f);
        s_phong.set((lightName + "quadratic").c_str(), 0.032f);
	}

	const std::string prefixSpots = "spotLight[";
	for (uint32_t i = 0; i < sizeof(spotLightPositions); ++i) {
		float factor = i * 0.10;
		const std::string lightName = prefixSpots + std::to_string(i) + "].";
		s_phong.set((lightName + "position").c_str(), camera.getPosition());
		s_phong.set((lightName + "direction").c_str(), camera.getFront());
		s_phong.set((lightName + "ambient").c_str(), 0.1f, 0.1f, 0.1f);
		s_phong.set((lightName + "diffuse").c_str(), 0.5f, 0.5f, 0.5f);
		s_phong.set((lightName + "specular").c_str(), 1.0f, 1.0f, 1.0f);
		s_phong.set((lightName + "constant").c_str(), 1.0f);
		s_phong.set((lightName + "linear").c_str(), 0.2f);
		s_phong.set((lightName + "quadratic").c_str(), 0.06f);
		s_phong.set((lightName + "cutOff").c_str(), glm::cos(glm::radians(20.0f)));
		s_phong.set((lightName + "outerCutOff").c_str(), glm::cos(glm::radians(25.0f)));
	}

	t_albedo.use(s_phong, "material.diffuse", 0);
	t_specular.use(s_phong, "material.specular", 1);
	s_phong.set("material.shininess", 32);

	floor.render();

	for (const auto& cubePos : LaberintoPositions) {
	
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePos);
		s_phong.set("model", model);

		glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
		s_phong.set("normalMat", normalMat);

		object.render();
	}

	s_normal.use();
	for (const auto& enem : enemyPositions)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, enem);
		model = glm::scale(model, glm::vec3(0.5f));
		s_normal.set("model", model);
		s_normal.set("view", view);
		s_normal.set("proj", proj);

		glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
		s_normal.set("normalMat", normalMat);

		s_normal.set("viewPos", camera.getPosition());
		s_normal.set("light.position", lightPos);
		s_normal.set("material.shininess", 32);

		enemy.render(s_normal);
	}

	{
		s_phong.use();
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		s_phong.set("model", model);
		s_phong.set("view", view);
		s_phong.set("proj", proj);

		normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
		s_phong.set("normalMat", normalMat);

		coins.render(s_phong);
	}
}
//-------------------------------------------------------------------FUNCIÓN RENDER-------------------------------------------------------------------//

//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creación de la ventana

	glClearColor(0.1137f, 0.1176f, 0.2f, 1.0f);													// Color de la ventana

	// Shaders
	const Shader s_phong("../projects/FINAL/phong.vs", "../projects/FINAL/blinn.fs");			// Carga del shader de phong
	const Shader s_light("../projects/FINAL/light.vs", "../projects/FINAL/light.fs");			// Carga del shader de light
	const Shader s_normal("../projects/FINAL/normal.vs", "../projects/FINAL/normal.fs");		// Carga del shader de normal
	const Shader s_depth("../projects/FINAL/depth.vs", "../projects/FINAL/depth.fs");			// Carga del shader de depth
	const Shader s_debug("../projects/FINAL/debug.vs", "../projects/FINAL/debug.fs");			// Carga del shader de debug

	// Texturas
	const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);		// Textura albedo
	const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);	// Textura specular
	const Texture t_normal("../assets/textures/bricks_normal.png", Texture::Format::RGB);		// Textura normal

	// Objetos
	const Sphere sphere(1.0f, 50, 50);															// Creación de esfera
	const Quad quad(1.0f);																		// Creación de quad
	const Cube cube(1.0f);
	const Model enemy("../assets/models/Spider/Only_Spider_with_Animations_Export.obj");		// Creación del modelo
	const Model coins("../assets/models/Cofre/chest.obj");										// Creación del modelo

	auto fbo = createFBO();

	glEnable(GL_CULL_FACE);																		// Activación del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	glEnable(GL_DEPTH_TEST);																	// Activación del cull depth test
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Input::instance()->setKeyPressedCallback(onKeyPress);										// Asociación de callback de tecla pulsada
	Input::instance()->setMouseMoveCallback(onMouseMoved);										// Asociación de callback de rat�n movido
	Input::instance()->setScrollMoveCallback(onScrollMoved);									// Asociación de callback de scroll movido

	// Mientras la ventana siga abierta
	while (window->alive()) {
		const float currentFrame = glfwGetTime();												// Se obtiene el frame actual
		const float deltaTime = currentFrame - lastFrame;										// Se calcula el tiempo transcurrido
		lastFrame = currentFrame;																// Se guarda el último frame

		handleInput(deltaTime);

		render(quad, cube, sphere, enemy, coins,												// Se renderizan los objetos y la luz
			   s_phong, s_light, s_normal, s_depth, s_debug,									// Se renderizan los shaders
			   t_albedo, t_specular, t_normal,													// Se renderizan las texturas
			   fbo.first, fbo.second);
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////