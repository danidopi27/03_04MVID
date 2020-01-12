/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Librería de generación y movimiento de la cámara
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////CÓDIGO///////////////////////////////////////////////////////////////////////////////////////////

//############################################################################## DEFINICIÓN .HPP ##############################################################################//
#ifndef __CAMERA_06_02_H__
#define __CAMERA_06_02_H__

//-----------LIBRERÍAS-----------//
#include <glm/glm.hpp>
//-----------LIBRERÍAS-----------//

//--------------VARIABLES--------------//
const float k_Yaw = -90.0f;
const float k_Pitch = 0.0f;
const float k_Speed = 2.5f;
const float k_Sensitivity = 0.1f;
const float k_FOV = 45.0f;
//--------------VARIABLES--------------//

//-----------------------------------------------------------------------------CLASE CUBE_05_01-----------------------------------------------------------------------------//
class Camera_06_02 {
	// Métodos y atributos públicos
    public:
        enum class Movement {
            Forward = 0,
            Backward = 1,
            Left = 2,
            Right = 3,
        };

		Camera_06_02(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = k_Yaw, float pitch = k_Pitch);
		Camera_06_02(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 getViewMatrix() const;
        float getFOV() const;
        glm::vec3 getPosition() const;

        void handleKeyboard(Movement direction, float dt);
        void handleMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void handleMouseScroll(float yoffset);
	
	// Métodos y atributos privados
    private:
        void updateCameraVectors();
    private:
        glm::vec3 _position, _front, _up, _right, _worldUp;
        float _yaw, _pitch;
        float _fov;
};
//-----------------------------------------------------------------------------CLASE CUBE_05_01-----------------------------------------------------------------------------//

#endif
//############################################################################## DEFINICIÓN .HPP ##############################################################################//

////////////////////////////////////////////////////////////////////////////////////////FIN DE CÓDIGO////////////////////////////////////////////////////////////////////////////////////////