/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Vertex.vs del ejercicio 3_04
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;               // La posición 0 corresponde a posición
layout (location=1) in vec3 aColor;             // La posición 1 corresponde a color

out vec3 myColor;                               // Salida de color

void main() {
    myColor = aPos;                             // Asignación del color para fragment.fs
    gl_Position = vec4(aPos, 1.0);              // Se asigna la posición
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////