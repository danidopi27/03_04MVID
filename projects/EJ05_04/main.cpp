/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 5_04
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////C�DIGO///////////////////////////////////////////////////////////////////////////

//------------------------------------------LIBRER�AS------------------------------------------//
#include <glad/glad.h>						// Librer�a de manejo de GLAD

#include "engine/window.hpp"				// Librer�a de manejo de ventanas
#include "engine/shader.hpp"				// Librer�a de manejo de shaders
#include "engine/texture.hpp"				// Librer�a de manejo de texturas
#include "engine/geometry/cube_05_01.hpp"	// Librer�a de manejo de geometr�a cubo modificada
#include "engine/geometry/quad_05_04.hpp"	// Librer�a de manejo de geometr�a quad modificada

#include <glm/gtc/matrix_transform.hpp>		// Librer�a de transformaci�n de matrices
#include <GLFW/glfw3.h>						// Librer�a de manejo de GLFW
//------------------------------------------LIBRER�AS------------------------------------------//

//---------------FUNCI�N HANDLEINPUT---------------//
void handleInput() {/*Intentionally Left BLank*/ }
//---------------FUNCI�N HANDLEINPUT---------------//

//--------------------------------------------------------------------FUNCI�N RENDER--------------------------------------------------------------------//
void render(const Geometry& cube_1, const Geometry& cube_2, const Geometry& cube_3, const Geometry& suelo, const Shader& shader, Texture& tex) {
	glClear(GL_COLOR_BUFFER_BIT);																					// Borrado de la pantalla

	glm::mat4 model = glm::mat4(1.0f);																				// Matriz diagonal

	glm::mat4 view = glm::mat4(1.0f);																				// Matriz diagonal
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));														// C�mara acercandose a pantalla

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);							// Perspectiva de la visi�n

	shader.use();																									// Se ejecuta el shader

	tex.use(shader, "tex", 0);																						// Uso de la textura

	shader.set("model", model);																						// Uso de la matriz model
	shader.set("view", view);																						// Uso de la matriz view
	shader.set("proj", proj);																						// Uso de la matriz proj

	cube_1.render();																								// Se pinta la geometr�a
	cube_2.render();																								// Se pinta la geometr�a
	cube_3.render();																								// Se pinta la geometr�a
	suelo.render();																									// Se pinta la geometr�a
}
//--------------------------------------------------------------------FUNCI�N RENDER--------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader shader("../projects/EJ05_04/vertex.vs", "../projects/EJ05_04/fragment.fs");	// Carga de los shaders

	float center_1[3] = { -0.5f, 0.0f, 1.0f };													// Coordenadas del centro
	float radio_1 = 0.1f;																		// Radio del cubo
	const Cube_05_01 cube_1(center_1, radio_1);													// Creaci�n del cubo

	float center_2[3] = { 0.25f, 0.0f, 0.0f };													// Coordenadas del centro
	float radio_2 = 0.05f;																		// Radio del cubo
	const Cube_05_01 cube_2(center_2, radio_2);													// Creaci�n del cubo

	float center_3[3] = { 0.25f, 0.75f, 1.0f };													// Coordenadas del centro
	float radio_3 = 0.7f;																		// Radio del cubo
	const Cube_05_01 cube_3(center_3, radio_3);													// Creaci�n del cubo

	float size = 1;
	const Quad_05_04 suelo(size);

	Texture tex("../assets/textures/bricks_specular.png", Texture::Format::RGB);				// Creaci�n de la textura

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();																			// Se controlan las entradas
		render(cube_1, cube_2, cube_3, suelo, shader, tex);										// Se renderiza el cubo, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////FIN DE C�DIGO////////////////////////////////////////////////////////////////////////