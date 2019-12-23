/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Vertex.vs del ejercicio 3_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;               // La posición 0 corresponde a posición
layout (location=1) in vec3 aColor;             // La posición 1 corresponde a color

out vec3 myColor;                               // Salida de color

vec3 aPos_reves;                                // Vector de triángulo al revés

void main() {
    myColor = aColor;                           // Asignación del color para fragment.fs
    aPos_reves.x = aPos.x;                      // La posición x se mantiene
    aPos_reves.y = -1 * aPos.y;                 // La posición y se invierte
    aPos_reves.z = aPos.z;                      // La posición z se mantiene
    gl_Position = vec4(aPos_reves, 1.0);        // Se asigna la posición
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////