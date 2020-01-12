/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CURSO:	   Máster en Diseño y Desarrollo de Videojuegos
  ASIGNATURA:  Programación I
  DESCRIPCIÓN: Librería de generación y movimiento de la cámara
  PROGRAMADOR: Daniel Dopico Graña
  FECHA:       Diciembre 2019
  VERSIÓN:     1.0

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////CÓDIGO//////////////////////////////////////////////////////////////////////

//---------------LIBRERÍAS---------------//
#include "engine/camera_06_01.hpp"
#include <glm/gtc/matrix_transform.hpp>
//---------------LIBRERÍAS---------------//

//-----------------------------------------------CONSTRUCTOR-----------------------------------------------//
Camera_06_01::Camera_06_01(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
 : _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}
//-----------------------------------------------CONSTRUCTOR-----------------------------------------------//

//-------------------------------------------------------CONSTRUCTOR-------------------------------------------------------//
Camera_06_01::Camera_06_01(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}
//-------------------------------------------------------CONSTRUCTOR-------------------------------------------------------//

//-------------------FUNCIÓN GETVIEWMATRIX-------------------//
glm::mat4 Camera_06_01::getViewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}
//-------------------FUNCIÓN GETVIEWMATRIX-------------------//

//-----------FUNCIÓN GETFOV-----------//
float Camera_06_01::getFOV() const {
    return _fov;
}
//-----------FUNCIÓN GETFOV-----------//

//-------------FUNCIÓN GETPOSITION-------------//
glm::vec3 Camera_06_01::getPosition() const {
    return _position;
}
//-------------FUNCIÓN GETPOSITION-------------//

//--------------------FUNCIÓN UPDATECAMERAVECTORS--------------------//
void Camera_06_01::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}
//--------------------FUNCIÓN UPDATECAMERAVECTORS--------------------//

//---------------------------------------------FUNCIÓN HANDLEKEYBOARD---------------------------------------------//
void Camera_06_01::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;

    switch (direction) {
        case Movement::Forward: _position.z += _front.z * velocity; _position.x += _front.x * velocity; break;
        case Movement::Backward: _position.z -= _front.z * velocity; _position.x -= _front.x * velocity; break;
        case Movement::Left: _position -= _right * velocity; break;
        case Movement::Right: _position += _right * velocity; break;
        default:;
    }
}
//---------------------------------------------FUNCIÓN HANDLEKEYBOARD---------------------------------------------//

//----------------------------------FUNCIÓN HANDLEMOUSEMOVEMENT----------------------------------//
void Camera_06_01::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
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
//----------------------------------FUNCIÓN HANDLEMOUSEMOVEMENT----------------------------------//

//---------------FUNCIÓN HANDLEMOUSESCROLL---------------//
void Camera_06_01::handleMouseScroll(float yoffset) {
    if (_fov >= 1.0f && _fov <= 45.0f) _fov -= yoffset;
    if (_fov <= 1.0f) _fov = 1.0f;
    if (_fov >= 45.0f) _fov = 45.0f;
}
//---------------FUNCIÓN HANDLEMOUSESCROLL---------------//

///////////////////////////////////////////////////////////////////FIN DE CÓDIGO///////////////////////////////////////////////////////////////////