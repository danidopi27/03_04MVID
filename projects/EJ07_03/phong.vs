/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Phong.vs del ejercicio 7_01
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;                               // La posici�n 0 corresponde a posici�n
layout (location=1) in vec2 aUV;                                // La posici�n 1 corresponde a textura
layout (location=2) in vec3 aNormal;                            // La posici�n 2 corresponde a vector normal

uniform mat4 model;                                             // Matriz de espacio mundo
uniform mat4 view;                                              // Matriz de vista
uniform mat4 proj;                                              // Matriz de proyecci�n
uniform mat3 normalMat;											// Matriz de normales
	
out vec3 normal;												// Salida de normal
out vec3 fragPos;												// Salida de posici�n

void main() {
    normal = normalMat * aNormal;								// C�lculo de normales
    fragPos = vec3(model * vec4(aPos, 1.0));					// Posici�n
    gl_Position = proj * view * model * vec4(aPos, 1.0);		// C�lculo de posici�n del elemento
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////