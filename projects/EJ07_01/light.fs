/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Lights.fs del ejercicio 7_01
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;								// Salida de fragments

uniform vec3 lightColor;						// Color de la luz

void main() {
    FragColor = vec4(lightColor, 1.0f);			// Se asigna el color de luz
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////