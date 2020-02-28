/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: blur_vertical.fs del ejercicio 13_03
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Febrero 2020
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;

const float offset = 1.0 / 600.0;

void main() {
   float offsets[3] = (0.0, 1.3846153846, 3.2307692308);
   float kernel[3] = (0.2270270270, 0.3162162162, 0.0702702703);

   vec3 color = vec3(0.0);

   color = vec3(texture(screenTexture, uv.st / 600)) * kernel[0];

    for (int i = 1; i < 3; ++i) {
        color += vec3(texture(screenTexture, (uv.st + vec2(0.0, offsets[i]) / offset))) * kernel[i];
        color += vec3(texture(screenTexture, (uv.st - vec2(0.0, offsets[i]) / offset))) * kernel[i];
    }

    FragColor = vec4(color, 1.0);
}

////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////