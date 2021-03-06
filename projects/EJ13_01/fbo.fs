/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: fbo.fs del ejercicio 13_01
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Febrero 2020
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;

void main() {
    FragColor = texture(screenTexture, uv);
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////