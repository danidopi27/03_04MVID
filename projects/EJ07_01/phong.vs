/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Phong.vs del ejercicio 7_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;                               // La posición 0 corresponde a posición
layout (location=1) in vec2 aUV;                                // La posición 1 corresponde a textura
layout (location=2) in vec3 aNormal;                            // La posición 2 corresponde a vector normal

uniform mat4 model;                                             // Matriz de espacio mundo
uniform mat4 view;                                              // Matriz de vista
uniform mat4 proj;                                              // Matriz de proyección
uniform mat3 normalMat;											// Matriz de normales
	
out vec3 normal;												// Salida de normal
out vec3 fragPos;												// Salida de posición

void main() {
    normal = normalMat * aNormal;								// Cálculo de normales
    fragPos = vec3(model * vec4(aPos, 1.0));					// Posición
    gl_Position = proj * view * model * vec4(aPos, 1.0);		// Cálculo de posición del elemento
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////