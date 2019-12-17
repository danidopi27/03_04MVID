/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 2_05
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////

//-----------------------------LIBRER�AS-----------------------------//
#include <glad/glad.h>			// Librer�a de manejo de GLAD
#include <GLFW/glfw3.h>			// Librer�a de manejo de GLFW

#include "engine/input.hpp"		// Librer�a de manejo de inputs
#include "engine/window.hpp"	// Librer�a de manejo de ventanas

#include <iostream>				// Librer�a de funciones del sistema

#include <stdio.h>
#include <math.h>
//-----------------------------LIBRER�AS-----------------------------//

//----------------------------------------------FUNCI�N HANDLEINPUT----------------------------------------------//
void handleInput() {
	// Funci�n de manejo de entradas
	std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();	// Obtenci�n de teclas pulsadas
	for (auto& key : keys) {
		std::cout << key.first << " - " << key.second << std::endl;			// Impresi�n de la tecla pulsada
	}
}
//----------------------------------------------FUNCI�N HANDLEINPUT----------------------------------------------//

//--------------------------------------------FUNCI�N CHECKSHADER--------------------------------------------//
bool checkShader(uint32_t shader) {
	// Comprobaci�n del shader
	int success;															// Varialbe de �xito
	char infoLog[512];														// Variable log
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);						// Status del shader
	// Si no se cre� el shader
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);					// Se obtiene mensaje de error
		std::cout << "Error Compiling Shader " << infoLog << std::endl;		// Se imprime el mensaje
		return false;														// Se retorna false
	}
	// Si se cre� el shader
	return true;															// Se retorna true
}
//--------------------------------------------FUNCI�N CHECKSHADER--------------------------------------------//

//-------------------------------------------FUNCI�N CHECKPROGRAM-------------------------------------------//
bool checkProgram(uint32_t program) {
	// Comprobaci�n del programa
	int success;															// Varialbe de �xito
	char infoLog[512];														// Variable log
	glGetProgramiv(program, GL_LINK_STATUS, &success);						// Se obtiene mensaje de error
	// Si no se cre� el programa
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);				// Se obtiene mensaje de error
		std::cout << "Error Linking Program " << infoLog << std::endl;		// Se imprime el mensaje
		return false;														// Se retorna false
	}
	// Si se cre� el programa
	return true;															// Se retorna true
}
//-------------------------------------------FUNCI�N CHECKPROGRAM-------------------------------------------//

//---------------------------------------FUNCI�N CREATEPROGRAM---------------------------------------//
uint32_t createProgram() {
	// Funci�n de creaci�n de programa

	// C�digo fuente del vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}\0";
	// C�digo fuente del fragment shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"    FragColor = vec4(0.6, 0.6, 0.1, 1.0);\n"
		"}\0";

	const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);			// Generar shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);			// Subir los datos
	glCompileShader(vertexShader);											// Compilar el shader
	checkShader(vertexShader);												// Comprobar shader

	const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// Generar shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);		// Subir los datos
	glCompileShader(fragmentShader);										// Compilar el shader
	checkShader(fragmentShader);											// Comprobar shader

	const uint32_t program = glCreateProgram();								// Creaci�n del programa
	glAttachShader(program, vertexShader);									// Se asigna un shader
	glAttachShader(program, fragmentShader);								// Se asigna un shader
	glLinkProgram(program);													// Se unen al programa
	checkProgram(program);													// Comprobar programa

	glDeleteShader(vertexShader);											// Borrado de shader
	glDeleteShader(fragmentShader);											// Borrado de shader

	return program;															// Se retorna programa
}
//---------------------------------------FUNCI�N CREATEPROGRAM---------------------------------------//

//-----------------------------------------------FUNCI�N CREATEVERTEXDATA-----------------------------------------------//
uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	// Creaci�n de los vertices de los triangulos
	float coord_y = sqrt(3)/4;
	// V�rtices de los tri�ngulos
	float vertices[] = {
		  0.0f,     0.0f, 0.0f,
		  0.5f,     0.0f, 0.0f,	// V�rtice 0
		 0.25f,  coord_y, 0.0f,	// V�rtice 1
		-0.25f,  coord_y, 0.0f,	// V�rtice 2
		 -0.5f,     0.0f, 0.0f,	// V�rtice 3
		-0.25f, -coord_y, 0.0f,	// V�rtice 4
		 0.25f, -coord_y, 0.0f		// V�rtice 5
	};

	// Definici�n de los tri�ngulos a partir de los v�rtices
	uint32_t indices[] = {
		2, 0, 1,																		// Primer tri�ngulo
		2, 3, 0,																		// Segundo tri�ngulo
		3, 4, 0,																		// Tercer tri�ngulo
		4, 5, 0,																		// Cuarto tri�ngulo
		0, 5, 6,
		0, 6, 1
	};

	uint32_t VAO;																		// Generaci�n del VAO
	glGenVertexArrays(1, &VAO);															// Asignaci�n de ID al VAO
	glGenBuffers(1, VBO);																// Generaci�n del VBO
	glGenBuffers(1, EBO);																// Generaci�n del EBO

	glBindVertexArray(VAO);																// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);												// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// Se sube la informaci�n

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);										// Se genera el buffer de EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	// Se sube la informaci�n

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);		// Se establece el puntero
	glEnableVertexAttribArray(0);														// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);													// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);											// Se desbindea el buffer

	return VAO;																			// Se retorna el VAO
}
//-----------------------------------------------FUNCI�N CREATEVERTEXDATA-----------------------------------------------//

//----------------------------------------FUNCI�N RENDER----------------------------------------//
void render(uint32_t VAO, uint32_t program) {
	// Renderizaci�n del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	glUseProgram(program);											// Se asigna el program
	glBindVertexArray(VAO);											// Se asigna el VAO
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);		// Se dibujan los elementos
}
//----------------------------------------FUNCI�N RENDER----------------------------------------//

//-------------------------------------------------FUNCI�N MAIN-------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();					// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);					// Color de la ventana

	uint32_t VBO, EBO;										// Creaci�n del VBO y el EBO
	const uint32_t VAO = createVertexData(&VBO, &EBO);		// Creaci�n de los v�rtices
	const uint32_t program = createProgram();				// Se crea un programa

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);				// Modo polygon para mostrar las lineas y relleno

	glEnable(GL_CULL_FACE);									// Activaci�n de ocultaci�n de caras
	glCullFace(GL_BACK);									// Ocultadas las caras traseras

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();										// Se controlan las entradas
		render(VAO, program);								// Se renderiza el VAO en el program
		window->frame();									// Se dibuja la ventana
	}

	glDeleteVertexArrays(1, &VAO);							// Borrado del VAO
	glDeleteBuffers(1, &VBO);								// Borrado del VBO
	glDeleteBuffers(1, &EBO);								// Borrado del EBO

	glDeleteProgram(program);								// Borrado de programa

	return 0;
}
//-------------------------------------------------FUNCI�N MAIN-------------------------------------------------//

////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////