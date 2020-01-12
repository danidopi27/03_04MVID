/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 5_04
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
#include "engine/geometry/cube_05_01.hpp"	// Librería de manejo de geometría cubo modificada
#include "engine/geometry/quad.hpp"			// Librería de manejo de geometría quad

#include <glm/gtc/matrix_transform.hpp>		// Librería de transformación de matrices
#include <GLFW/glfw3.h>						// Librería de manejo de GLFW
//------------------------------------------LIBRERÍAS------------------------------------------//

//---------------FUNCIÓN HANDLEINPUT---------------//
void handleInput() {/*Intentionally Left BLank*/ }
//---------------FUNCIÓN HANDLEINPUT---------------//

//--------------------------------------------------------------------FUNCIÓN RENDER--------------------------------------------------------------------//
void render(const Geometry& cube_1, const Geometry& cube_2, const Geometry& cube_3, const Geometry& suelo, const Shader& shader, const Shader& shader_2, Texture& tex) {
	// Función de renderización

	glClear(GL_COLOR_BUFFER_BIT);																					// Borrado de la pantalla

	glm::mat4 model = glm::mat4(1.0f);																				// Matriz diagonal

	glm::mat4 view = glm::mat4(1.0f);																				// Matriz diagonal
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));														// Cámara acercandose a pantalla

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);							// Perspectiva de la visión

	shader.use();																									// Se ejecuta el shader

	tex.use(shader, "tex", 0);																						// Uso de la textura

	shader.set("model", model);																						// Uso de la matriz model
	shader.set("view", view);																						// Uso de la matriz view
	shader.set("proj", proj);																						// Uso de la matriz proj

	cube_1.render();																								// Se pinta la geometría
	cube_2.render();																								// Se pinta la geometría
	cube_3.render();																								// Se pinta la geometría

	glm::mat4 model_2 = glm::mat4(1.0f);																			// Matriz diagonal
	model_2 = glm::rotate(model_2, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view_2 = glm::mat4(1.0f);																				// Matriz diagonal
	view_2 = glm::translate(view_2, glm::vec3(0.0f, 0.0f, -3.0f));													// Cámara acercandose a pantalla

	glm::mat4 proj_2 = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);						// Perspectiva de la visión

	shader_2.use();																									// Se ejecuta el shader

	tex.use(shader_2, "tex", 0);																					// Uso de la textura

	shader_2.set("model", model_2);																						// Uso de la matriz model
	shader_2.set("view", view_2);																						// Uso de la matriz view
	shader_2.set("proj", proj_2);																						// Uso de la matriz proj

	suelo.render();																									// Se pinta la geometría
}
//--------------------------------------------------------------------FUNCIÓN RENDER--------------------------------------------------------------------//

//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader shader("../projects/EJ05_04/vertex.vs", "../projects/EJ05_04/fragment.fs");	// Carga de los shaders
	const Shader shader_2("../projects/EJ05_04/vertex.vs", "../projects/EJ05_04/fragment.fs");	// Carga de los shaders

	float center_1[3] = { -0.5f, 0.0f, 1.0f };													// Coordenadas del centro
	float radio_1 = 0.1f;																		// Radio del cubo
	const Cube_05_01 cube_1(center_1, radio_1);													// Creación del cubo

	float center_2[3] = { 0.25f, 0.0f, 0.0f };													// Coordenadas del centro
	float radio_2 = 0.05f;																		// Radio del cubo
	const Cube_05_01 cube_2(center_2, radio_2);													// Creación del cubo

	float center_3[3] = { 0.25f, 0.75f, 1.0f };													// Coordenadas del centro
	float radio_3 = 0.3f;																		// Radio del cubo
	const Cube_05_01 cube_3(center_3, radio_3);													// Creación del cubo

	const Quad suelo(1.0f);

	Texture tex("../assets/textures/bricks_specular.png", Texture::Format::RGB);				// Creación de la textura

	glEnable(GL_CULL_FACE);																		// Activación del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();																			// Se controlan las entradas
		render(cube_1, cube_2, cube_3, suelo, shader, shader_2, tex);							// Se renderiza el cubo, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCIÓN MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////////