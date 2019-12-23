/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Fragments.vs del ejercicio 4_02
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

in vec2 UV;                                                             // Entrada de textura
out vec4 FragColor;                                                     // Salida de fragments

uniform sampler2D tex_1;                                                // Uniform de la textura 1

vec2 UV_2;                                                              // Vector de textura flipeado

void main() {
    UV_2.x = (-1) * UV.x;                                               // Flipeado de la x de la textura
    UV_2.y = (-1) * UV.y;                                               // Flipeado de la y de la textura
    FragColor = texture(tex_1, UV_2);                                   // Se asignan las texturas
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////