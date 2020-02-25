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

layout (location=0) in vec3 aPos;                               // La posición 0 corresponde a posición
layout (location=1) in vec2 aUV;                                // La posición 1 corresponde a textura
layout (location=2) in vec3 aNormal;                            // La posición 2 corresponde a vector normal

uniform mat4 model;                                             // Matriz de espacio mundo
uniform mat4 view;                                              // Matriz de vista
uniform mat4 proj;                                              // Matriz de posición
uniform mat3 normalMat;											                    // Matriz de normales
	
out vec3 normal;												                        // Salida de normal
out vec3 fragPos;												                        // Salida de posición

void main() {
    normal = normalMat * aNormal;								                // C�lculo de normales
    fragPos = vec3(view * model * vec4(aPos, 1.0));					    // Posición en espacion de vista
    gl_Position = proj * view * model * vec4(aPos, 1.0);		    // C�lculo de posición del elemento
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////