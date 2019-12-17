/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Ejercicio 2_02
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

//---------------------------------------------FUNCI�N CREATEPROGRAM---------------------------------------------//
uint32_t createProgram() {
	// Funci�n de creaci�n de programa
	const char* vertexShaderSource = "#version 330 core\n"					// C�digo fuente del vertex shader
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"    gl_Position = vec4(aPos, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"				// C�digo fuente del fragment shader
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
//---------------------------------------------FUNCI�N CREATEPROGRAM---------------------------------------------//

//------------------------------------------FUNCI�N CREATEVERTEXDATA_TRIANGLE1------------------------------------------//
uint32_t createVertexData_triangle1(uint32_t* VBO) {
	// Creaci�n de los vertices del segundo tri�ngulo

	// V�rtices de los tri�ngulos
	float vertices[] = {
		// Primer tri�ngulo
		0.5f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		0.25f, 0.5f, 0.0f,

	};

	uint32_t VAO;																		// Generaci�n del VAO
	glGenVertexArrays(1, &VAO);															// Asignaci�n de ID al VAO
	glGenBuffers(1, VBO);																// Generaci�n del VBO

	glBindVertexArray(VAO);																// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);												// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// Se sube la informaci�n

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);		// Se establece el puntero
	glEnableVertexAttribArray(0);														// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);													// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);											// Se desbindea el buffer

	return VAO;																			// Se retorna el VAO
}
//------------------------------------------FUNCI�N CREATEVERTEXDATA_TRIANGLE1------------------------------------------//

//------------------------------------------FUNCI�N CREATEVERTEXDATA_TRIANGLE2------------------------------------------//
uint32_t createVertexData_triangle2(uint32_t* VBO) {
	// Creaci�n de los vertices del segundo tri�ngulo

	// V�rtices de los tri�ngulos
	float vertices[] = {
		0.0f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f,
	};

	uint32_t VAO;																		// Generaci�n del VAO
	glGenVertexArrays(1, &VAO);															// Asignaci�n de ID al VAO
	glGenBuffers(1, VBO);																// Generaci�n del VBO

	glBindVertexArray(VAO);																// Bindeado del VAO

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);												// Se genera el buffer de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);			// Se sube la informaci�n

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);		// Se establece el puntero
	glEnableVertexAttribArray(0);														// Habilitado

	glBindBuffer(GL_ARRAY_BUFFER, 0);													// Se desbindea el buffer

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);											// Se desbindea el buffer

	return VAO;																			// Se retorna el VAO
}
//------------------------------------------FUNCI�N CREATEVERTEXDATA_TRIANGLE2------------------------------------------//

//----------------------------------------FUNCI�N RENDER----------------------------------------//
void render(uint32_t VAO_1, uint32_t VAO_2, uint32_t program) {
	// Renderizaci�n del VAO en el programa
	glClear(GL_COLOR_BUFFER_BIT);									// Se borra el buffer

	glUseProgram(program);											// Se asigna el program
	glBindVertexArray(VAO_1);										// Se asigna el VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);								// Se dibujan los elementos
	glBindVertexArray(VAO_2);										// Se asigna el VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);								// Se dibujan los elementos
}
//----------------------------------------FUNCI�N RENDER----------------------------------------//

//-------------------------------------------------FUNCI�N MAIN-------------------------------------------------//
int main(int, char* []) {
	Window* window = Window::instance();							// Creaci�n de la ventana

	glClearColor(0.0f, 0.3f, 0.6f, 1.0f);							// Color de la ventana

	uint32_t VBO_t1, VBO_t2;										// Creaci�n del VBO de los tri�ngulos 1 y 2
	const uint32_t VAO_t1 = createVertexData_triangle1(&VBO_t1);	// Creaci�n de los v�rtices del tri�ngulo 1
	const uint32_t VAO_t2 = createVertexData_triangle2(&VBO_t2);	// Creaci�n de los v�rtices del tri�ngulo 1
	const uint32_t program = createProgram();						// Se crea un programa

	// Mientras la ventana siga abierta
	while (window->alive()) {
		handleInput();												// Se controlan las entradas
		render(VAO_t1, VAO_t2, program);							// Se renderiza el VAO en el program
		window->frame();											// Se dibuja la ventana
	}

	glDeleteVertexArrays(1, &VAO_t1);								// Borrado del VAO del tri�ngulo 1
	glDeleteVertexArrays(1, &VAO_t2);								// Borrado del VAO del tri�ngulo 2
	glDeleteBuffers(1, &VBO_t1);									// Borrado del VBO del tri�ngulo 1
	glDeleteBuffers(1, &VBO_t2);									// Borrado del VBO del tri�ngulo 2

	glDeleteProgram(program);										// Borrado de programa

	return 0;
}
//-------------------------------------------------FUNCI�N MAIN-------------------------------------------------//

////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////