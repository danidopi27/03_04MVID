/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Fragments.vs del ejercicio 4_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

in vec2 UV;                                                             // Entrada de textura
in vec3 myColor;
out vec4 FragColor;                                                     // Salida de fragments

uniform sampler2D tex_1;                                                // Uniform de la textura 1

vec4 textura;                                                           // Vector de textura

void main() {
    textura = texture(tex_1, UV);                                       // Se asignan las texturas
    FragColor.x = textura.x + myColor.x;                                // Se añade a la textura el color en x
    FragColor.y = textura.y + myColor.y;                                // Se añade a la textura el color en y
    FragColor.z = textura.z + myColor.z;                                // Se añade a la textura el color en z
    FragColor.w = textura.w;                                            // Se añade la textura
 }
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////