/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Vertex.vs del ejercicio 3_03
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;               // La posición 1 corresponde a posición
layout (location=1) in vec3 aColor;             // La posición 1 corresponde a color

out vec3 myColor;                               // Salida de color

uniform vec3 desplazamiento;                    // Vector de desplazamiento

vec3 new_aPos = aPos;                           // Vector de nueva posición

void main() {
    myColor = aColor;                           // Asignación del color para fragment.fs
    new_aPos.x = desplazamiento.x + aPos.x;     // Posición en x desplazada respecto a la posición inicial
    gl_Position = vec4(new_aPos, 1.0);          // Se asigna la nueva posición
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////