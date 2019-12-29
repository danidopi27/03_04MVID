/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 5_02
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
#include "engine/geometry/cube_05_02.hpp"	// Librer�a de manejo de geometr�a cubo modificada

#include <glm/gtc/matrix_transform.hpp>		// Librer�a de transformaci�n de matrices
#include <GLFW/glfw3.h>						// Librer�a de manejo de GLFW
//------------------------------------------LIBRER�AS------------------------------------------//

//---------------FUNCI�N HANDLEINPUT---------------//
void handleInput() {/*Intentionally Left BLank*/ }
//---------------FUNCI�N HANDLEINPUT---------------//

//--------------------------------------------------------------------FUNCI�N RENDER--------------------------------------------------------------------//
void render(const Geometry& geom, const Shader& shader, Texture& tex) {
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 model = glm::mat4(1.0f);																					// Matriz diagonal
	model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));	// Rotaci�n de la c�mara

	glm::mat4 view = glm::mat4(1.0f);																					// Matriz diagonal
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));															// C�mara acercandose a pantalla

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);								// Perspectiva de la visi�n

	shader.use();																										// Se ejecuta el shader

	tex.use(shader, "tex", 0);																							// Uso de la textura

	shader.set("model", model);																							// Uso de la matriz model
	shader.set("view", view);																							// Uso de la matriz view
	shader.set("proj", proj);																							// Uso de la matriz proj

	geom.render();																										// Se pinta la geometr�a
}
//--------------------------------------------------------------------FUNCI�N RENDER--------------------------------------------------------------------//

//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	const Shader shader("../projects/EJ05_02/vertex.vs", "../projects/EJ05_02/fragment.fs");	// Carga de los shaders
	float center[3] = { 0.0f, 0.0f, 0.0f };														// Coordenadas del centro
	float radio = 0.5f;																			// Radio del cubo
	const Cube_05_02 cube_05_02(center, radio);													// Creaci�n del cubo

	Texture tex("../projects/EJ05_02/EJ05.02_cube_uv_b.jpg", Texture::Format::RGB);				// Creaci�n de la textura

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();																			// Se controlan las entradas
		render(cube_05_02, shader, tex);														// Se renderiza el cubo, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	return 0;
}
//----------------------------------------------------------------FUNCI�N MAIN----------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////FIN DE C�DIGO////////////////////////////////////////////////////////////////////////