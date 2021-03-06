/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 4_04
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////

//-------------------------------LIBRER�AS-------------------------------//
#include <glad/glad.h>				// Librer�a de manejo de GLAD

#include "engine/window.hpp"		// Librer�a de manejo de ventanas
#include "engine/shader.hpp"		// Librer�a de manejo de shaders

#include <iostream>					// Librer�a de funciones del sistema

#define STB_IMAGE_IMPLEMENTATION	// Definici�n para uso de im�genes
#include <stb_image.h>				// Librer�a de manejo de shaders
//-------------------------------LIBRER�AS-------------------------------//

//---------------FUNCI�N HANDLEINPUT---------------//
void handleInput() {/*Intentionally Left BLank*/ }
//---------------FUNCI�N HANDLEINPUT---------------//

//----------------------------------------------------------FUNCI�N CREATEVERTEXDATA----------------------------------------------------------//
uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	// Creaci�n de los v�rtices del tri�ngulo y sus colores
	float vertices[] = {
		// V�rtices			   // Colores		   // Texturas
		 0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	};

	// Definici�n del tri�ngulo a partir de los v�rtices
	uint32_t indices[] = {
		0, 3, 1,
		1, 3, 2
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);						// Se establece el puntero de v�rtices
	glEnableVertexAttribArray(0);																		// Habilitado

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));		// Se establece el puntero de colores
	glEnableVertexAttribArray(1);																		// Habilitado

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));		// Se establece el puntero de texturas
	glEnableVertexAttribArray(2);																		// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);																	// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);															// Se desbindea el buffer

	return VAO;																							// Se retorna el VAO
}
//----------------------------------------------------------FUNCI�N CREATEVERTEXDATA----------------------------------------------------------//

//------------------------------------------------------------FUNCI�N CREATETEXTURE------------------------------------------------------------//
uint32_t createTexture(const char* path) {
	// Funci�n de creaci�n de textura
	uint32_t texture;																					// Variable de textura
	glGenTextures(1, &texture);																			// Asignaci�n de ID
	glBindTexture(GL_TEXTURE_2D, texture);																// Asociaci�n a 2D

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);										// Configuraci�n textura en S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);										// Configuraci�n textura en T										

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);									// Configuraci�n de filtrado linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);									// Configuraci�n de filtrado linear

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);								// Configuraci�n de filtrado nearest
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);								// Configuraci�n de filtrado nearest

	int width, height, nChannels;																		// Variables de la imagen
	unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);								// Conversi�n de imagen

	// Si existen datos en la imagen
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);		// Se asocian la imagen a la textura
		glGenerateMipmap(GL_TEXTURE_2D);																// Se genera el mipmap
		stbi_image_free(data);																			// Se libera la memoria
	}

	// Si se produce alg�n error con la imagen
	else {
		std::cout << "Error loading texture " << path << std::endl;										// Mensaje de error
	}

	return texture;																						// Se retorna la textura
}
//------------------------------------------------------------FUNCI�N CREATETEXTURE------------------------------------------------------------//

//-----------------------------------------------FUNCI�N RENDER-----------------------------------------------//
void render(uint32_t VAO, const Shader& shader, uint32_t tex1) {
	// Renderizaci�n del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	shader.use();													// Se ejecuta el shader
	glBindVertexArray(VAO);											// Se asigna el VAO

	glActiveTexture(GL_TEXTURE0);									// Se activa la textura 1
	glBindTexture(GL_TEXTURE_2D, tex1);								// Se asigna la textura 1

	shader.set("tex_1", 0);											// Se pasa la textura 1 al shader

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);		// Se dibujan los elementos
}
//-----------------------------------------------FUNCI�N RENDER-----------------------------------------------//

//---------------------------------------------------------------FUNCI�N MAIN---------------------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();														// Creaci�n de la ventana

	stbi_set_flip_vertically_on_load(true);														// Imagen flipeada

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);														// Color de la ventana

	uint32_t VBO, EBO;																			// Creaci�n del VBO y el EBO
	const uint32_t VAO = createVertexData(&VBO, &EBO);											// Creaci�n de los v�rtices
	const Shader shader("../projects/EJ04_04/vertex.vs", "../projects/EJ04_04/fragment.fs");	// Carga de los shaders

	uint32_t tex1 = createTexture("../assets/textures/bricks_arrow.jpg");						// Creaci�n de la textura 1

	glEnable(GL_CULL_FACE);																		// Activaci�n del cull face
	glCullFace(GL_BACK);																		// Ocultar la cara trasera

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();																			// Se controlan las entradas
		render(VAO, shader, tex1);																// Se renderiza el VAO, shader y texturas
		window->frame();																		// Se dibuja la ventana
	}

	glDeleteVertexArrays(1, &VAO);																// Borrado del VAO
	glDeleteBuffers(1, &VBO);																	// Borrado del VBO
	glDeleteBuffers(1, &EBO);																	// Borrado del EBO

	return 0;
}
//---------------------------------------------------------------FUNCI�N MAIN---------------------------------------------------------------//

////////////////////////////////////////////////////////////////////FIN DE C�DIGO////////////////////////////////////////////////////////////////////