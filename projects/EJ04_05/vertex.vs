/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Vertex.vs del ejercicio 4_05
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;               // La posición 0 corresponde a posición
layout (location=1) in vec3 aColor;             // La posición 1 corresponde a color
layout (location=2) in vec2 aUV;                // La posición 2 corresponde a textura

out vec2 UV;                                    // Salida de textura

void main() {
    UV = aUV;                                   // Asignación de textura para fragment.fs
    gl_Position = vec4(aPos, 1.0);              // Se asigna la posición
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////