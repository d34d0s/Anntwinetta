#include "../../headers/core/LotusCamera.h"

// Internal Camera API
LotusCamera* _lotusMakeCamera(GLFWwindow* window, LMvec3 location, LMvec3 up, float fov, float near, float far, unsigned int lookMode) {
    _LOTUS_CAMERA.far = far;
    _LOTUS_CAMERA.near = near;
    _LOTUS_CAMERA.fov = lmRadians(fov);
    _LOTUS_CAMERA.yaw = -90.0f;
    _LOTUS_CAMERA.pitch = 0.0f;
    _LOTUS_CAMERA.speed = 2.5f;
    _LOTUS_CAMERA.last_x = 0.0f;
    _LOTUS_CAMERA.last_y = 0.0f;
    _LOTUS_CAMERA.globalup = up;
    _LOTUS_CAMERA.sensitivity = 0.1f;
    _LOTUS_CAMERA.location = location;
    _LOTUS_CAMERA.forward = lmVec3(0.0f, 0.0f, -1.0f);
    
    int w, h; glfwGetWindowSize(window, &w, &h);
    _LOTUS_CAMERA.proj = lmPerspective(_LOTUS_CAMERA.fov, w / h, _LOTUS_CAMERA.near, _LOTUS_CAMERA.far);
    _LOTUS_CAMERA.view = lmLookAt(_LOTUS_CAMERA.location, lmAddVec3(_LOTUS_CAMERA.location, _LOTUS_CAMERA.forward), _LOTUS_CAMERA.up);

    switch (lookMode) {
        case CAM_MODE_FREELOOK:
            glfwSetCursorPosCallback(window, _lotusFreeLookCallback);
            break;
        default:
            break;
    } return &_LOTUS_CAMERA;
}

void _lotusFreeLookCallback(GLFWwindow* window, double xpos, double ypos) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float xoffset = xpos - _LOTUS_CAMERA.last_x;
    float yoffset = _LOTUS_CAMERA.last_y - ypos; 
    _LOTUS_CAMERA.last_x = xpos;
    _LOTUS_CAMERA.last_y = ypos;

    xoffset *= _LOTUS_CAMERA.sensitivity;
    yoffset *= _LOTUS_CAMERA.sensitivity;

    // Correct pitch and yaw assignment
    _LOTUS_CAMERA.yaw += xoffset;
    _LOTUS_CAMERA.pitch += yoffset;

    // Constrain pitch
    if (_LOTUS_CAMERA.pitch > 89.0f)
        _LOTUS_CAMERA.pitch = 89.0f;
    if (_LOTUS_CAMERA.pitch < -89.0f)
        _LOTUS_CAMERA.pitch = -89.0f;
}

// Move the camera forward (along the forward vector)
void _lotusCamMovIn(float delta_time) {
    _LOTUS_CAMERA.location = lmAddVec3(_LOTUS_CAMERA.location, lmScaleVec3(_LOTUS_CAMERA.forward, _LOTUS_CAMERA.speed * delta_time));
}

// Move the camera backward (along the forward vector)
void _lotusCamMovOut(float delta_time) {
    _LOTUS_CAMERA.location = lmSubVec3(_LOTUS_CAMERA.location, lmScaleVec3(_LOTUS_CAMERA.forward, _LOTUS_CAMERA.speed * delta_time));
}

// Move the camera to the left (perpendicular to the forward vector)
void _lotusCamMovLeft(float delta_time) {
    LMvec3 left = lmNormVec3(lmCrossVec3(_LOTUS_CAMERA.forward, _LOTUS_CAMERA.up));
    _LOTUS_CAMERA.location = lmSubVec3(_LOTUS_CAMERA.location, lmScaleVec3(left, _LOTUS_CAMERA.speed * delta_time));
}

// Move the camera to the right (perpendicular to the forward vector)
void _lotusCamMovRight(float delta_time) {
    LMvec3 right = lmNormVec3(lmCrossVec3(_LOTUS_CAMERA.forward, _LOTUS_CAMERA.up));
    _LOTUS_CAMERA.location = lmAddVec3(_LOTUS_CAMERA.location, lmScaleVec3(right, _LOTUS_CAMERA.speed * delta_time));
}

// Move the camera up (along the up vector)
void _lotusCamMovUp(float delta_time) {
    _LOTUS_CAMERA.location = lmAddVec3(_LOTUS_CAMERA.location, lmScaleVec3(_LOTUS_CAMERA.up, _LOTUS_CAMERA.speed * delta_time));
}

// Move the camera down (along the up vector)
void _lotusCamMovDown(float delta_time) {
    _LOTUS_CAMERA.location = lmSubVec3(_LOTUS_CAMERA.location, lmScaleVec3(_LOTUS_CAMERA.up, _LOTUS_CAMERA.speed * delta_time));
}

void _lotusUpdateCam(GLFWwindow* window) {
    LMvec3 forward;
    forward.x = cosf(lmRadians(_LOTUS_CAMERA.yaw)) * cosf(lmRadians(_LOTUS_CAMERA.pitch));
    forward.y = sinf(lmRadians(_LOTUS_CAMERA.pitch));
    forward.z = sinf(lmRadians(_LOTUS_CAMERA.yaw)) * cosf(lmRadians(_LOTUS_CAMERA.pitch));
    _LOTUS_CAMERA.forward = lmNormVec3(forward);
    _LOTUS_CAMERA.right = lmNormVec3(lmCrossVec3(_LOTUS_CAMERA.forward, _LOTUS_CAMERA.globalup));
    _LOTUS_CAMERA.up = lmNormVec3(lmCrossVec3(_LOTUS_CAMERA.right, _LOTUS_CAMERA.forward));

    int w, h; glfwGetWindowSize(window, &w, &h);
    _LOTUS_CAMERA.proj = lmPerspective(_LOTUS_CAMERA.fov, w / h, _LOTUS_CAMERA.near, _LOTUS_CAMERA.far);
    _LOTUS_CAMERA.view = lmLookAt(_LOTUS_CAMERA.location, lmAddVec3(_LOTUS_CAMERA.location, _LOTUS_CAMERA.forward), _LOTUS_CAMERA.up);
}


// External Camera API
LMmat4* lotusGetProjMatrix(void) { return &_LOTUS_CAMERA.proj; }
LMmat4* lotusGetViewMatrix(void) { return &_LOTUS_CAMERA.view; }
