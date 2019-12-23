/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Fragments.vs del ejercicio 4_04
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

in vec2 UV;                                                             // Entrada de textura
out vec4 FragColor;                                                     // Salida de fragments

uniform sampler2D tex_1;                                                // Uniform de la textura 1

vec2 UV_2;                                                              // Vector de textura con zoom

void main() {
    UV_2.x = UV.x * 0.25;                                               // Zoom de la textura UV en x
    UV_2.y = UV.y * 0.25;                                               // Zoom de la textura UV en y
    FragColor = texture(tex_1, UV_2);                                   // Se asignan las texturas
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////