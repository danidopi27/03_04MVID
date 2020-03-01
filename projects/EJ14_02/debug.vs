/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: debug.vs del ejercicio 14_02
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Febrero 2020
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;

out vec2 uv;

void main() {
    uv = aUv;
    gl_Position = vec4(aPos, 1.0);
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////