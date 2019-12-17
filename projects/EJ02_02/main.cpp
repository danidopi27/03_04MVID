/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Ejercicio 2_02
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

//---------------------------------------------FUNCIÓN CREATEPROGRAM---------------------------------------------//
uint32_t createProgram() {
	// Función de creación de programa
	const char* vertexShaderSource = "#version 330 core\n"					// Código fuente del vertex shader
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"				// Código fuente del fragment shader
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
//---------------------------------------------FUNCIÓN CREATEPROGRAM---------------------------------------------//

//------------------------------------------FUNCIÓN CREATEVERTEXDATA_TRIANGLE1------------------------------------------//
uint32_t createVertexData_triangle1(uint32_t* VBO) {
	// Creación de los vertices del segundo triángulo

	// Vértices de los triángulos
	float vertices[] = {
		// Primer triángulo
		0.5f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.25f, 0.5f, 0.0f,

	};

	uint32_t VAO;																		// Generación del VAO
	glGenVertexArrays(1, &VAO);															// Asignación de ID al VAO
	glGenBuffers(1, VBO);																// Generación del VBO

	glBindVertexArray(VAO);																// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);												// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// Se sube la información

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);		// Se establece el puntero
	glEnableVertexAttribArray(0);														// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);													// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);											// Se desbindea el buffer

	return VAO;																			// Se retorna el VAO
}
//------------------------------------------FUNCIÓN CREATEVERTEXDATA_TRIANGLE1------------------------------------------//

//------------------------------------------FUNCIÓN CREATEVERTEXDATA_TRIANGLE2------------------------------------------//
uint32_t createVertexData_triangle2(uint32_t* VBO) {
	// Creación de los vertices del segundo triángulo

	// Vértices de los triángulos
	float vertices[] = {
		0.0f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f,
	};

	uint32_t VAO;																		// Generación del VAO
	glGenVertexArrays(1, &VAO);															// Asignación de ID al VAO
	glGenBuffers(1, VBO);																// Generación del VBO

	glBindVertexArray(VAO);																// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);												// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// Se sube la información

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);		// Se establece el puntero
	glEnableVertexAttribArray(0);														// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);													// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);											// Se desbindea el buffer

	return VAO;																			// Se retorna el VAO
}
//------------------------------------------FUNCIÓN CREATEVERTEXDATA_TRIANGLE2------------------------------------------//

//----------------------------------------FUNCIÓN RENDER----------------------------------------//
void render(uint32_t VAO_1, uint32_t VAO_2, uint32_t program) {
	// Renderización del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	glUseProgram(program);											// Se asigna el program
	glBindVertexArray(VAO_1);										// Se asigna el VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);								// Se dibujan los elementos
	glBindVertexArray(VAO_2);										// Se asigna el VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);								// Se dibujan los elementos
}
//----------------------------------------FUNCIÓN RENDER----------------------------------------//

//-------------------------------------------------FUNCIÓN MAIN-------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();							// Creación de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);							// Color de la ventana

	uint32_t VBO_t1, VBO_t2;										// Creación del VBO de los triángulos 1 y 2
	const uint32_t VAO_t1 = createVertexData_triangle1(&VBO_t1);	// Creación de los vértices del triángulo 1
	const uint32_t VAO_t2 = createVertexData_triangle2(&VBO_t2);	// Creación de los vértices del triángulo 1
	const uint32_t program = createProgram();						// Se crea un programa

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();												// Se controlan las entradas
		render(VAO_t1, VAO_t2, program);							// Se renderiza el VAO en el program
		window->frame();											// Se dibuja la ventana
	}

	glDeleteVertexArrays(1, &VAO_t1);								// Borrado del VAO del triángulo 1
	glDeleteVertexArrays(1, &VAO_t2);								// Borrado del VAO del triángulo 2
	glDeleteBuffers(1, &VBO_t1);									// Borrado del VBO del triángulo 1
	glDeleteBuffers(1, &VBO_t2);									// Borrado del VBO del triángulo 2

	glDeleteProgram(program);										// Borrado de programa

	return 0;
}
//-------------------------------------------------FUNCIÓN MAIN-------------------------------------------------//

////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////