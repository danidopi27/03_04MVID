/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 3_04
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////

//-----------------------------LIBRERÍAS-----------------------------//
#include <glad/glad.h>			// Librería de manejo de GLAD

#include "engine/input.hpp"		// Librería de manejo de inputs
#include "engine/window.hpp"	// Librería de manejo de ventanas
#include "engine/shader.hpp"	// Librería de manejo de shaders

#include <iostream>				// Librería de funciones del sistema
//-----------------------------LIBRERÍAS-----------------------------//

//----------------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------------//
void handleInput() {
	// Función de manejo de entradas
	//std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();	// Obtención de teclas pulsadas
	//for (auto& key : keys) {
	//	std::cout << key.first << " - " << key.second << std::endl;			// Impresión de la tecla pulsada
	//}
}
//----------------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------------//

//----------------------------------------------------------FUNCIÓN CREATEVERTEXDATA----------------------------------------------------------//
uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	// Creación de los vértices del triángulo y sus colores
	float vertices[] = {
		// Vértices				// Colores
		 0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
	};

	// Definición del triángulo a partir de los vértices
	uint32_t indices[] = {
		0, 2, 1
	};

	uint32_t VAO;																						// Generación del VAO
	glGenVertexArrays(1, &VAO);																			// Asignación de ID al VAO
	glGenBuffers(1, VBO);																				// Generación del VBO
	glGenBuffers(1, EBO);																				// Generación del EBO

	glBindVertexArray(VAO);																				// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);																// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);							// Se sube la información

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);														// Se genera el buffer de EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);					// Se sube la información

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);						// Se establece el puntero de vértices
	glEnableVertexAttribArray(0);																		// Habilitado

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));		// Se establece el puntero de colores
	glEnableVertexAttribArray(1);																		// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);																	// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);															// Se desbindea el buffer

	return VAO;																							// Se retorna el VAO
}
//----------------------------------------------------------FUNCIÓN CREATEVERTEXDATA----------------------------------------------------------//

//------------------------------------------FUNCIÓN RENDER------------------------------------------//
void render(uint32_t VAO, const Shader& shader) {
	// Renderización del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	shader.use();													// Se ejecuta el shader

	glBindVertexArray(VAO);											// Se asigna el VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);		// Se dibujan los elementos
}
//------------------------------------------FUNCIÓN RENDER------------------------------------------//

//--------------------------------------------------------------FUNCIÓN MAIN--------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	uint32_t VBO, EBO;																			// Creación del VBO y el EBO
	const uint32_t VAO = createVertexData(&VBO, &EBO);											// Creación de los vértices
	const Shader shader("../projects/EJ03_04/vertex.vs", "../projects/EJ03_04/fragment.fs");	// Carga de los shaders

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);													// Modo polygon para las lineas y relleno

	glEnable(GL_CULL_FACE);																		// Activación de ocultación de caras
	glCullFace(GL_BACK);																		// Ocultadas las caras traseras

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();																			// Se controlan las entradas
		render(VAO, shader);																	// Se renderiza el VAO con el shader
		window->frame();																		// Se dibuja la ventana
	}

	glDeleteVertexArrays(1, &VAO);																// Borrado del VAO
	glDeleteBuffers(1, &VBO);																	// Borrado del VBO
	glDeleteBuffers(1, &EBO);																	// Borrado del EBO

	return 0;
}
//--------------------------------------------------------------FUNCIÓN MAIN--------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////