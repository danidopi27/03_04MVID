/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Phong.fs del ejercicio 7_01
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;																      // Salida de framents

in vec3 normal;																	        // Entrada de normales
in vec3 fragPos;																        // Entrada de posiciones

uniform vec3 objectColor;														    // Color de objeto
uniform vec3 lightColor;													    	// Color de luz

uniform float ambientStrength;													// Fuerza del ambiente

uniform vec3 lightPos;															    // Posición de la luz
uniform vec3 viewPos;															      // Posición de la vista
uniform int shininess;															    // Valor de brillo
uniform float specularStrength;													// Fuerza de la componente especular

uniform mat4 view;                                      // Matriz de espacio de vista

void main() {
    vec3 lightPosVista = vec3(view * vec4(lightPos, 1.0));                // LightPos en espacio de vista

    vec3 ambient = ambientStrength * lightColor;								          // Cálculo del ambiente

    vec3 norm = normalize(normal);												                // Cálculo de normales
    vec3 lightDir = normalize(lightPosVista - fragPos);								    // Dirección de la luz en espacio de vista
    float diff = max(dot(norm, lightDir), 0.0);									          // Diferencia entre normales y dirección de la luz
    vec3 diffuse = diff * lightColor;											                // Cálculo de la difusión

    vec3 viewDir = normalize(-fragPos);								                    // Vista de la dirección de la luz desde el (0, 0, 0)
    vec3 reflectDir = reflect(-lightDir, norm);									          // Cálculo del reflejo de luz
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);			// Cálculo de componente especular
    vec3 specular = spec * specularStrength * lightColor;						      // Composición de componente especular

    vec3 phong = (ambient + diffuse + specular) * objectColor;					  // Cálculo del phong
    FragColor = vec4(phong, 1.0f);												                // Se asigna la luz
}
////////////////////////////////////////////////////////////////////FIN DE CóDIGO//////////////////////////////////////////////////////////////////