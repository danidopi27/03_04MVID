/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 5_02
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////CÓDIGO///////////////////////////////////////////////////////////////////////////

//------------------------------------------LIBRERÍAS------------------------------------------//
#include <glad/glad.h>						// Librería de manejo de GLAD

#include "engine/window.hpp"				// Librería de manejo de ventanas
#include "engine/shader.hpp"				// Librería de manejo de shaders
#include "engine/texture.hpp"				// Librería de manejo de texturas
#include "engine/geometry/cube_05_02.hpp"	// Librería de manejo de geometría cubo modificada

#include <glm/gtc/matrix_transform.hpp>		// Librería de transformación de matrices
#include <GLFW/glfw3.h>						// Librería de manejo de GLFW
//------------------------------------------LIBRERÍAS------------------------------------------//

//---------------FUNCIÓN HANDLEINPUT---------------//
void handleInput() {/*Intentionally Left BLank*/ }
//---------------FUNCIÓN HANDLEINPUT---------------//

//--------------------------------------------------------------------FUNCIÓN RENDER--------------------------------------------------------------------//
void render(const Geometry& geom, const Shader& shader, Texture& tex) {
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);																					// Matriz diagonal
	model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));	// Rotación de la cámara

	glm::mat4 view = glm::mat4(1.0f);																					// Matriz diagonal
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));															// Cámara acercandose a pantalla

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);								// Perspectiva de la visión

	shader.use();																										// Se ejecuta el shader

	tex.use(shader, "tex", 0);																							// Uso de la textura

	shader.set("model", model);																							// Uso de la matriz model
	shader.set("view", view);																							// Uso de la matriz view
	shader.set("proj", proj);																							// Uso de la matriz proj

	geom.render();																										// Se pinta la geometría
}
//--------------------------------------------------------------------FUNCIÓN RENDER--------------------------------------------------------------------//

//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader shader("../projects/EJ05_02/vertex.vs", "../projects/EJ05_02/fragment.fs");	// Carga de los shaders
	float center[3] = { 0.0f, 0.0f, 0.0f };														// Coordenadas del centro
	float radio = 0.5f;																			// Radio del cubo
	const Cube_05_02 cube_05_02(center, radio);													// Creación del cubo

	Texture tex("../projects/EJ05_02/EJ05.02_cube_uv_b.jpg", Texture::Format::RGB);				// Creación de la textura

	glEnable(GL_CULL_FACE);																		// Activación del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();																			// Se controlan las entradas
		render(cube_05_02, shader, tex);														// Se renderiza el cubo, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////////