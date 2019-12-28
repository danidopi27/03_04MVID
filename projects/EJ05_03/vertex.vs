/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Vertex.vs del ejercicio 5_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;                               // La posición 0 corresponde a posición
layout (location=1) in vec2 aUV;                                // La posición 1 corresponde a textura
layout (location=2) in vec3 aNormal;                            // La posición 2 corresponde a vector normal

out vec2 UV;                                                    // Salida de textura

uniform mat4 model;                                             // Matriz de espacio mundo
uniform mat4 view;                                              // Matriz de vista
uniform mat4 proj;                                              // Matriz de proyección


void main() {
    UV = aUV;                                                   // Asignación de textura para fragment.fs
    gl_Position = proj * model * view * vec4(aPos, 1.0);        // Se asigna la posición transformada
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////