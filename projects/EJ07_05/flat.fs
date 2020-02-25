/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: flat.fs del ejercicio 7_05
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;																// Salida de framents

flat in vec3 normal;																	// Entrada de normales
flat in vec3 fragPos;																// Entrada de posiciones

uniform vec3 objectColor;														// Color de objeto
uniform vec3 lightColor;														// Color de luz

uniform float ambientStrength;													// Fuerza del ambiente

uniform vec3 lightPos;															// Posici�n de la luz
uniform vec3 viewPos;															// Posici�n de la vista
uniform int shininess;															// Valor de brillo
uniform float specularStrength;													// Fuerza de la componente especular
uniform float diffuseStrength;                          // Fuerza de la difusión

void main() {
    vec3 ambient = ambientStrength * lightColor;								// C�lculo del ambiente

    vec3 norm = normalize(normal);												// C�lculo de normales
    vec3 lightDir = normalize(lightPos - fragPos);								// Direcci�n de la luz
    float diff = max(dot(norm, lightDir), 0.0);									// Diferencia entre normales y direcci�n de la luz
    vec3 diffuse = diff * diffuseStrength * lightColor;					// C�lculo de la difusi�n

    vec3 viewDir = normalize(viewPos - fragPos);								// Vista de la direcci�n de la luz
    vec3 reflectDir = reflect(-lightDir, norm);									// C�lculo del reflejo de luz
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);			// C�lculo de componente especular
    vec3 specular = spec * specularStrength * lightColor;						// Composici�n de componente especular

    vec3 phong = (ambient + diffuse + specular) * objectColor;					// C�lculo del phong
    FragColor = vec4(phong, 1.0f);												// Se asigna la luz
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////