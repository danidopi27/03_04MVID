/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 2_05
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////

//-----------------------------LIBRERÍAS-----------------------------//
#include <glad/glad.h>			// Librería de manejo de GLAD
#include <GLFW/glfw3.h>			// Librería de manejo de GLFW

#include "engine/input.hpp"		// Librería de manejo de inputs
#include "engine/window.hpp"	// Librería de manejo de ventanas

#include <iostream>				// Librería de funciones del sistema

#include <stdio.h>
#include <math.h>
//-----------------------------LIBRERÍAS-----------------------------//

//----------------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------------//
void handleInput() {
	// Función de manejo de entradas
	std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();	// Obtención de teclas pulsadas
	for (auto& key : keys) {
		std::cout << key.first << " - " << key.second << std::endl;			// Impresión de la tecla pulsada
	}
}
//----------------------------------------------FUNCIÓN HANDLEINPUT----------------------------------------------//

//--------------------------------------------FUNCIÓN CHECKSHADER--------------------------------------------//
bool checkShader(uint32_t shader) {
	// Comprobación del shader
	int success;															// Varialbe de éxito
	char infoLog[512];														// Variable log
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);						// Status del shader
	// Si no se creó el shader
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);					// Se obtiene mensaje de error
		std::cout << "Error Compiling Shader " << infoLog << std::endl;		// Se imprime el mensaje
		return false;														// Se retorna false
	}
	// Si se creó el shader
	return true;															// Se retorna true
}
//--------------------------------------------FUNCIÓN CHECKSHADER--------------------------------------------//

//-------------------------------------------FUNCIÓN CHECKPROGRAM-------------------------------------------//
bool checkProgram(uint32_t program) {
	// Comprobación del programa
	int success;															// Varialbe de éxito
	char infoLog[512];														// Variable log
	glGetProgramiv(program, GL_LINK_STATUS, &success);						// Se obtiene mensaje de error
	// Si no se creó el programa
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, infoLog);				// Se obtiene mensaje de error
		std::cout << "Error Linking Program " << infoLog << std::endl;		// Se imprime el mensaje
		return false;														// Se retorna false
	}
	// Si se creó el programa
	return true;															// Se retorna true
}
//-------------------------------------------FUNCIÓN CHECKPROGRAM-------------------------------------------//

//---------------------------------------FUNCIÓN CREATEPROGRAM---------------------------------------//
uint32_t createProgram() {
	// Función de creación de programa

	// Código fuente del vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}\0";
	// Código fuente del fragment shader
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

	const uint32_t program = glCreateProgram();								// Creación del programa
	glAttachShader(program, vertexShader);									// Se asigna un shader
	glAttachShader(program, fragmentShader);								// Se asigna un shader
	glLinkProgram(program);													// Se unen al programa
	checkProgram(program);													// Comprobar programa

	glDeleteShader(vertexShader);											// Borrado de shader
	glDeleteShader(fragmentShader);											// Borrado de shader

	return program;															// Se retorna programa
}
//---------------------------------------FUNCIÓN CREATEPROGRAM---------------------------------------//

//-----------------------------------------------FUNCIÓN CREATEVERTEXDATA-----------------------------------------------//
uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
	// Creación de los vertices de los triangulos
	float coord_y = sqrt(3)/4;
	// Vértices de los triángulos
	float vertices[] = {
		  0.0f,     0.0f, 0.0f,
		  0.5f,     0.0f, 0.0f,	// Vértice 0
		 0.25f,  coord_y, 0.0f,	// Vértice 1
		-0.25f,  coord_y, 0.0f,	// Vértice 2
		 -0.5f,     0.0f, 0.0f,	// Vértice 3
		-0.25f, -coord_y, 0.0f,	// Vértice 4
		 0.25f, -coord_y, 0.0f		// Vértice 5
	};

	// Definición de los triángulos a partir de los vértices
	uint32_t indices[] = {
		2, 0, 1,																		// Primer triángulo
		2, 3, 0,																		// Segundo triángulo
		3, 4, 0,																		// Tercer triángulo
		4, 5, 0,																		// Cuarto triángulo
		0, 5, 6,
		0, 6, 1
	};

	uint32_t VAO;																		// Generación del VAO
	glGenVertexArrays(1, &VAO);															// Asignación de ID al VAO
	glGenBuffers(1, VBO);																// Generación del VBO
	glGenBuffers(1, EBO);																// Generación del EBO

	glBindVertexArray(VAO);																// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);												// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// Se sube la información

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);										// Se genera el buffer de EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);	// Se sube la información

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);		// Se establece el puntero
	glEnableVertexAttribArray(0);														// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);													// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);											// Se desbindea el buffer

	return VAO;																			// Se retorna el VAO
}
//-----------------------------------------------FUNCIÓN CREATEVERTEXDATA-----------------------------------------------//

//----------------------------------------FUNCIÓN RENDER----------------------------------------//
void render(uint32_t VAO, uint32_t program) {
	// Renderización del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	glUseProgram(program);											// Se asigna el program
	glBindVertexArray(VAO);											// Se asigna el VAO
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);		// Se dibujan los elementos
}
//----------------------------------------FUNCIÓN RENDER----------------------------------------//

//-------------------------------------------------FUNCIÓN MAIN-------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();					// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);					// Color de la ventana

	uint32_t VBO, EBO;										// Creación del VBO y el EBO
	const uint32_t VAO = createVertexData(&VBO, &EBO);		// Creación de los vértices
	const uint32_t program = createProgram();				// Se crea un programa

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);				// Modo polygon para mostrar las lineas y relleno

	glEnable(GL_CULL_FACE);									// Activación de ocultación de caras
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
//-------------------------------------------------FUNCIÓN MAIN-------------------------------------------------//

////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////