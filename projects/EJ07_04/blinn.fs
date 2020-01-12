/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Blinn.fs del ejercicio 7_01
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;																// Salida de framents

in vec3 normal;																	// Entrada de normales
in vec3 fragPos;																// Entrada de posiciones

uniform vec3 objectColor;														// Color de objeto
uniform vec3 lightColor;														// Color de luz

uniform float ambientStrength;													// Fuerza del ambiente

uniform vec3 lightPos;															// Posición de la luz
uniform vec3 viewPos;															// Posición de la vista
uniform int shininess;															// Valor de brillo
uniform float specularStrength;													// Fuerza de la componente especular

void main() {
    vec3 ambient = ambientStrength * lightColor;								// Cálculo del ambiente

    vec3 norm = normalize(normal);												// Cálculo de normales
    vec3 lightDir = normalize(lightPos - fragPos);								// Dirección de la luz
    float diff = max(dot(norm, lightDir), 0.0);									// Diferencia entre normales y dirección de la luz
    vec3 diffuse = diff * lightColor;											// Cálculo de la difusión

    vec3 viewDir = normalize(viewPos - fragPos);								// Vista de la dirección de la luz
    vec3 halfwayDir = normalize(lightDir + viewDir);							// Cálculo del reflejo de luz
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);				// Cálculo de componente especular
    vec3 specular = spec * specularStrength * lightColor;						// Composición de componente especular

    vec3 phong = (ambient + diffuse + specular) * objectColor;					// Cálculo del phong
    FragColor = vec4(phong, 1.0f);												// Se asigna la luz
}
////////////////////////////////////////////////////////////////////FIN DE CÓDIGO//////////////////////////////////////////////////////////////////