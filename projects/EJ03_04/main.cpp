/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 3_04
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////

//-----------------------------LIBRER�AS-----------------------------//
#include <glad/glad.h>			// Librer�a de manejo de GLAD

#include "engine/input.hpp"		// Librer�a de manejo de inputs
#include "engine/window.hpp"	// Librer�a de manejo de ventanas
#include "engine/shader.hpp"	// Librer�a de manejo de shaders

#include <iostream>				// Librer�a de funciones del sistema
//-----------------------------LIBRER�AS-----------------------------//

//----------------------------------------------FUNCI�N HANDLEINPUT----------------------------------------------//
void handleInput() {
	// Funci�n de manejo de entradas
	//std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();	// Obtenci�n de teclas pulsadas
	//for (auto& key : keys) {
	//	std::cout << key.first << " - " << key.second << std::endl;			// Impresi�n de la tecla pulsada
	//}
}
//----------------------------------------------FUNCI�N HANDLEINPUT----------------------------------------------//

//----------------------------------------------------------FUNCI�N CREATEVERTEXDATA----------------------------------------------------------//
uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	// Creaci�n de los v�rtices del tri�ngulo y sus colores
	float vertices[] = {
		// V�rtices				// Colores
		 0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
	};

	// Definici�n del tri�ngulo a partir de los v�rtices
	uint32_t indices[] = {
		0, 2, 1
	};

	uint32_t VAO;																						// Generaci�n del VAO
	glGenVertexArrays(1, &VAO);																			// Asignaci�n de ID al VAO
	glGenBuffers(1, VBO);																				// Generaci�n del VBO
	glGenBuffers(1, EBO);																				// Generaci�n del EBO

	glBindVertexArray(VAO);																				// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);																// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);							// Se sube la informaci�n

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);														// Se genera el buffer de EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);					// Se sube la informaci�n

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);						// Se establece el puntero de v�rtices
	glEnableVertexAttribArray(0);																		// Habilitado

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));		// Se establece el puntero de colores
	glEnableVertexAttribArray(1);																		// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);																	// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);															// Se desbindea el buffer

	return VAO;																							// Se retorna el VAO
}
//----------------------------------------------------------FUNCI�N CREATEVERTEXDATA----------------------------------------------------------//

//------------------------------------------FUNCI�N RENDER------------------------------------------//
void render(uint32_t VAO, const Shader& shader) {
	// Renderizaci�n del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	shader.use();													// Se ejecuta el shader

	glBindVertexArray(VAO);											// Se asigna el VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);		// Se dibujan los elementos
}
//------------------------------------------FUNCI�N RENDER------------------------------------------//

//--------------------------------------------------------------FUNCI�N MAIN--------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	uint32_t VBO, EBO;																			// Creaci�n del VBO y el EBO
	const uint32_t VAO = createVertexData(&VBO, &EBO);											// Creaci�n de los v�rtices
	const Shader shader("../projects/EJ03_04/vertex.vs", "../projects/EJ03_04/fragment.fs");	// Carga de los shaders

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);													// Modo polygon para las lineas y relleno

	glEnable(GL_CULL_FACE);																		// Activaci�n de ocultaci�n de caras
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
//--------------------------------------------------------------FUNCI�N MAIN--------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE C�DIGO////////////////////////////////////////////////////////////////////