/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Librer�a de generaci�n de cubos mediante centro y radio
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////C�DIGO/////////////////////////////////////////////////////////////////////

//----------------------------------------------LIBRER�AS----------------------------------------------//
#include "engine/geometry/cube_05_01.hpp"	// Librer�a de creaci�n de cubos mediante centro y radio
//----------------------------------------------LIBRER�AS----------------------------------------------//

//--------------------------------------------CONSTRUCTOR CUBE_05_01--------------------------------------------//
Cube_05_01::Cube_05_01(float* center, float radio) {
    _nVertices = 6 * 2 * 3;								// 6 caras * 2 tri�ngulos * 3 v�rtices;
    _nElements = _nVertices;							// N� de elementos = N� de v�rtices

	const float x = center[0];							// Coordenada en x del centro del cubo
	const float y = center[1];							// Coordenada en y del centro del cubo
	const float z = center[2];							// Coordenada en z del centro del cubo

	float x_pos = x + radio;							// Coordenada hacia la derecha del centro en x
	float x_neg = x - radio;							// Coordenada hacia la izquierda del centro en x
	float y_pos = y + radio;							// Coordenada hacia arriba del centro en y
	float y_neg = y - radio;							// Coordenada hacia abajo del centro en y
	float z_pos = z + radio;							// Coordenada hacia adelante del centro en z
	float z_neg = z - radio;							// Coordenada hacia atr�s del centro en z

	// Posici�n de los v�rtices
    float positions[] = { x_neg, y_neg, z_pos,			// Cara delantera
						  x_pos, y_neg, z_pos,
						  x_pos, y_pos, z_pos,

						  x_neg, y_neg, z_pos,
						  x_pos, y_pos, z_pos,
						  x_neg, y_pos, z_pos,

						  x_pos, y_neg, z_pos,			// Cara lateral derecha
						  x_pos, y_neg, z_neg,
						  x_pos, y_pos, z_neg,

						  x_pos, y_neg, z_pos,
						  x_pos, y_pos, z_neg,
						  x_pos, y_pos, z_pos,

						  x_pos, y_neg, z_neg,			// Cara trasera
						  x_neg, y_neg, z_neg,
						  x_neg, y_pos, z_neg,

						  x_pos, y_neg, z_neg,
						  x_neg, y_pos, z_neg,
						  x_pos, y_pos, z_neg,

						  x_neg, y_neg, z_neg,			// Cara lateral izquierda
						  x_neg, y_neg, z_pos,
						  x_neg, y_pos, z_pos,

						  x_neg, y_neg, z_neg,
						  x_neg, y_pos, z_pos,
						  x_neg, y_pos, z_neg,

						  x_neg, y_neg, z_neg,			// Cara inferior
						  x_pos, y_neg, z_neg,
						  x_pos, y_neg, z_pos,

						  x_neg, y_neg, z_neg,
						  x_pos, y_neg, z_pos,
						  x_neg, y_neg, z_pos,

						  x_neg, y_pos, z_pos,			// Cara superior
						  x_pos, y_pos, z_pos,
						  x_pos, y_pos, z_neg,

						  x_neg, y_pos, z_pos,
						  x_pos, y_pos, z_neg,
                          x_neg, y_pos, z_neg};

	// Posici�n de la textura
    float uvs[] = { 0.0f, 0.0f,							// Cara delantera
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,							// Cara lateral derecha
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,							// Cara trasera
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,							// Cara lateral izquierda
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,							// Cara inferior
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,							// Cara superior
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f};

	// Posici�n de los vectores normales
    float normals[] = { 0.0f, 0.0f, 1.0f,				// Cara delantera
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        1.0f, 0.0f, 0.0f,				// Cara lateral derecha
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        0.0f, 0.0f, -1.0f,				// Cara trasera
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,

                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,

                        -1.0f, 0.0f, 0.0f,				// Cara lateral izquierda
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,

                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,

                        0.0f, -1.0f, 0.0f,				// Cara inferior
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,

                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,				// Cara superior
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f};

    uint32_t indices[] = { 0,  1,  2,    3,  4,  5,		// Cara delantera
                           6,  7,  8,    9, 10, 11,		// Cara lateral derecha
                          12, 13, 14,   15, 16, 17,		// Cara trasera
                          18, 19, 20,   21, 22, 23,		// Cara lateral izquierda
                          24, 25, 26,   27, 28, 29,		// Cara inferior
                          30, 31, 32,   33, 34, 35 };	// Cara superior

    uploadData(positions, uvs, normals, indices);		// Se suben los datos
}
//--------------------------------------------CONSTRUCTOR CUBE_05_01--------------------------------------------//

//////////////////////////////////////////////////////////////////FIN DE C�DIGO//////////////////////////////////////////////////////////////////