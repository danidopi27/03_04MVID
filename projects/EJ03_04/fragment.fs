/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Fragments.vs del ejercicio 3_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

in vec3 myColor;                            // Entrada de color
out vec4 FragColor;                         // Salida de fragments

void main() {
    FragColor = vec4(myColor, 1.0);         // Se asigna el color
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////