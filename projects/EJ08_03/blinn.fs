/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Blinn.fs del ejercicio 8_03
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Febrero 2020
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////
#version 330 core

out vec4 FragColor;																// Salida de framents

in vec3 normal;																	// Entrada de normales
in vec3 fragPos;																// Entrada de posiciones
in vec2 uv;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    int shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos;

void main() {
    vec3 albedo = vec3(texture(material.diffuse, uv));
    vec3 ambient = albedo * light.ambient;								        // C�lculo del ambiente

    vec3 norm = normalize(normal);												// C�lculo de normales
    vec3 lightDir = normalize(light.position - fragPos);								// Direcci�n de la luz
    float diff = max(dot(norm, lightDir), 0.0);									// Diferencia entre normales y direcci�n de la luz
    vec3 diffuse = diff * albedo * light.diffuse;										// C�lculo de la difusi�n

    vec3 viewDir = normalize(viewPos - fragPos);								// Vista de la direcci�n de la luz
    vec3 halfwayDir = normalize(lightDir + viewDir);							// C�lculo del reflejo de luz
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);				// C�lculo de componente especular
    vec3 specular = spec * vec3(texture(material.specular, uv)) * light.specular;					// Composici�n de componente especular

    vec3 phong = ambient + diffuse + specular;					// C�lculo del phong
    FragColor = vec4(phong, 1.0f);												// Se asigna la luz
}
////////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////