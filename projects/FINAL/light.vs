/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	     Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Light.vs del ejercicio FINAL
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Febrero 2020
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;                               // La posición 0 corresponde a posición
layout (location=1) in vec2 aUV;                                // La posición 1 corresponde a textura
layout (location=2) in vec3 aNormal;                            // La posición 2 corresponde a vector normal

uniform mat4 model;                                             // Matriz de espacio mundo
uniform mat4 view;                                              // Matriz de vista
uniform mat4 proj;                                              // Matriz de proyección

void main() {
    gl_Position = proj * view * model * vec4(aPos, 1.0);		    // Cálculo de la posición del objeto
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////