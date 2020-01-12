/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Librer�a de generaci�n y movimiento de la c�mara
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////C�DIGO///////////////////////////////////////////////////////////////////////////////////////////

//############################################################################## DEFINICI�N .HPP ##############################################################################//
#ifndef __CAMERA_06_02_H__
#define __CAMERA_06_02_H__

//-----------LIBRER�AS-----------//
#include <glm/glm.hpp>
//-----------LIBRER�AS-----------//

//--------------VARIABLES--------------//
const float k_Yaw = -90.0f;
const float k_Pitch = 0.0f;
const float k_Speed = 2.5f;
const float k_Sensitivity = 0.1f;
const float k_FOV = 45.0f;
//--------------VARIABLES--------------//

//-----------------------------------------------------------------------------CLASE CUBE_05_01-----------------------------------------------------------------------------//
class Camera_06_02 {
	// M�todos y atributos p�blicos
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
	
	// M�todos y atributos privados
    private:
        void updateCameraVectors();
    private:
        glm::vec3 _position, _front, _up, _right, _worldUp;
        float _yaw, _pitch;
        float _fov;
};
//-----------------------------------------------------------------------------CLASE CUBE_05_01-----------------------------------------------------------------------------//

#endif
//############################################################################## DEFINICI�N .HPP ##############################################################################//

////////////////////////////////////////////////////////////////////////////////////////FIN DE C�DIGO////////////////////////////////////////////////////////////////////////////////////////