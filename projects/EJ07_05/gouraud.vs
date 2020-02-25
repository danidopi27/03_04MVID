/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Gouraud.vs del ejercicio 7_05
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

layout (location=0) in vec3 aPos;                               // La posici�n 0 corresponde a posici�n
layout (location=1) in vec2 aUV;                                // La posici�n 1 corresponde a textura
layout (location=2) in vec3 aNormal;                            // La posici�n 2 corresponde a vector normal

uniform mat4 model;                                             // Matriz de espacio mundo
uniform mat4 view;                                              // Matriz de vista
uniform mat4 proj;                                              // Matriz de proyecci�n
uniform mat3 normalMat;											// Matriz de normales

uniform vec3 objectColor;														    // Color de objeto
uniform vec3 lightColor;													    	// Color de luz

uniform float ambientStrength;													// Fuerza del ambiente

uniform vec3 lightPos;															    // Posición de la luz
uniform vec3 viewPos;															      // Posición de la vista
uniform int shininess;															    // Valor de brillo
uniform float specularStrength;													// Fuerza de la componente especular

out vec3 fragPos;												// Salida de posici�n

void main() {
    vec3 normal = normalMat * aNormal;								// C�lculo de normales
    
    vec3 ambient = ambientStrength * lightColor;								          // Cálculo del ambiente

    vec3 norm = normalize(normal);												                // Cálculo de normales
    vec3 lightDir = normalize(lightPos - fragPos);								    // Dirección de la luz en espacio de vista
    float diff = max(dot(norm, lightDir), 0.0);									          // Diferencia entre normales y dirección de la luz
    vec3 diffuse = diff * lightColor;											                // Cálculo de la difusión

    vec3 viewDir = normalize(viewPos-fragPos);								                    // Vista de la dirección de la luz desde el (0, 0, 0)
    vec3 reflectDir = reflect(-lightDir, norm);									          // Cálculo del reflejo de luz
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);			// Cálculo de componente especular
    vec3 specular = spec * specularStrength * lightColor;		
    
    vec3 phong = (ambient + diffuse + specular) * objectColor;					  // Cálculo del phong	
    
    fragPos = phong;					// Posici�n
    gl_Position = proj * view * model * vec4(aPos, 1.0);		// C�lculo de posici�n del elemento
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////