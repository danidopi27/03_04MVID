/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Lights.vs del ejercicio 8_02
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Febrero 2020
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

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);		// C�lculo de la posici�n del objeto
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////