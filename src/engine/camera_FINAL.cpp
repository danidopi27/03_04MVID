/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   M�ster en Dise�o y Desarrollo de Videojuegos
  ASIGNATURA:  Programaci�n I
  DESCRIPCI�N: Librer�a de generaci�n y movimiento de la c�mara
  PROGRAMADOR: Daniel Dopico Gra�a
  FECHA:       Diciembre 2019
  VERSI�N:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////C�DIGO//////////////////////////////////////////////////////////////////////

//---------------LIBRER�AS---------------//
#include "engine/camera_FINAL.hpp"
#include <glm/gtc/matrix_transform.hpp>
//---------------LIBRER�AS---------------//

//-----------------------------------------------CONSTRUCTOR-----------------------------------------------//
Camera_FINAL::Camera_FINAL(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
 : _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}
//-----------------------------------------------CONSTRUCTOR-----------------------------------------------//

//-------------------------------------------------------CONSTRUCTOR-------------------------------------------------------//
Camera_FINAL::Camera_FINAL(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}
//-------------------------------------------------------CONSTRUCTOR-------------------------------------------------------//

//-------------------FUNCI�N GETVIEWMATRIX-------------------//
glm::mat4 Camera_FINAL::getViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}
//-------------------FUNCI�N GETVIEWMATRIX-------------------//

//-----------FUNCI�N GETFOV-----------//
float Camera_FINAL::getFOV() const {
    return _fov;
}
//-----------FUNCI�N GETFOV-----------//

//-------------FUNCI�N GETPOSITION-------------//
glm::vec3 Camera_FINAL::getPosition() const {
    return _position;
}
//-------------FUNCI�N GETPOSITION-------------//

//--------------------FUNCI�N UPDATECAMERAVECTORS--------------------//
void Camera_FINAL::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}
//--------------------FUNCI�N UPDATECAMERAVECTORS--------------------//

//--------------------------FUNCI�N GETFRONT--------------------------//
glm::vec3 Camera_FINAL::getFront() {
	return _front;		// Devuelve la posici�n frontal de la c�mara
}
//--------------------------FUNCI�N GETFRONT--------------------------//

//---------------------------------------------FUNCI�N HANDLEKEYBOARD---------------------------------------------//
void Camera_FINAL::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;

    switch (direction) {
        case Movement::Forward: _position.z += _front.z * velocity; _position.x += _front.x * velocity; break;
        case Movement::Backward: _position.z -= _front.z * velocity; _position.x -= _front.x * velocity; break;
        case Movement::Left: _position -= _right * velocity; break;
        case Movement::Right: _position += _right * velocity; break;
        default:;
    }
}
//---------------------------------------------FUNCI�N HANDLEKEYBOARD---------------------------------------------//

//----------------------------------FUNCI�N HANDLEMOUSEMOVEMENT----------------------------------//
void Camera_FINAL::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    const float xoff = xoffset * k_Sensitivity;
    const float yoff = yoffset * k_Sensitivity;

    _yaw += xoff;
    _pitch += yoff;

    if (constrainPitch) {
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }

    updateCameraVectors();
}
//----------------------------------FUNCI�N HANDLEMOUSEMOVEMENT----------------------------------//

//---------------FUNCI�N HANDLEMOUSESCROLL---------------//
void Camera_FINAL::handleMouseScroll(float yoffset) {
    if (_fov >= 1.0f && _fov <= 45.0f) _fov -= yoffset;
    if (_fov <= 1.0f) _fov = 1.0f;
    if (_fov >= 45.0f) _fov = 45.0f;
}
//---------------FUNCI�N HANDLEMOUSESCROLL---------------//

///////////////////////////////////////////////////////////////////FIN DE C�DIGO///////////////////////////////////////////////////////////////////