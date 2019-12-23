/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Fragments.vs del ejercicio 4_05
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

in vec2 UV;                                                                       // Entrada de textura
out vec4 FragColor;                                                               // Salida de fragments

uniform sampler2D tex_1;                                                          // Uniform de la textura 1
uniform sampler2D tex_2;                                                          // Uniform de la textura 2
uniform float interpolacion;                                                      // Valor de interpolación

void main() {
    FragColor = mix(texture(tex_1, UV), texture(tex_2, UV), interpolacion);       // Se asignan las texturas con el valor de interpolación
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////